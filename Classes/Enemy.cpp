#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const _In_ FLOAT x, const _In_ FLOAT y, const _In_ INT flightType)
	: m_PosX(x), m_PosY(y), m_FlightType(flightType)
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