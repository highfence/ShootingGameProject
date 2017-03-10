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

EnemyItem::EnemyItem(
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_opt_ Vec flightVec,
	const _In_opt_ ::CreateOption flightOption)
	: 
	Enemy(createPos, flightType, flightVec)
{
	m_pSprite = new CImage;
	m_pShadeSprite = new CImage; 
	m_Option = flightOption;

	vRESULT retval = init();

	DebugLogPrint(retval, MESSAGES::creationFailed, _T(" from EnemyItem"));
}

const vRESULT EnemyItem::init()
{
	if (InitialImgLoad() != WELL_PERFORMED)
	{
		return ERROR_IMG_LOAD_FAILED;
	}

	m_FlightSpeed = enemyItemFlightSpeed;
	m_SpriteRange.x = enemyItemSpriteWidth;
	m_SpriteRange.y = enemyItemSpriteHeight;
	m_ColideRange = m_SpriteRange;
	m_Hp = enemyItemHp;
	m_MissileSpeed = enemyItemMissileSpeed;
	m_LoadedMissileNumber = enemyItemLoadedMissileNumber;
	LoadMissiles(ENEMY::MISSILE_SIZE::SMALL);
	return WELL_PERFORMED;
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
		UIManager::getInstance()->PlusScore(300);
		Explode();
		m_IsEnemyExplode = TRUE;
	}
	return;
}

void EnemyItem::Fire()
{
	const FLOAT fireFrequency = 1.5f;
	if (m_RecordAccTime > fireFrequency)
	{
		for (auto i : m_MissileVec)
		{
			if (i->Missile::Launch(ENEMY::MISSILE_TYPE::STRAIGHT_FIRE, m_Pos))
			{
				break;
			}
		}
		m_RecordAccTime = 0.f;
	}
	return;
}

void EnemyItem::Explode()
{
	if (m_Option.m_IsItemLaunched)
	{
		EnemyManager::getInstance()->MakeEnemyOneTime(
			ENEMY::ENEMY_TYPE::ITEM,
			m_Pos,
			ENEMY::FLIGHT_TYPE::FLY_ITEM,
			Vec(0, 1),
			nullptr);
	}
	EffectManager::getInstance()->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos);
	return;
}

const vRESULT EnemyItem::InitialImgLoad()
{
	if (m_Option.m_IsItemLaunched == TRUE)
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