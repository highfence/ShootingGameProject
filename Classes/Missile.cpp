#include "stdafx.h"
#include "Missile.h"
#include "Enemy.h"
#include "EnemyManager.h"

// 미사일 대기 장소.
const FLOAT savePlacePos = -300;

Missile::Missile()
	: m_IsMissileLaunched(false), m_PosX(savePlacePos), m_PosY(savePlacePos) 
{
	m_pSprite = new CImage;
	m_pShapeSprite = new CImage;
	init();
}

void Missile::init()
{
	return;
}

Missile::~Missile()
{
	delete m_pSprite;
	delete m_pShapeSprite;
}

BOOL Missile::Launch(const _In_ FLOAT x, const _In_ FLOAT y)
{
	if (m_IsMissileLaunched)
	{
		return FALSE;
	}
	
	m_IsMissileLaunched = TRUE;
	m_PosX = x;
	m_PosY = y;
	
	return TRUE;
}


BOOL Missile::IsMissileOnDisplay()
{
	if (m_PosY < -m_Height)
	{
		return FALSE;
	}
	else if (m_PosX < -m_Width)
	{
		return FALSE;
	}
	else if (m_PosX > winWidth + m_Width)
	{
		return FALSE;
	}
	else if (m_PosY > winHeight + m_Height)
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

	m_pShapeSprite->BitBlt(drawDC, m_PosX - m_Width / 2, m_PosY - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCAND);

	m_pSprite->BitBlt(drawDC, m_PosX - m_Width / 2, m_PosY - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCPAINT);

	return;
}


BOOL Missile::GetMissileLaunched()
{
	return m_IsMissileLaunched;
}