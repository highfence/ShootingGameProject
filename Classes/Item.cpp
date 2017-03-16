#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Item.h"

using namespace ENEMY;

Item::Item(void)
	: Enemy()
{
	init();
}


void Item::init()
{
	m_pSprite->Load(itemSpritePath.c_str());
	m_pShadeSprite->Load(itemShadePath.c_str());
	m_SpriteRange.x = itemWidth;
	m_SpriteRange.y = itemHeight;
	m_ColideRange = Vec(0, 0);
	m_Hp = 100000;
	m_LoadedMissileNumber = 0;
	m_EnemyType = ENEMY::ENEMY_TYPE::ITEM;
	
	return;
}


Item::~Item()
{
}

void Item::CalcProc(const _In_ FLOAT dt)
{
	AccTime(dt);
	Fly(dt);
	CheckPlayerGetItem();

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
//
//void Item::Fire()
//{
//	return;
//}

BOOL Item::CheckPlayerGetItem()
{
	Player& playerInfo = EnemyManager::GetInstance()->getPlayerInfo();
	FLOAT playerCorrectionPixel = playerInfo.GetCollisionPixel();
	Vec playerPos;
	playerInfo.GetPosition(&playerPos);

	if (IsObjectColided(playerPos, Vec(playerCorrectionPixel, playerCorrectionPixel),
		m_Pos, m_SpriteRange))
	{
		playerInfo.PlayerPowerUp();
		Deactivate();
		return TRUE;
	}
	return FALSE;
}
