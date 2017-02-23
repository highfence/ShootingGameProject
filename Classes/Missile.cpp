#include "stdafx.h"
#include "Missile.h"

const wchar_t* playerMissile = _T("../Resources/MissileRed.png");
const wchar_t* playerShape = _T("../Resources/MissileRedShape.png");
const FLOAT playerMissileSpeed = 700;
const FLOAT playerMissileWidth = 6;
const FLOAT playerMissileHeight = 22;
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
	m_pShapeSprite->Load(playerShape);
	m_pSprite->Load(playerMissile);
	return;
}

Missile::~Missile()
{
	delete m_pSprite;
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

// TODO :: Fly 타입에 따라 다르도록 설정.. 해야하는데.
// 우선 간단하게 만들어보자.
void Missile::Fly(const _In_ FLOAT dt)
{
	if (!m_IsMissileLaunched)
	{
		return;
	}

	m_PosY -= playerMissileSpeed * dt;

	if (!IsMissileOnDisplay())
	{
		m_IsMissileLaunched = FALSE;
	}

	return;
}


BOOL Missile::IsMissileOnDisplay()
{
	if (m_PosY < -playerMissileHeight)
	{
		return FALSE;
	}
	else if (m_PosX < -playerMissileWidth)
	{
		return FALSE;
	}
	else if (m_PosX > winWidth + playerMissileWidth)
	{
		return FALSE;
	}
	else if (m_PosY > winHeight + playerMissileHeight)
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

	m_pShapeSprite->BitBlt(drawDC, m_PosX - playerMissileWidth / 2, m_PosY - playerMissileHeight / 2,
		playerMissileWidth, playerMissileHeight, 0, 0, SRCAND);

	m_pSprite->BitBlt(drawDC, m_PosX - playerMissileWidth / 2, m_PosY - playerMissileHeight / 2,
		playerMissileWidth, playerMissileHeight, 0, 0, SRCPAINT);

	return;
}