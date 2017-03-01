#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const _In_ FLOAT x, const _In_ FLOAT y, const _In_ INT flightType)
	: m_PosX(x), m_PosY(y), m_AccTime(0.f), m_FlightType(flightType), m_IsEnemyDead(FALSE)
{
	init();
}

void Enemy::init()
{
	m_pFlightHandler[FLY_STRAIGHT] = &Enemy::FlyStraight;
	return;
}

Enemy::~Enemy()
{

}

void Enemy::Fly(const _In_ FLOAT dt)
{
	(this->*m_pFlightHandler[m_FlightType])(dt);
	return;
}

BOOL Enemy::FlyStraight(const _In_ FLOAT dt)
{
	m_PosY += m_FlightSpeed * dt;
	return true;
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

void Enemy::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	return;
}
