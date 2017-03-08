#include "stdafx.h"
#include "EnemyHandShot.h"
#include "EffectManager.h"
#include "EnemyManager.h"
#include "EnemyMissile.h"

const std::wstring enemyHandShotSpritePath = _T("../Resources/EnemyHandShot.png");
const std::wstring enemyHandShotShadePath = _T("../Resources/EnemyHandShotS.png");
const INT enemyHandShotSpriteWidth = 90;
const INT enemyHandShotSpriteHeight = 74;
const INT enemyHandShotHp = 320;
const INT enemyHandShotLoadedMissileNumber = 30;

EnemyHandShot::EnemyHandShot(
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_opt_ Vec flightVec,
	const _In_opt_::CreateOption flightOption)
	:
	Enemy(createPos, flightType, flightVec)
{
	m_pSprite = new CImage;
	m_pShadeSprite = new CImage;
	m_Option = flightOption;

	vRESULT retval = init();

	DebugLogPrint(retval, MESSAGES::creationFailed, _T(" from EnemyHandShot"));
}

const vRESULT EnemyHandShot::init()
{
	if (InitialImgLoad() != WELL_PERFORMED)
	{
		return ERROR_IMG_LOAD_FAILED;
	}

	m_SpriteRange.x = enemyHandShotSpriteWidth;
	m_SpriteRange.y = enemyHandShotSpriteHeight;
	m_ColideRange = m_SpriteRange;
	m_Hp = enemyHandShotHp;
	m_LoadedMissileNumber = enemyHandShotLoadedMissileNumber;
	LoadMissiles(ENEMY::MISSILE_SIZE::MEDIUM);
	return WELL_PERFORMED;
}

EnemyHandShot::~EnemyHandShot()
{
	delete m_pSprite;
	delete m_pShadeSprite;
}

void EnemyHandShot::Draw(_Inout_ HDC drawDC)
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

void EnemyHandShot::DeadProc()
{
	if ((!m_IsEnemyExplode) && (m_IsEnemyDead))
	{
		Explode();
		m_IsEnemyExplode = TRUE;
	}
	return;
}

void EnemyHandShot::Fire()
{
	// TODO :: N-Way탄 구현.
	return;
}

void EnemyHandShot::Explode()
{
	// TODO :: 큰 폭발 구현.
	return;
}

const vRESULT EnemyHandShot::InitialImgLoad()
{
	if (m_pSprite->Load(enemyHandShotSpritePath.c_str()) == E_FAIL)
	{
		return ERROR_IMG_LOAD_FAILED;
	}
	if (m_pShadeSprite->Load(enemyHandShotShadePath.c_str()) == E_FAIL)
	{
		return ERROR_IMG_LOAD_FAILED;
	}
	return WELL_PERFORMED;
}

/*
	EnemyHandShot이 맞았을 경우 특별한 이펙트를 발생시키기 위해 오버라이딩.
*/
const vRESULT EnemyHandShot::GetDamage(const _In_ INT damage, const _In_ Vec playerMissileVec)
{
	m_Hp -= damage;

	if (m_Hp <= 0)
	{
		m_IsEnemyDead = TRUE;
	}
	else
	{
		EffectManager::getInstance()->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_HIT, Vec(playerMissileVec.x + rand() % 10 - 5, m_Pos.y + m_SpriteRange.y / 2), 150, Vec(0, -1));
	}

	return WELL_PERFORMED;
}