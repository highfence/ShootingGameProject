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
	Init();
}

void PlayerMissile::Init()
{
	InitialImgLoad();
	return;
}

PlayerMissile::~PlayerMissile()
{

}

/*
	init에서 호출. 
	맨 처음 이미지를 로드해주는 함수.
*/
INT PlayerMissile::InitialImgLoad()
{
	ImgLoad(m_pShapeSprite, playerMissileShape, 1, fileExtension, FALSE);
	ImgLoad(m_pSprite, playerMissile, 1, fileExtension, FALSE);

	return WELL_PERFORMED;
}

/*
	입력받은 방향과 속도로 자신의 위치를 계산하는 함수.
*/
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

/*
	충돌이 일어났는지 확인하고 일어났다면 데미지를 주고 비행을 끝낸다.
*/
BOOL PlayerMissile::CheckColide()
{
	Enemy* i = EnemyManager::GetInstance()->FindEnemyColideWith(m_Pos, Vec(m_Width, m_Height));
	if (i != nullptr)
	{
		// 충돌 처리.
		i->GetDamage(m_Damage, m_Pos);

		// 충돌 후 미사일 소멸
		m_IsMissileLaunched = FALSE;
		return TRUE;
	}

	return FALSE;
}

/*
	// TODO :: 미사일 이미지 로드하지 말고, 메모리 풀 잡아놓고 하기.
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