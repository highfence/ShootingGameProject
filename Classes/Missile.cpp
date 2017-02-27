#include "stdafx.h"
#include "Missile.h"
#include "Enemy.h"
#include "EnemyManager.h"

const wchar_t* playerMissile = _T("../Resources/MissileRed.png");
const wchar_t* playerShape = _T("../Resources/MissileRedShape.png");
const FLOAT playerMissileSpeed = 2000;
const FLOAT playerMissileWidth = 6;
const FLOAT playerMissileHeight = 22;
const FLOAT savePlacePos = -300;
const FLOAT colideCorrectionPixel = 15;
const INT playerMissileDamageOneTier = 50;

Missile::Missile()
	: m_IsMissileLaunched(false), m_PosX(savePlacePos), m_PosY(savePlacePos), m_Damage(playerMissileDamageOneTier)
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

BOOL Missile::CheckColide()
{
	auto EnemyVec = EnemyManager::getInstance()->getEnemyVec();

	for (auto i : EnemyVec)
	{
		if (IsColideWithEnemy(i->m_PosX, i->m_PosY, i->m_Width, i->m_Height))
		{
			// 충돌 처리.
			i->GetDamage(m_Damage);

			// 충돌 후 미사일 소멸
			m_IsMissileLaunched = FALSE;
			return TRUE;
		}
	}
	
	return FALSE;
}

BOOL Missile::IsColideWithEnemy(const _In_ FLOAT enemyPosX, const _In_ FLOAT enemyPosY, const _In_ FLOAT enemyWidth, const _In_ FLOAT enemyHeight)
{
	FLOAT enemyX1 = enemyPosX - enemyWidth / 2 + colideCorrectionPixel;
	FLOAT enemyY1 = enemyPosY - enemyHeight / 2 + colideCorrectionPixel;
	FLOAT enemyX2 = enemyPosX + enemyWidth / 2 - colideCorrectionPixel;
	FLOAT enemyY2 = enemyPosY + enemyHeight / 2 - colideCorrectionPixel;

	FLOAT thisX1 = m_PosX - playerMissileWidth / 2;
	FLOAT thisY1 = m_PosY - playerMissileHeight / 2;
	FLOAT thisX2 = m_PosX + playerMissileWidth / 2;
	FLOAT thisY2 = m_PosY + playerMissileHeight / 2;

	if (!(thisX2 < enemyX1 || enemyX2 < thisX1 || thisY2 < enemyY1 || enemyY2 < thisY1))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL Missile::GetMissileLaunched()
{
	return m_IsMissileLaunched;
}