#include "stdafx.h"
#include "Enemy.h"
#include "EnemyMissile.h"

Enemy::Enemy(
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_opt_ Vec flightVec)
	: 
	m_Pos(createPos),
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
	m_FlightVec = flightVec;
	init();
}

void Enemy::init()
{
	m_pFlightHandler[FLIGHT_TYPE::FLY_STRAIGHT] = &Enemy::FlyStraight;
	m_pFlightHandler[FLIGHT_TYPE::FLY_ITEM] = &Enemy::FlyItem;
	m_pFlightHandler[FLIGHT_TYPE::FLY_ACCELERATE] = &Enemy::FlyAccelerate;
	m_pFlightHandler[FLIGHT_TYPE::FLY_GO_AND_SLOW] = &Enemy::FlyGoAndSlow;

	m_pMissileFlyHandler[MISSILE_TYPE::STRAIGHT_FIRE] = &Enemy::MissileFlyStraight;

	return;
}


/*
	~Enemy
	m_MissileVec�� �ִ� �̻��ϵ� �����ֱ�.
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

/*
	FlyStratight accord with m_FlightVec.
*/
BOOL Enemy::FlyStraight(const _In_ FLOAT dt)
{
	m_Pos.x += m_FlightVec.x * m_FlightSpeed * dt;
	m_Pos.y += m_FlightVec.y * m_FlightSpeed * dt;
	return TRUE;
}

/*
	Make random flightVector and Fly until "itemFlyTime(const FLOAT)" end.
	Using in Item :: public Enemy
*/
BOOL Enemy::FlyItem(const _In_ FLOAT dt)
{
	const FLOAT itemFlyTime = 1.0f;
	if ((m_UnitVecX == 0 && m_UnitVecY == 0) || (m_RecordFlyTime > itemFlyTime))
	{
		GetUnitVec((FLOAT)(rand() % 100), (FLOAT)(rand() % 100), &m_UnitVecX, &m_UnitVecY);
		m_RecordFlyTime = 0.f;
	}

	m_Pos.x += m_UnitVecX * dt * m_FlightSpeed;
	m_Pos.y += m_UnitVecY * dt * m_FlightSpeed;
	return TRUE;
}

/*
	���� �������� ����
*/
BOOL Enemy::FlyAccelerate(const _In_ FLOAT dt)
{
	FLOAT currentSpeed = (m_Option.m_InitSpeed + m_Option.m_AccSpeedPerSec * m_AccTime);
	m_Pos.x += m_FlightVec.x * currentSpeed * dt;
	m_Pos.y += m_FlightVec.y * currentSpeed * dt;
	return TRUE;
}

/*
	��� ���� �Ÿ������� ������ �����ϴٰ� ���� �ð� �� �ڸ����� ������ ���� ����.
*/
BOOL Enemy::FlyGoAndSlow(const _In_ FLOAT dt)
{
	// ���� �ð��� m_TimeToSlow�� m_TimeToSlow + m_SlowedTime ������ ��� ���� ����.
	if ((m_AccTime < m_Option.m_TimeToSlow + m_Option.m_SlowedTime) 
		&& (m_AccTime > m_Option.m_TimeToSlow))
	{
		m_Pos.x += m_FlightVec.x * m_Option.m_SlowedSpeed * dt;
		m_Pos.y += m_FlightVec.y * m_Option.m_SlowedSpeed * dt;
	}
	else
	{
		m_Pos.x += m_FlightVec.x * m_Option.m_InitSpeed * dt;
		m_Pos.y += m_FlightVec.y * m_Option.m_InitSpeed * dt;
	}

	return TRUE;
}

/*
	�������� �̻����� ���ư��� �ϴ� ���.
*/
BOOL Enemy::MissileFlyStraight(EnemyMissile* missile, const FLOAT dt)
{
	missile->Fly(dt, 0, 1, m_MissileSpeed);
	missile->CheckColideWithPlayer();
	return TRUE;
}

/*
	Return Enemy Is on Display.
*/
BOOL Enemy::CheckEnemyIsOnDisplay()
{
	if ((m_Pos.x + m_SpriteRange.x / 2) <= -boundaryRange)
	{
		return FALSE;
	}
	else if ((m_Pos.x - m_SpriteRange.y / 2) >= winWidth + boundaryRange)
	{
		return FALSE;
	}
	else if ((m_Pos.y + m_SpriteRange.y / 2) <= -boundaryRange)
	{
		return FALSE;
	}
	else if ((m_Pos.y - m_SpriteRange.x / 2) >= winHeight + boundaryRange)
	{
		return FALSE;
	}

	return true;
}

/*
	m_FlightVec�� �µ��� CImage�� ȸ�������ִ� �Լ�.
	Enemy ��� Ŭ�������� ȣ��.
*/
INT Enemy::RotateAccordWithVec()
{
	// TODO :: CImage ȸ�� �Լ�.

	return WELL_PERFORMED;
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

// Enemy�ȿ� �ð��� �������ִ� �Լ�.
void Enemy::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	m_RecordAccTime += dt;
	m_RecordFlyTime += dt;
	return;
}

// �ڽ��� �׾����� �ƴ��� �Ǵ��ϴ� �Լ�. �׾��ٸ� TRUE�� ��ȯ.
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

// �̻��ϵ��� �����ϴ� �Լ�. Enemy�� ��ӹ޴� Ŭ������ init���� ȣ��.
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
	�̻��� ���͸� ��ȸ�ϸ� Draw�� ȣ�����ִ� �Լ�.
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
	��� ���� m_MissileVec�� �ִ� ��� ���ҵ��� ��ȸ�ϸ鼭 �Ҹ��ڸ� ȣ�����ִ� �Լ�.
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