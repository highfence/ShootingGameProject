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
		m_Height = enemyMissileSmallHeigth;
	}
	return;
}

void EnemyMissile::init()
{
	return;
}

BOOL EnemyMissile::CheckColideWithPlayer()
{
	Player& playerInfo = EnemyManager::getInstance()->getPlayerInfo();
	FLOAT playerCorrectionPixel = playerInfo.GetCollisionPixel();
	FLOAT playerPosX;
	FLOAT playerPosY;
	playerInfo.GetPosition(&playerPosX, &playerPosY);

	auto x0 = m_PosX - m_Width / 2;
	auto y0 = m_PosY - m_Height / 2;
	auto x1 = m_PosX + m_Width / 2;
	auto y1 = m_PosY + m_Height / 2;
	auto mx0 = playerPosX - playerCorrectionPixel;
	auto my0 = playerPosY - playerCorrectionPixel;
	auto mx1 = playerPosX + playerCorrectionPixel;
	auto my1 = playerPosY + playerCorrectionPixel;

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

	m_PosX += unitVecX * speed * dt;
	m_PosY += unitVecY * speed * dt;

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