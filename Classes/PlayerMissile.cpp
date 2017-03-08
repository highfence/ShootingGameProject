#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "PlayerMissile.h"

using namespace PLAYER;

PlayerMissile::PlayerMissile()
{
	m_Damage = playerMissileDamageArray[0];
	m_Width = playerMissileWidthArray[0];
	m_Height = playerMissileHeightArray[0];
	init();
}

void PlayerMissile::init()
{
	InitialImgLoad();
	return;
}

PlayerMissile::~PlayerMissile()
{

}

/*
	InitialImgLoad
	init에서 호출. 
	맨 처음 이미지를 로드해주는 함수.
*/
INT PlayerMissile::InitialImgLoad()
{
	ImgLoad(m_pShapeSprite, playerMissileShape, 1, fileExtension, FALSE);
	ImgLoad(m_pSprite, playerMissile, 1, fileExtension, FALSE);

	return WELL_PERFORMED;
}

void PlayerMissile::Fly(
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

BOOL PlayerMissile::CheckColide()
{
	auto EnemyVec = EnemyManager::getInstance()->getEnemyList();

	for (auto i : EnemyVec)
	{
		if (IsColideWithEnemy(i->m_Pos.x, i->m_Pos.y, i->m_SpriteRange.x, i->m_SpriteRange.y))
		{
			// 충돌 처리.
			i->GetDamage(m_Damage);

			// 충돌 후 미사일 소멸
			m_IsMissileLaunched = FALSE;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL PlayerMissile::IsColideWithEnemy(
	const _In_ FLOAT enemyPosX,
	const _In_ FLOAT enemyPosY,
	const _In_ FLOAT enemyWidth,
	const _In_ FLOAT enemyHeight)
{
	FLOAT enemyX1 = enemyPosX - enemyWidth / 2 + colideCorrectionPixel;
	FLOAT enemyY1 = enemyPosY - enemyHeight / 2 + colideCorrectionPixel;
	FLOAT enemyX2 = enemyPosX + enemyWidth / 2 - colideCorrectionPixel;
	FLOAT enemyY2 = enemyPosY + enemyHeight / 2 - colideCorrectionPixel;

	FLOAT thisX1 = m_Pos.x - m_Width / 2;
	FLOAT thisY1 = m_Pos.y - m_Height / 2;
	FLOAT thisX2 = m_Pos.x + m_Width / 2;
	FLOAT thisY2 = m_Pos.y + m_Height / 2;

	if (!(thisX2 < enemyX1 || enemyX2 < thisX1 || thisY2 < enemyY1 || enemyY2 < thisY1))
	{
		return TRUE;
	}

	return FALSE;
}

/*
	ChangeMissileTier
	미사일의 티어를 받아 이미지와 데미지를 바꾸는 함수.
*/
BOOL PlayerMissile::ChangeMissileTier(const _In_ INT tierNumber)
{
	ImgLoad(m_pShapeSprite, playerMissileShape, tierNumber, fileExtension, TRUE);
	ImgLoad(m_pSprite, playerMissile, tierNumber, fileExtension, TRUE);
	m_Damage = playerMissileDamageArray[tierNumber - 1];
	m_Width = playerMissileWidthArray[tierNumber - 1];
	m_Height = playerMissileHeightArray[tierNumber - 1];

	return TRUE;
}