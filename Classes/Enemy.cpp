#include "stdafx.h"
#include "Enemy.h"
#include "EnemyMissile.h"

Enemy::Enemy(const _In_ FLOAT x, const _In_ FLOAT y, const _In_ INT flightType)
	: m_PosX(x), m_PosY(y), m_AccTime(0.f), m_RecordAccTime(0.f), m_PlayerX(0.f), m_PlayerY(0.f), m_FlightType(flightType), m_IsEnemyDead(FALSE)
{
	init();
}

void Enemy::init()
{
	m_pFlightHandler[FLIGHT_TYPE::FLY_STRAIGHT] = &Enemy::FlyStraight;
	m_pMissileFlyHandler[MISSILE_TYPE::STRAIGHT_FIRE] = &Enemy::MissileFlyStraight;
	return;
}

Enemy::~Enemy()
{

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
	return true;
}

BOOL Enemy::MissileFlyStraight(EnemyMissile* missile, const FLOAT dt)
{
	missile->Fly(dt, 0, 1, m_MissileSpeed);
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

// Enemy�ȿ� �ð��� �������ִ� �Լ�.
void Enemy::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	m_RecordAccTime += dt;
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

// ���ư��� �ִ� �̻��ϵ��� �׷��ִ� �Լ�.
void Enemy::DrawMissiles(_Inout_ HDC drawDC)
{
	for (auto i : m_MissileVec)
	{
		i->Draw(drawDC);
	}

	return;
}
