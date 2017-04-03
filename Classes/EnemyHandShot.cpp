#include "stdafx.h"
#include "EnemyHandShot.h"
#include "EffectManager.h"
#include "EnemyManager.h"
#include "UIManager.h"
#include "ExplodeSmoke.h"
#include "ExplodeHit.h"
#include "ExplodeBig.h"
#include "EnemyMissile.h"

const std::wstring enemyHandShotSpritePath = _T("../Resources/EnemyHandShot.png");
const std::wstring enemyHandShotShadePath = _T("../Resources/EnemyHandShotS.png");
const INT enemyHandShotSpriteWidth = 90;
const INT enemyHandShotSpriteHeight = 74;
const INT enemyHandShotHp = 320;
const INT enemyHandShotLoadedMissileNumber = 40;

const FLOAT fireIntevalDelayTime = 0.3f;
const FLOAT fireInitialDelayTime = 1.5f;
const FLOAT degreeOfOddWayLaunch = 22.5f;
const FLOAT degreeOfEvenWayLaunch = 22.5f;

EnemyHandShot::EnemyHandShot()
	: 
	Enemy(),
	m_IsLaunchRightHand(TRUE),
	m_ShotNum(0)
{
	m_RightHandPos = Vec(32, 32);
	m_LeftHandPos = Vec(-32, 32);
	Init();
}


void EnemyHandShot::Init()
{
	if (InitialImgLoad() != WELL_PERFORMED)
	{
		return;
	}

	m_EnemyType = ENEMY::ENEMY_TYPE::ENEMY_HAND_SHOT;
	m_SpriteRange.x = enemyHandShotSpriteWidth;
	m_SpriteRange.y = enemyHandShotSpriteHeight;
	m_ColideRange = m_SpriteRange;
	m_LoadedMissileNumber = enemyHandShotLoadedMissileNumber;
	LoadMissiles(ENEMY::MISSILE_SIZE::MEDIUM);
	return;
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
		UIManager::GetInstance()->PlusScore(2700);
		Explode();
		this->m_IsEnemyExplode = TRUE;
	}
	return;
}

/*
	RightHand에서 발사할 것인지 LeftHand에서 발사할 것인지 판단하고 발사 위치를 반환해주는 함수.
*/
Vec EnemyHandShot::GetLaunchPos() const
{
	if (m_IsLaunchRightHand)
	{
		return Vec(m_Pos.x + m_RightHandPos.x, m_Pos.y + m_RightHandPos.y);
	}

	return Vec(m_Pos.x + m_LeftHandPos.x, m_Pos.y + m_LeftHandPos.y);
}


void EnemyHandShot::Explode()
{
	EffectManager::GetInstance()->MakeEffect<ExplodeBig>(m_Pos);
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
void EnemyHandShot::GetDamage(const _In_ INT damage, const _In_ Vec playerMissileVec)
{
	m_Hp -= damage;

	if (m_Hp <= 0)
	{
		m_IsEnemyDead = TRUE;
	}
	else
	{
		Vec hitEffectVec = Vec(playerMissileVec.x + rand() % 10 - 5, m_Pos.y + m_SpriteRange.y / 2);
		EffectManager::GetInstance()->MakeEffectWithFloat<ExplodeHit>(
			hitEffectVec, 150, Vec(0, -1));
	}
}

/*
	Enemy::CalcLaunchPos 오버라이딩. 어느 손에서 발사할지 결정해준다. 
*/
void EnemyHandShot::CalcLaunchPos()
{
	auto opt = GetFireOption();
	auto data = opt.GetNwayShotData();

	// NwayShot을 쏘는 경우
	if (data != nullptr)
	{
		if (data.RecordShotTimes == 0)
		{
			ChangeHand();
		}
	}
	// 그렇지 않은 경우.
	else
	{
		if (m_ShootedMissileNumber == opt.GetMissileShotNumber())
		{
			ChangeHand();
		}
	}

	m_LaunchPos = GetLaunchPos();
	return;
}

/*
	손을 바꾸어주는 함수.
*/
void EnemyHandShot::ChangeHand()
{
	if (m_IsLaunchRightHand)
	{
		m_IsLaunchRightHand = FALSE;
	}
	else
	{
		m_IsLaunchRightHand = TRUE;
	}
	return;

}