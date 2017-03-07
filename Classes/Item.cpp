#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Item.h"

using namespace ENEMY;

Item::Item(
	const _In_ FLOAT vecX,
	const _In_ FLOAT vecY,
	const _In_ INT flightType,
	const _In_ Vec flightVec)
	: Enemy(vecX, vecY, flightType, flightVec)
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
	m_Width = itemWidth;
	m_Height = itemHeight;
	m_Hp = 10;
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
	if (!CheckDead())
	{
		AccTime(dt);
		Fly(dt);
		MissileFly(dt);
		Fire();
		CheckPlayerGetItem();
	}
	return;
}

void Item::Draw(_Inout_ HDC drawDC)
{
	m_pShadeSprite->BitBlt(drawDC, m_PosX - m_Width / 2, m_PosY - m_Height,
		m_Width, m_Height, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_PosX - m_Width / 2, m_PosY - m_Height,
		m_Width, m_Height, 0, 0, SRCPAINT);
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
	FLOAT playerPosX;
	FLOAT playerPosY;
	playerInfo.GetPosition(&playerPosX, &playerPosY);

	auto x0 = m_PosX - m_Width / 2;
	auto y0 = m_PosY - m_Height / 2;
	auto x1 = m_PosX + m_Width / 2;
	auto y1 = m_PosY + m_Height / 2;
	auto mx0 = playerPosX - playerCorrectionPixel;
	auto my0 = playerPosY - playerCorrectionPixel;
	auto mx1 = playerPosX + playerCorrectionPixel;
	auto my1 = playerPosY + playerCorrectionPixel;

	if (!(x1 <= mx0 || mx1 <= x0 || y1 <= my0 || my1 <= y0))
	{
		m_Hp -= 10;
		playerInfo.PlayerPowerUp();
		return TRUE;
	}
	return FALSE;
}
