#include "stdafx.h"
#include "Enemy.h"
#include "EnemyMissile.h"

Enemy::Enemy(const _In_ FLOAT x, const _In_ FLOAT y, const _In_ INT flightType)
	: m_PosX(x),
	m_PosY(y),
	m_AccTime(0.f),
	m_RecordAccTime(0.f),
	m_UnitVecX(0),
	m_UnitVecY(0),
	m_RecordFlyTime(0.f),
	m_PlayerX(0.f),
	m_PlayerY(0.f),
	m_FlightType(flightType),
	m_IsEnemyDead(FALSE)
{
	init();
}

void Enemy::init()
{
	m_pFlightHandler[FLIGHT_TYPE::FLY_STRAIGHT] = &Enemy::FlyStraight;
	m_pFlightHandler[FLIGHT_TYPE::FLY_ITEM] = &Enemy::FlyItem;
	m_pMissileFlyHandler[MISSILE_TYPE::STRAIGHT_FIRE] = &Enemy::MissileFlyStraight;

	return;
}


/*
	~Enemy
	m_MissileVec에 있는 미사일들 지워주기.
*/
Enemy::~Enemy()
{
	DeleteAllElementsMissileVector();
}


void Enemy::CalProc(const _In_ FLOAT dt)
{
	if (!CheckDead())
	{
		AccTime(dt);
		Fly(dt);
		MissileFly(dt);
		Fire();
	}
	return;
}

void Enemy::DrawProc(_Inout_ HDC drawDC)
{
	Draw(drawDC);
	DrawMissiles(drawDC);
	return;
}

void Enemy::Fly(const _In_ FLOAT dt)
{
	(this->*m_pFlightHandler[m_FlightType])(dt);
	return;
}

void Enemy::MissileFly(const _In_ FLOAT dt)
{
	for (auto i : m_MissileVec)
	{
		if (i->GetMissileLaunched())
		{
			auto MissileType = i->GetMissileType();
			(this->*m_pMissileFlyHandler[MissileType])(i, dt);
		}
	}
	return;
}

BOOL Enemy::FlyStraight(const _In_ FLOAT dt)
{
	m_PosY += m_FlightSpeed * dt;
	return TRUE;
}

// 랜덤한 방향의 벡터를 받아서 지정한 만큼 중구난방으로 움직이는 아이템.
BOOL Enemy::FlyItem(const _In_ FLOAT dt)
{
	const FLOAT itemFlyTime = 1.0f;
	if ((m_UnitVecX == 0 && m_UnitVecY == 0) || (m_RecordFlyTime > itemFlyTime))
	{
		GetUnitVec(rand() % 100, rand() % 100, &m_UnitVecX, &m_UnitVecY);
		m_RecordFlyTime = 0.f;
	}

	m_PosX += m_UnitVecX * dt * m_FlightSpeed;
	m_PosY += m_UnitVecY * dt * m_FlightSpeed;
	return TRUE;
}

BOOL Enemy::MissileFlyStraight(EnemyMissile* missile, const FLOAT dt)
{
	missile->Fly(dt, 0, 1, m_MissileSpeed);
	missile->CheckColideWithPlayer();
	return TRUE;
}

BOOL Enemy::CheckEnemyIsOnDisplay()
{
	if ((m_PosX + m_Width / 2) <= 0)
	{
		return false;
	}
	else if ((m_PosX - m_Width / 2) >= winWidth)
	{
		return false;
	}
	else if ((m_PosY + m_Height / 2) <= 0)
	{
		return false;
	}
	else if ((m_PosY - m_Height) / 2 >= winHeight)
	{
		return false;
	}

	return true;
}

void Enemy::GetDamage(const _In_ INT damage)
{
	m_Hp -= damage;

	if (m_Hp <= 0)
	{
		m_IsEnemyDead = TRUE;
	}
	
	return;
}

// Enemy안에 시간을 누적해주는 함수.
void Enemy::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	m_RecordAccTime += dt;
	m_RecordFlyTime += dt;
	return;
}

// 자신이 죽었는지 아닌지 판단하는 함수. 죽었다면 TRUE를 반환.
BOOL Enemy::CheckDead()
{
	if (m_Hp <= 0)
	{
		m_IsEnemyDead = TRUE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// 미사일들을 적재하는 함수. Enemy를 상속받는 클래스의 init에서 호출.
void Enemy::LoadMissiles(const _In_ ENEMY::MISSILE_SIZE missileSize)
{
	for (int i = 0; i < m_LoadedMissileNumber; ++i)
	{
		EnemyMissile* newMissile = new EnemyMissile(missileSize);
		m_MissileVec.push_back(newMissile);
	}

	return;
}

/*
	DrawMissiles
	미사일 벡터를 순회하며 Draw를 호출해주는 함수.
*/
void Enemy::DrawMissiles(_Inout_ HDC drawDC)
{
	for (auto i : m_MissileVec)
	{
		i->Draw(drawDC);
	}

	return;
}

/*
	DeleteAllElementsMissileVector
	멤버 변수 m_MissileVec에 있는 모든 원소들을 순회하면서 소멸자를 호출해주는 함수.
*/
void Enemy::DeleteAllElementsMissileVector()
{
	std::vector<EnemyMissile*>::iterator iter = m_MissileVec.begin();
	while (iter != m_MissileVec.end())
	{
		delete (*iter);
		iter = m_MissileVec.erase(iter);
	}

	return;
}