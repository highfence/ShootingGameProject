#include "stdafx.h"
#include "EffectManager.h"
#include "EnemyMine.h"
#include "EnemyManager.h"
#include "UIManager.h"

const std::wstring enemyMineSpritePath = _T("../Resources/Enemy/mine_11_0");
const std::wstring enemyMineItemSpritePath = _T("../Resources/Enemy/mine_12_0");
const std::wstring enemyMineShadePath = _T("../Resources/Enemy/mine_11_S0");
const std::wstring enemyMineFileExtension = _T(".png");
const INT enemyMineSpriteWidth = 48;
const INT enemyMineSpriteHeight = 48;
const INT enemyMineHp = 1;
const INT enemyMineLoadedMissileNumber = 5;

EnemyMine::EnemyMine()
{
	Init();
}

void EnemyMine::Init()
{
	m_EnemyType = ENEMY::ENEMY_TYPE::ENEMY_MINE;
	m_SpriteRange.x = enemyMineSpriteWidth;
	m_SpriteRange.y = enemyMineSpriteHeight;
	m_ColideRange = m_SpriteRange;
	m_Hp = enemyMineHp;

	InitialImgLoad();
	m_LoadedMissileNumber = enemyMineLoadedMissileNumber;
	LoadMissiles(ENEMY::MISSILE_SIZE::SMALL);
}

EnemyMine::~EnemyMine()
{
}

/*
	Mine�� ���ư��� �ִϸ��̼��� ���� CalcProc �����ε�.
	�Լ� ���ο��� Enemy::CalcProc ȣ��.
*/
void EnemyMine::CalcProc(const _In_ FLOAT dt)
{
	// ���� Enemy�� �Լ� ȣ��.
	this->Enemy::CalcProc(dt);
	
	// RecordFrameTime�� �ð� ����.
	m_RecordFrameTime += dt;

	// ������ �ð��� Frame�� ��е� �ð����� ũ�ٸ� ���� Frame ȣ��.
	if (m_RecordFrameTime > m_TimePerOneFrame)
	{
		MakeSpriteNextThing();
		m_RecordFrameTime = 0.f;
	}

	return;
}

void EnemyMine::Draw(_Inout_ HDC drawDC)
{
#pragma warning(push)
#pragma warning(disable : 4244)

	m_pShadeSprite->BitBlt(drawDC, m_Pos.x - m_SpriteRange.x / 2, m_Pos.y - m_SpriteRange.y / 2,
		m_SpriteRange.x, m_SpriteRange.y, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_Pos.x - m_SpriteRange.x / 2, m_Pos.y - m_SpriteRange.y / 2,
		m_SpriteRange.x, m_SpriteRange.y, 0, 0, SRCPAINT);

#pragma warning(pop)
}

void EnemyMine::Explode()
{
	if (m_CreateOption.GetIsItemLaunched() == TRUE)
	{
		EnemyManager::GetInstance()->ActivateEnemyOnce(m_Pos, CREATE_OPTION::ITEM_CREATE, FIRE_OPTION::NO_FIRE);
	}

	EffectManager::GetInstance()->MakeEffect(
		EFFECT::EFFECT_TYPE::EXPLODE_LIGHT,
		m_Pos,
		m_CreateOption.GetFlightSpeed(),
		m_CreateOption.GetFlightVec()
	);

	return;
}

void EnemyMine::DeadProc()
{
	if ((!m_IsEnemyExplode) && (m_IsEnemyDead))
	{
		UIManager::GetInstance()->PlusScore(75);
		Explode();
		this->m_IsEnemyExplode = TRUE;
	}
	return;
}

void EnemyMine::InitialImgLoad()
{
	ImgLoad(m_pSprite, enemyMineSpritePath, m_FrameNum, enemyMineFileExtension, FALSE);
	ImgLoad(m_pShadeSprite, enemyMineShadePath, m_FrameNum, enemyMineFileExtension, FALSE);

	return;
}

void EnemyMine::MakeSpriteNextThing()
{
	// FrameNum�� ���� Frame����.
	++m_FrameNum;
	if (m_FrameNum == m_MaxFrameNum + 1)
	{
		m_FrameNum = 1;
	}

	if (m_CreateOption.GetIsItemLaunched())
	{
		ImgLoad(m_pSprite, enemyMineItemSpritePath, m_FrameNum, enemyMineFileExtension, TRUE);
	}
	else
	{
		ImgLoad(m_pSprite, enemyMineSpritePath, m_FrameNum, enemyMineFileExtension, TRUE);
	}
	ImgLoad(m_pShadeSprite, enemyMineShadePath, m_FrameNum, enemyMineFileExtension, TRUE);
	return;
}