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

FireOption::~FireOption()
{
}

FireOption & FireOption::operator=(const FireOption op)
{
	setFireType(op.getFireType());
	setMissileType(op.getMissileType());
	setMissileSize(op.getMissileSize());
	setMissileSpeed(op.getMissileSpeed());
	setAccMissileSpeed(op.getAccMissileSpeed());
	setWaitingTime(op.getWaitingTime());
	setMissileVec(op.getMissileVec());
	m_IsOptionCanUse = TRUE;
	return *this;
}

/*
	Getter, Setter Zone
*/
BOOL FireOption::getIsOptionCanUse() const
{
	return m_IsOptionCanUse;
}

ENEMY::FIRE_TYPE FireOption::getFireType() const
{
	return m_FireType;
}

ENEMY::MISSILE_TYPE FireOption::getMissileType() const
{
	return m_MissileType;
}

ENEMY::MISSILE_SIZE FireOption::getMissileSize() const
{
	return m_MissileSize;
}

FLOAT FireOption::getMissileSpeed() const
{
	return m_MissileSpeed;
}

FLOAT FireOption::getAccMissileSpeed() const
{
	return m_AccMissileSpeed;
}

FLOAT FireOption::getWaitingTime() const
{
	return m_WaitingTime;
}

Vec FireOption::getMissileVec() const
{
	return m_MissileVec;
}

void FireOption::setFireType(const ENEMY::FIRE_TYPE fireType)
{
	m_FireType = fireType;
}

void FireOption::setMissileType(const ENEMY::MISSILE_TYPE missileType)
{
	m_MissileType = missileType;
}

void FireOption::setMissileSize(const ENEMY::MISSILE_SIZE missileSize)
{
	m_MissileSize = missileSize;
}

void FireOption::setMissileSpeed(const FLOAT missileSpeed)
{
	m_MissileSpeed = missileSpeed;
}

void FireOption::setAccMissileSpeed(const FLOAT accMissileSpeed)
{
	m_AccMissileSpeed = accMissileSpeed;
}

void FireOption::setWaitingTime(const FLOAT waitingTime)
{
	m_WaitingTime = waitingTime;
}

void FireOption::setMissileVec(const Vec missileVec)
{
	m_MissileVec = missileVec;
}
