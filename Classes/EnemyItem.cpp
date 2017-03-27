#include "stdafx.h"
#include "EnemyItem.h"
#include "EffectManager.h"
#include "EnemyManager.h"
#include "UIManager.h"
#include "EnemyMissile.h"

const std::wstring enemyItemSpritePath = _T("../Resources/EnemyItem.png");
const std::wstring enemyItemShadePath = _T("../Resources/EnemyItemShade.png");
const std::wstring enemyItemSpriteOnPath = _T("../Resources/EnemyItemOn.png");
const INT enemyItemSpriteWidth = 64;
const INT enemyItemSpriteHeight = 64;
const FLOAT enemyItemFlightSpeed = 300;
const INT enemyItemHp = 1;

EnemyItem::EnemyItem()
	: Enemy()
{
	Init();
}

void EnemyItem::Init()
{
	m_EnemyType = ENEMY::ENEMY_TYPE::ENEMY_ITEM;
	m_SpriteRange.x = enemyItemSpriteWidth;
	m_SpriteRange.y = enemyItemSpriteHeight;
	m_ColideRange = m_SpriteRange;
	m_Hp = enemyItemHp;
	m_LoadedMissileNumber = enemyItemLoadedMissileNumber;
	LoadMissiles(ENEMY::MISSILE_SIZE::SMALL);
	return;
}

EnemyItem::~EnemyItem()
{
	delete m_pSprite;
	delete m_pShadeSprite;
}

void EnemyItem::Draw(_Inout_ HDC drawDC)
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

void EnemyItem::DeadProc()
{
	if ((!m_IsEnemyExplode) && (m_IsEnemyDead))
	{
		UIManager::GetInstance()->PlusScore(300);
		Explode();
		m_IsEnemyExplode = TRUE;
	}
	return;
}
//
//void EnemyItem::Fire()
//{
//	const FLOAT fireFrequency = 1.5f;
//	if (m_RecordAccTime > fireFrequency)
//	{
//		for (auto i : m_MissileVec)
//		{
//			if (i->Missile::Launch(ENEMY::MISSILE_TYPE::STRAIGHT_FIRE, m_Pos))
//			{
//				break;
//			}
//		}
//		m_RecordAccTime = 0.f;
//	}
//	return;
//}

void EnemyItem::Activate(
	const Vec createPos,
	CreateOption & createOption,
	FireOption & fireOption)
{
	SetIsEnemyActivated(TRUE);
	SetIsEnemyDead(FALSE);
	SetCreateOption(createOption);
	SetFireOption(fireOption);
	m_Pos = createPos;
	m_Hp = createOption.GetEnemyHp();
	InitialImgLoad(TRUE);
}

void EnemyItem::Explode()
{
	if (m_CreateOption.GetIsItemLaunched())
	{
		CreateOption itemOption = CreateOption(100000, ITEM, FLY_ITEM, Vec(0, 0), 150.f, 0, NULL, FALSE);
		FireOption enemyNoFire = FireOption(FIRE_TYPE::FIRE_TYPE_NUM, MISSILE_TYPE::NONE, MISSILE_SIZE::SMALL, 0.f, 0.f, 0.f, Vec(0.f, 0.f), 0.f, 0.f, 0, 0.f, 0);
		EnemyManager::GetInstance()->ActivateEnemyOnce(m_Pos, itemOption, enemyNoFire);
	}
	EffectManager::GetInstance()->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos);
	return;
}

const vRESULT EnemyItem::InitialImgLoad(const _In_ BOOL isImgLoadedOnce)
{
	if (isImgLoadedOnce)
	{
		m_pShadeSprite->Destroy();
		m_pSprite->Destroy();
	}
	if (m_CreateOption.GetIsItemLaunched() == TRUE)
	{
		if (m_pSprite->Load(enemyItemSpriteOnPath.c_str()) == E_FAIL)
		{
			return ERROR_IMG_LOAD_FAILED;
		}
	}
	else
	{
		if (m_pSprite->Load(enemyItemSpritePath.c_str()) == E_FAIL)
		{
			return ERROR_IMG_LOAD_FAILED;
		}
	}
	if (m_pShadeSprite->Load(enemyItemShadePath.c_str()) == E_FAIL)
	{
		return ERROR_IMG_LOAD_FAILED;
	}
	return WELL_PERFORMED;
}