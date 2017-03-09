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

const FLOAT fireIntevalDelayTime = 0.3f;
const FLOAT fireInitialDelayTime = 1.5f;
const FLOAT degreeOfOddWayLaunch = 22.5f;
const FLOAT degreeOfEvenWayLaunch = 22.5f;

EnemyHandShot::EnemyHandShot(
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_opt_ Vec flightVec,
	const _In_opt_::CreateOption flightOption)
	:
	Enemy(createPos, flightType, flightVec),
	m_IsLaunchRightHand(TRUE),
	m_ShotNum(0)
{
	m_pSprite = new CImage;
	m_pShadeSprite = new CImage;
	m_Option = flightOption;
	m_RightHandPos = Vec(32, 32);
	m_LeftHandPos = Vec(-32, 32);

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
	if (m_AccTime > fireInitialDelayTime)
	{
		if (m_ShotNum == 0 && (m_RecordAccTime > fireInitialDelayTime))
		{
			NWayBulletLaunch(5);
			m_RecordAccTime = 0.f;
			++m_ShotNum;
		}
		else if (m_ShotNum == 1 && (m_RecordAccTime > fireIntevalDelayTime))
		{
			NWayBulletLaunch(6);
			m_RecordAccTime = 0.f;
			++m_ShotNum;
		}
		else if (m_ShotNum == 2 && (m_RecordAccTime > fireIntevalDelayTime))
		{
			NWayBulletLaunch(5);
			m_RecordAccTime = 0.f;
			++m_ShotNum;
		}
		else if (m_ShotNum == 3)
		{
			m_ShotNum = 0;
			if (m_IsLaunchRightHand)
			{
				m_IsLaunchRightHand = FALSE;
			}
			else
			{
				m_IsLaunchRightHand = TRUE;
			}
		}
	}

	return;
}

const vRESULT EnemyHandShot::NWayBulletLaunch(const _In_ INT bulletNumber)
{
	Vec LaunchPos;
	Vec ShotVec;
	if (m_IsLaunchRightHand)
	{
		LaunchPos = Vec(m_Pos.x + m_RightHandPos.x, m_Pos.y + m_RightHandPos.y);
	}
	else
	{
		LaunchPos = Vec(m_Pos.x + m_LeftHandPos.x, m_Pos.y + m_LeftHandPos.y);
	}

	// TODO :: 중복코드 정리.
	// 홀수일 경우.
	INT IsBulletNumberOdd = bulletNumber % 2;
	if (IsBulletNumberOdd == TRUE)
	{
		INT shotNumber = (bulletNumber - 1) / 2 + 1;
		for (int i = 0; i < shotNumber; ++i)
		{
			RotateVec(i * degreeOfOddWayLaunch, 0.f, 1.f, ShotVec.x, ShotVec.y);
			MissileOption option1(ShotVec, 300.f, AIM_FIRE, MEDIUM);
			MissileOption option2(ShotVec.GetXSymmetryVec(), 300.f, AIM_FIRE, MEDIUM);
			EnemyMissile* leftBullet = GetLaunchableMissile();
			if (leftBullet != nullptr)
			{
				leftBullet->Launch(LaunchPos, option1);
			}

			EnemyMissile* rightBullet = GetLaunchableMissile();
			if (rightBullet != nullptr)
			{
				rightBullet->Launch(LaunchPos, option2);
			}
		}
	}
	// 짝수일 경우.
	else
	{
		INT shotNumber = bulletNumber / 2;
		for (int i = 0; i < shotNumber; ++i)
		{
			RotateVec(i * degreeOfEvenWayLaunch + 12.25f, 0.f, 1.f, ShotVec.x, ShotVec.y);
			MissileOption option1(ShotVec, 300.f, AIM_FIRE, MEDIUM);
			MissileOption option2(ShotVec.GetXSymmetryVec(), 300.f, AIM_FIRE, MEDIUM);
			EnemyMissile* leftBullet = GetLaunchableMissile();
			if (leftBullet != nullptr)
			{
				leftBullet->Launch(LaunchPos, option1);
			}

			EnemyMissile* rightBullet = GetLaunchableMissile();
			if (rightBullet != nullptr)
			{
				rightBullet->Launch(LaunchPos, option2);
			}
		}
	}

	return WELL_PERFORMED;
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