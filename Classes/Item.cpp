#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Item.h"

using namespace ENEMY;

Item::Item(
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_ Vec flightVec)
	: Enemy(createPos, flightType, flightVec)
{
	m_pSprite = new CImage;
	m_pShadeSprite = new CImage;
	init();
}

void Item::init()
{
	m_pSprite->Load(itemSpritePath.c_str());
	m_pShadeSprite->Load(itemShadePath.c_str());
	m_FlightSpeed = 150;
	m_SpriteRange.x = itemWidth;
	m_SpriteRange.y = itemHeight;
	m_ColideRange = Vec(0, 0);
	m_Hp = 100000;
	m_LoadedMissileNumber = 0;
	
	return;
}


Item::~Item()
{
	delete m_pSprite;
	delete m_pShadeSprite;
}

void Item::CalProc(const _In_ FLOAT dt)
{
	AccTime(dt);
	Fly(dt);
	CheckPlayerGetItem();

	if (!CheckEnemyIsOnDisplay())
	{
		m_IsEnemyReadyToDelete = TRUE;
	}
	return;
}

void Item::Draw(_Inout_ HDC drawDC)
{
#pragma warning(push)
#pragma warning(disable : 4244)

	m_pShadeSprite->BitBlt(drawDC, m_Pos.x - m_SpriteRange.x / 2, m_Pos.y - m_SpriteRange.y / 2,
		m_SpriteRange.x, m_SpriteRange.y, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_Pos.x - m_SpriteRange.x / 2, m_Pos.y - m_SpriteRange.y / 2,
		m_SpriteRange.x, m_SpriteRange.y, 0, 0, SRCPAINT);

#pragma warning(pop)
	return;
}

void Item::Explode()
{
	return;
}

void Item::DeadProc()
{
	return;
}

void Item::Fire()
{
	return;
}

BOOL Item::CheckPlayerGetItem()
{
	Player& playerInfo = EnemyManager::getInstance()->getPlayerInfo();
	FLOAT playerCorrectionPixel = playerInfo.GetCollisionPixel();
	Vec playerPos;
	playerInfo.GetPosition(&playerPos);

	// TODO :: 이거 충돌판정 하나로 모아서 처리할 함수 만들기.
	auto x0 = m_Pos.x - m_SpriteRange.x / 2;
	auto y0 = m_Pos.y - m_SpriteRange.y / 2;
	auto x1 = m_Pos.x + m_SpriteRange.x / 2;
	auto y1 = m_Pos.y + m_SpriteRange.y / 2;
	auto mx0 = playerPos.x - playerCorrectionPixel;
	auto my0 = playerPos.y - playerCorrectionPixel;
	auto mx1 = playerPos.x + playerCorrectionPixel;
	auto my1 = playerPos.y + playerCorrectionPixel;

	if (!(x1 <= mx0 || mx1 <= x0 || y1 <= my0 || my1 <= y0))
	{
		playerInfo.PlayerPowerUp();
		m_IsEnemyReadyToDelete = TRUE;
		return TRUE;
	}
	return FALSE;
}
