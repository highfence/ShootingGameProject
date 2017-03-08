#include "stdafx.h"
#include "MissileOption.h"

MissileOption::MissileOption(
	const _In_opt_ Vec missileVec,
	const _In_opt_ FLOAT missileSpeed,
	const _In_opt_ ENEMY::MISSILE_TYPE missileType,
	const _In_opt_ ENEMY::MISSILE_SIZE missileSize)
	: m_MissileVec(missileVec),
	m_MissileSpeed(missileSpeed),
	m_MissileType(missileType),
	m_MissileSize(missileSize),
	m_IsOptionCanUse(TRUE)
{
}

MissileOption::MissileOption(const std::nullptr_t)
	: m_IsOptionCanUse(FALSE)
{
}

MissileOption::MissileOption()
	: m_IsOptionCanUse(FALSE)
{
}

MissileOption::~MissileOption()
{
}

MissileOption & MissileOption::operator=(const _In_ MissileOption option)
{
	m_IsOptionCanUse = TRUE;
	m_MissileVec = option.m_MissileVec;
	m_MissileSpeed = option.m_MissileSpeed;
	m_MissileType = option.m_MissileType;
	m_MissileSize = option.m_MissileSize;

	return *this;
}

BOOL MissileOption::IsOptionCanUse() const
{
	return m_IsOptionCanUse;
}