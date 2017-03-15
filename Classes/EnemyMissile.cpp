#include "stdafx.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EnemyMissile.h"

using namespace ENEMY;

EnemyMissile::EnemyMissile(ENEMY::MISSILE_SIZE missileSize)
{
	if (missileSize == ENEMY::MISSILE_SIZE::SMALL)
	{
		m_pSprite->Load(enemyMissileSmall.c_str());
		m_pShapeSprite->Load(enemyMissileShadeSmall.c_str());
		m_Width = enemyMissileSmallWidth;
		m_Height = enemyMissileSmallHeight;
	}
	else if (missileSize == ENEMY::MISSILE_SIZE::MEDIUM)
	{
		m_pSprite->Load(enemyMissileMedium.c_str());
		m_pShapeSprite->Load(enemyMissileShadeMedium.c_str());
		m_Width = enemyMissileMediumWidth;
		m_Height = enemyMissileMediumHeight;
	}
	init();
	return;
}

void EnemyMissile::init()
{
	RegisterFunctionPointer();
	return;
}

/*
	함수 포인터를 등록시켜주는 함수.
*/
void EnemyMissile::RegisterFunctionPointer()
{
	m_pMissileFlyHandler[MISSILE_TYPE::STRAIGHT_FIRE] = &EnemyMissile::MissileFlyNormal;
	m_pMissileFlyHandler[MISSILE_TYPE::ACCELERATE_FIRE] = &EnemyMissile::MissileAccelerate;
	return;
}

/*
	FireOption에 등록되어있는대로 일정하게 날아가는 미사일.
*/
BOOL EnemyMissile::MissileFlyNormal(const FLOAT deltaTime)
{
	FireOption op = GetOption();
	Vec missileVec = op.GetMissileVec();
	Fly(deltaTime, missileVec.x, missileVec.y, op.GetMissileSpeed());

	return TRUE;
}

/*
	일정하게 가/감속 하는 스타일의 미사일.
*/
BOOL EnemyMissile::MissileAccelerate(const FLOAT deltaTime)
{
	FireOption op = GetOption();
	Vec missileVec = op.GetMissileVec();
	FLOAT initSpeed = op.GetMissileSpeed();
	FLOAT accSpeed = op.GetAccMissileSpeed();
	FLOAT currentSpeed = initSpeed + accSpeed * m_AccTime;
	Fly(deltaTime, missileVec.x, missileVec.y, currentSpeed);
	
	return TRUE;
}

BOOL EnemyMissile::CheckColideWithPlayer()
{
	Player& playerInfo = EnemyManager::getInstance()->getPlayerInfo();
	FLOAT playerCorrectionPixel = playerInfo.GetCollisionPixel();
	Vec playerPos;
	playerInfo.GetPosition(&playerPos);

	auto x0 = m_Pos.x - m_Width / 2;
	auto y0 = m_Pos.y - m_Height / 2;
	auto x1 = m_Pos.x + m_Width / 2;
	auto y1 = m_Pos.y + m_Height / 2;
	auto mx0 = playerPos.x - playerCorrectionPixel;
	auto my0 = playerPos.y - playerCorrectionPixel;
	auto mx1 = playerPos.x + playerCorrectionPixel;
	auto my1 = playerPos.y + playerCorrectionPixel;

	if (!(x1 <= mx0 || mx1 <= x0 || y1 <= my0 || my1 <= y0))
	{
		playerInfo.PlayerDamaged();
		return TRUE;
	}
	return FALSE;
}

EnemyMissile::~EnemyMissile()
{

}

void EnemyMissile::CalcProc(const FLOAT deltaTime)
{
	// 미사일이 아직 발사되지 않은 경우 바로 리턴.
	if (!m_IsMissileLaunched)
	{
		return;
	}

	// 시간 누적
	m_AccTime += deltaTime;

	// 충돌 검사.
	CheckColideWithPlayer();

	// 옵션 호출 및 이상할 경우 바로 리턴.
	FireOption op = GetOption();
	if (!op.GetIsOptionCanUse())
	{
		return;
	}

	(this->*m_pMissileFlyHandler[op.GetMissileType()])(deltaTime);
	return;
}

void EnemyMissile::Fly(
	const _In_ FLOAT dt,
	const _In_ FLOAT vecX,
	const _In_ FLOAT vecY,
	const _In_ FLOAT speed)
{
	if (!m_IsMissileLaunched)
	{
		return;
	}

	FLOAT unitVecX;
	FLOAT unitVecY;

	GetUnitVec(vecX, vecY, &unitVecX, &unitVecY);

	m_Pos.x += unitVecX * speed * dt;
	m_Pos.y += unitVecY * speed * dt;

	if (!IsMissileOnDisplay())
	{
		m_IsMissileLaunched = FALSE;
	}

	return;
}

// EnemyMissile에게 Player의 위치 정보를 알려주는 함수. (충돌 판정을 위해)
void EnemyMissile::SetPlayerPos(
	const _In_ FLOAT playerPosX,
	const _In_ FLOAT playerPosY)
{
	m_PlayerPosX = playerPosX;
	m_PlayerPosY = playerPosY;

	return;
}

/*
	Initialize with MissileOption (Launch Func Overloading)
	Using in EnemyMissile
*/
BOOL EnemyMissile::Launch(
	const _In_ Vec createVec,
	const _In_ FireOption& option)
{
	if (m_IsMissileLaunched)
	{
		return FALSE;
	}

	m_IsMissileLaunched = TRUE;
	m_Pos = createVec;
	m_Option = option;
	m_MissileType = option.GetMissileType();

	return TRUE;
}

FireOption EnemyMissile::GetOption() const
{
	return m_Option;
}

void EnemyMissile::SetFireOption(const FireOption & op)
{
	m_Option = op;
}
