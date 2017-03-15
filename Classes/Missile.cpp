#include "stdafx.h"
#include "Missile.h"
#include "Enemy.h"
#include "EnemyManager.h"

// 미사일 대기 장소.
const FLOAT savePlacePos = -300.f;

Missile::Missile()
	: m_IsMissileLaunched(false),
	m_Pos(savePlacePos, savePlacePos),
	m_MissileType(NONE),
	m_pSprite(nullptr),
	m_pShapeSprite(nullptr)
{
	m_pSprite = new CImage();
	m_pShapeSprite = new CImage();
	init();
}

void Missile::init()
{
	return;
}

/*
	Destructer of Missile.
*/
Missile::~Missile()
{
	delete m_pSprite;
	delete m_pShapeSprite;
}


/*
	Launch gives position to Missile (Generally their own position who calls this Function) 
	If Launch success, it return TRUE.
	else, it return FALSE.
*/
BOOL Missile::Launch(
	const _In_ Vec createVec)
{
	if (m_IsMissileLaunched)
	{
		return FALSE;
	}
	
	m_IsMissileLaunched = TRUE;
	m_Pos = createVec;
	
	return TRUE;
}

/*
	Initialize with MissileType (Launch Func Overloading)
*/
BOOL Missile::Launch(
	const _In_ ENEMY::MISSILE_TYPE missileType,
	const _In_ Vec createVec)
{
	if (!Launch(createVec))
	{
		return FALSE;
	}

	m_MissileType = missileType;
	return TRUE;
}

/*
	If missile is on the board, return TRUE.
	else, return FALSE (It means missile is DEAD)
*/ 
BOOL Missile::IsMissileOnDisplay()
{
	if (m_Pos.y < -m_Height)
	{
		return FALSE;
	}
	else if (m_Pos.x < -m_Width)
	{
		return FALSE;
	}
	else if (m_Pos.x > winWidth + m_Width)
	{
		return FALSE;
	}
	else if (m_Pos.y > winHeight + m_Height)
	{
		return FALSE;
	}
	
	return TRUE;
}

void Missile::Draw(_Inout_ HDC drawDC)
{
	if (!m_IsMissileLaunched)
	{
		return;
	}

#pragma warning(push)
#pragma warning(disable : 4244)

	m_pShapeSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCAND);

	m_pSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCPAINT);

#pragma warning(pop)
	return;
}


BOOL Missile::GetMissileLaunched() const
{
	return m_IsMissileLaunched;
}

void Missile::SetMissileType(const _In_ ENEMY::MISSILE_TYPE type)
{
	m_MissileType = type;
	return;
}

MISSILE_TYPE Missile::GetMissileType() const
{
	return m_MissileType;
}