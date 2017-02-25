#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const _In_ FLOAT x, const _In_ FLOAT y, const _In_ INT flightType)
	: m_PosX(x), m_PosY(y), m_FlightType(flightType)
{
	init();
}

void Enemy::init()
{
	return;
}

Enemy::~Enemy()
{

}