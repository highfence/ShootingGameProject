#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Item.h"

using namespace ENEMY;

Item::Item(const _In_ FLOAT vecX, const _In_ FLOAT vecY, const _In_ INT flightType)
	: Enemy(vecX, vecY, flightType)
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
	
	return;
}


Item::~Item()
{
	delete m_pSprite;
	delete m_pShadeSprite;
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

	if ((m_PosX + m_Width / 2) < playerPosX - playerCorrectionPixel)
	{
		return FALSE;
	}
	else if ((m_PosX - m_Width / 2) > playerPosX + playerCorrectionPixel)
	{
		return FALSE;
	}
	else if ((m_PosY + m_Height / 2) < playerPosY - playerCorrectionPixel)
	{
		return FALSE;
	}
	else if ((m_PosY - m_Height / 2) < playerPosY + playerCorrectionPixel)
	{
		return FALSE;
	}

	return TRUE;
}
