#include "stdafx.h"
#include "EnemyZaco.h"

const std::wstring enemyZacoSpritePath = _T("../Resources/EnemyZaco.png");
const std::wstring enemyZacoShadePath = _T("../Resources/EnemyZacoS.png");
const INT enemyZacoSpriteWidth = 32;
const INT enemyZacoSpriteHeight = 32;
const INT enemyZacoHp = 1;
const FLOAT enemyZacoMissileSpeed = 450.f;
const INT enemyZacoLoadedMissileNumber = 5;

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
	if (retval != WELL_PERFORMED)
	{
		std::wstring guideWord = MESSAGES::creationFailed + std::to_wstring(retval) + _T("(In Creation ENEMY ZACO)");
		OutputDebugString(guideWord.c_str());
		exit(0);
	}
}

EnemyZaco::~EnemyZaco()
{
}

void EnemyZaco::Draw(HDC)
{
	return;
}

void EnemyZaco::Explode()
{
	return;
}

void EnemyZaco::DeadProc()
{
	return;
}

void EnemyZaco::Fire()
{
	return;
}

/*
	Width, Height, Hp, MissileSpeed를 지정해주고
	이미지 로드, 미사일 적재등을 초기화 해주는 함수.
*/
const vRESULT EnemyZaco::init()
{
	m_Width = enemyZacoSpriteWidth;
	m_Height = enemyZacoSpriteHeight;
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