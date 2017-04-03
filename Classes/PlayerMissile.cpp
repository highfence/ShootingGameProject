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
	init���� ȣ��. 
	�� ó�� �̹����� �ε����ִ� �Լ�.
*/
INT PlayerMissile::InitialImgLoad()
{
	ImgLoad(m_pShapeSprite, playerMissileShape, 1, fileExtension, FALSE);
	ImgLoad(m_pSprite, playerMissile, 1, fileExtension, FALSE);

	return WELL_PERFORMED;
}

/*
	�Է¹��� ����� �ӵ��� �ڽ��� ��ġ�� ����ϴ� �Լ�.
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
	�浹�� �Ͼ���� Ȯ���ϰ� �Ͼ�ٸ� �������� �ְ� ������ ������.
*/
BOOL PlayerMissile::CheckColide()
{
	Enemy* i = EnemyManager::GetInstance()->FindEnemyColideWith(m_Pos, Vec(m_Width, m_Height));
	if (i != nullptr)
	{
		// �浹 ó��.
		i->GetDamage(m_Damage, m_Pos);

		// �浹 �� �̻��� �Ҹ�
		m_IsMissileLaunched = FALSE;
		return TRUE;
	}

	return FALSE;
}

/*
	// TODO :: �̻��� �̹��� �ε����� ����, �޸� Ǯ ��Ƴ��� �ϱ�.
	ChangeMissileTier
	�̻����� Ƽ� �޾� �̹����� �������� �ٲٴ� �Լ�.
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