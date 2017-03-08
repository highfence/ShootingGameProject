#include "stdafx.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "EnemyZaco.h"

const std::wstring enemyZacoSpritePath = _T("../Resources/EnemyZaco.png");
const std::wstring enemyZacoShadePath = _T("../Resources/EnemyZacoS.png");
const INT enemyZacoSpriteWidth = 32;
const INT enemyZacoSpriteHeight = 32;
const INT enemyZacoHp = 1;
const FLOAT enemyZacoMissileSpeed = 450.f;
const INT enemyZacoLoadedMissileNumber = 5;
const FLOAT enemyZacoColideCorrectionRange = 15;

EnemyZaco::EnemyZaco(
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_opt_ Vec flightVec,
	const _In_opt_ ::CreateOption flightOption)
	: Enemy(createPos, flightType, flightVec)
{
	m_pSprite = new CImage;
	m_pShadeSprite = new CImage;
	m_Option = flightOption;

	vRESULT retval = init();

	DebugLogPrint(retval, MESSAGES::creationFailed, _T("from EnemyZaco"));
}

/*
	Width, Height, Hp, MissileSpeed를 지정해주고
	이미지 로드, 미사일 적재등을 초기화 해주는 함수.
*/
const vRESULT EnemyZaco::init()
{
	m_SpriteRange.x = enemyZacoSpriteWidth;
	m_SpriteRange.y = enemyZacoSpriteHeight;
	m_ColideRange = m_SpriteRange + enemyZacoColideCorrectionRange;
	m_Hp = enemyZacoHp;
	m_MissileSpeed = enemyZacoMissileSpeed;

	if (InitialImgLoad() != WELL_PERFORMED)
	{
		return ERROR_IMG_LOAD_FAILED;
	}

	m_LoadedMissileNumber = enemyZacoLoadedMissileNumber;
	LoadMissiles(ENEMY::MISSILE_SIZE::SMALL);
	return WELL_PERFORMED;
}

EnemyZaco::~EnemyZaco()
{
}

void EnemyZaco::Draw(_Inout_ HDC drawDC)
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

void EnemyZaco::Explode()
{
	EffectManager::getInstance()->MakeEffect(
		EFFECT::EFFECT_TYPE::EXPLODE_LIGHT,
		m_Pos,
		m_Option.m_InitSpeed,
		m_FlightVec);

	return;
}

void EnemyZaco::DeadProc()
{
	if ((!m_IsEnemyExplode) && (m_IsEnemyDead))
	{
		Explode();
		m_IsEnemyExplode = TRUE;
	}
	return;
}

void EnemyZaco::Fire()
{
	return;
}


/*
	초기화시에 이미지 로드를 담당하는 함수.
	(init에서 호출)
*/
const vRESULT EnemyZaco::InitialImgLoad()
{
	if (m_pSprite->Load(enemyZacoSpritePath.c_str()) == E_FAIL)
	{
		return ERROR_IMG_LOAD_FAILED;
	}
	if (m_pShadeSprite->Load(enemyZacoShadePath.c_str()) == E_FAIL)
	{
		return ERROR_IMG_LOAD_FAILED;
	}

	return WELL_PERFORMED;
}