#include "stdafx.h"
#include "EnemyItem.h"
#include "EffectManager.h"

const wchar_t* spritePath = _T("../Resources/EnemyItem.png");
const wchar_t* shadePath = _T("../Resources/EnemyItemShade.png");
const wchar_t* spriteOnPath = _T("../Resources/EnemyItemOn.png");
const INT enemyItemSpriteWidth = 64;
const INT enemyItemSpriteHeight = 64;
const FLOAT enemyItemFlightSpeed = 300;
const INT enemyItemHp = 100;

EnemyItem::EnemyItem(const _In_ FLOAT createX, const _In_ FLOAT createY, const _In_ INT flightType, const _In_ BOOL ItemLaunched)
	: Enemy(createX, createY, flightType), m_IsItemLaunched(ItemLaunched)
{
	m_pSprite = new CImage;
	m_pShadeSprite = new CImage; 
	init();
}

void EnemyItem::init()
{
	if (m_IsItemLaunched == TRUE)
	{
		m_pSprite->Load(spriteOnPath);
	}
	else
	{
		m_pSprite->Load(spritePath);
	}
	m_pShadeSprite->Load(shadePath);

	m_FlightSpeed = enemyItemFlightSpeed;
	m_Width = enemyItemSpriteWidth;
	m_Height = enemyItemSpriteHeight;
	m_Hp = enemyItemHp;
	return;
}

EnemyItem::~EnemyItem()
{
	delete m_pSprite;
	delete m_pShadeSprite;
}

void EnemyItem::Draw(_Inout_ HDC drawDC)
{
	m_pShadeSprite->BitBlt(drawDC, m_PosX - m_Width / 2, m_PosY - m_Height,
		m_Width, m_Height, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_PosX - m_Width / 2, m_PosY - m_Height,
		m_Width, m_Height, 0, 0, SRCPAINT);

	return;
}

void EnemyItem::DeadProc(_Inout_ HDC drawDC)
{
	if ((!m_IsEnemyExplode) && (m_IsEnemyDead))
	{
		Explode(drawDC);
		m_IsEnemyExplode = TRUE;
	}

	return;
}

void EnemyItem::Explode(_Inout_ HDC drawDC)
{
	EffectManager::getInstance()->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_PosX, m_PosY);
	return;
}