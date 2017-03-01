#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "PlayerMissile.h"

using namespace PLAYER;

PlayerMissile::PlayerMissile()
{
	m_Damage = playerMissileDamageOneTier;
	m_Width = playerMissileWidth;
	m_Height = playerMissileHeight;
	init();
}

void PlayerMissile::init()
{
	m_pShapeSprite->Load(playerShape.c_str());
	m_pSprite->Load(playerMissile.c_str());
	return;
}

PlayerMissile::~PlayerMissile()
{

}

void PlayerMissile::Fly(const _In_ FLOAT dt, const _In_ FLOAT vecX, const _In_ FLOAT vecY, const _In_ FLOAT speed)
{
	if (!m_IsMissileLaunched)
	{
		return;
	}

	FLOAT unitVecX;
	FLOAT unitVecY;

	GetUnitVec(vecX, vecY, &unitVecX, &unitVecY);

	m_PosX += unitVecX * speed * dt;
	m_PosY -= unitVecY * speed * dt;

	if (!IsMissileOnDisplay())
	{
		m_IsMissileLaunched = FALSE;
	}

	return;
}

BOOL PlayerMissile::CheckColide()
{
	auto EnemyVec = EnemyManager::getInstance()->getEnemyVec();

	for (auto i : EnemyVec)
	{
		if (IsColideWithEnemy(i->m_PosX, i->m_PosY, i->m_Width, i->m_Height))
		{
			// 面倒 贸府.
			i->GetDamage(m_Damage);

			// 面倒 饶 固荤老 家戈
			m_IsMissileLaunched = FALSE;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL PlayerMissile::IsColideWithEnemy(const _In_ FLOAT enemyPosX, const _In_ FLOAT enemyPosY, const _In_ FLOAT enemyWidth, const _In_ FLOAT enemyHeight)
{
	FLOAT enemyX1 = enemyPosX - enemyWidth / 2 + colideCorrectionPixel;
	FLOAT enemyY1 = enemyPosY - enemyHeight / 2 + colideCorrectionPixel;
	FLOAT enemyX2 = enemyPosX + enemyWidth / 2 - colideCorrectionPixel;
	FLOAT enemyY2 = enemyPosY + enemyHeight / 2 - colideCorrectionPixel;

	FLOAT thisX1 = m_PosX - m_Width / 2;
	FLOAT thisY1 = m_PosY - m_Height / 2;
	FLOAT thisX2 = m_PosX + m_Width / 2;
	FLOAT thisY2 = m_PosY + m_Height / 2;

	if (!(thisX2 < enemyX1 || enemyX2 < thisX1 || thisY2 < enemyY1 || enemyY2 < thisY1))
	{
		return TRUE;
	}

	return FALSE;
}