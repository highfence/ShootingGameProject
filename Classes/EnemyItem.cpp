#include "stdafx.h"
#include "EnemyItem.h"

const wchar_t* spritePath = _T("../Resources/EnemyItem.png");
const wchar_t* shadePath = _T("../Resources/EnemyItemShade.png");
const INT enemyItemSpriteWidth = 64;
const INT enemyItemSpriteHeight = 64;

EnemyItem::EnemyItem(const _In_ FLOAT createX, const _In_ FLOAT createY, const _In_ INT flightType, const _In_ BOOL ItemLaunched)
	: Enemy(createX, createY, flightType), m_IsItemLaunched(ItemLaunched)
{
	m_pSprite = new CImage;
	m_pShadeSprite = new CImage;
	init();
}

void EnemyItem::init()
{
	m_pSprite->Load(spritePath);
	m_pShadeSprite->Load(shadePath);
	return;
}

EnemyItem::~EnemyItem()
{
	delete m_pSprite;
	delete m_pShadeSprite;
}

void EnemyItem::Draw(_Inout_ HDC drawDC)
{
	m_pShadeSprite->BitBlt(drawDC, m_PosX - enemyItemSpriteWidth / 2, m_PosY - enemyItemSpriteHeight,
		enemyItemSpriteWidth, enemyItemSpriteHeight, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_PosX - enemyItemSpriteWidth / 2, m_PosY - enemyItemSpriteHeight,
		enemyItemSpriteWidth, enemyItemSpriteHeight, 0, 0, SRCPAINT);
	return;
}
