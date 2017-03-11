#include "stdafx.h"
#include "FireOption.h"



FireOption::FireOption()
	: m_IsOptionCanUse(FALSE)
{
}

FireOption::FireOption(
	const ENEMY::FIRE_TYPE fireType,
	const ENEMY::MISSILE_TYPE missileType,
	const ENEMY::MISSILE_SIZE missileSize,
	const FLOAT missileSpeed,
	const FLOAT accMissileSpeed,
	const FLOAT waitingTime,
	const Vec missileVec)
	: m_IsOptionCanUse(TRUE)
{
}

FireOption::FireOption(const std::nullptr_t)
{
	m_IsOptionCanUse = FALSE;
}

FireOption::~FireOption()
{
}

FireOption & FireOption::operator=(const FireOption op)
{
	SetFireType(op.GetFireType());
	SetMissileType(op.GetMissileType());
	SetMissileSize(op.GetMissileSize());
	SetMissileSpeed(op.GetMissileSpeed());
	SetAccMissileSpeed(op.GetAccMissileSpeed());
	SetWaitingTime(op.GetWaitingTime());
	SetMissileVec(op.GetMissileVec());
	m_IsOptionCanUse = TRUE;
	return *this;
}

/*
	Getter, Setter Zone
*/
BOOL FireOption::GetIsOptionCanUse() const
{
	return m_IsOptionCanUse;
}

ENEMY::FIRE_TYPE FireOption::GetFireType() const
{
	return m_FireType;
}

ENEMY::MISSILE_TYPE FireOption::GetMissileType() const
{
	return m_MissileType;
}

ENEMY::MISSILE_SIZE FireOption::GetMissileSize() const
{
	return m_MissileSize;
}

FLOAT FireOption::GetMissileSpeed() const
{
	return m_MissileSpeed;
}

FLOAT FireOption::GetAccMissileSpeed() const
{
	return m_AccMissileSpeed;
}

FLOAT FireOption::GetWaitingTime() const
{
	return m_WaitingTime;
}

Vec FireOption::GetMissileVec() const
{
	return m_MissileVec;
}

void FireOption::SetFireType(const ENEMY::FIRE_TYPE fireType)
{
	m_FireType = fireType;
}

void FireOption::SetMissileType(const ENEMY::MISSILE_TYPE missileType)
{
	m_MissileType = missileType;
}

void FireOption::SetMissileSize(const ENEMY::MISSILE_SIZE missileSize)
{
	m_MissileSize = missileSize;
}

void FireOption::SetMissileSpeed(const FLOAT missileSpeed)
{
	m_MissileSpeed = missileSpeed;
}

void FireOption::SetAccMissileSpeed(const FLOAT accMissileSpeed)
{
	m_AccMissileSpeed = accMissileSpeed;
}

void FireOption::SetWaitingTime(const FLOAT waitingTime)
{
	m_WaitingTime = waitingTime;
}

void FireOption::SetMissileVec(const Vec missileVec)
{
	m_MissileVec = missileVec;
}
