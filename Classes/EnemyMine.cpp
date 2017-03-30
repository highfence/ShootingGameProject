#include "stdafx.h"
#include "EffectManager.h"
#include "EnemyMine.h"
#include "UIManager.h"

const std::wstring enemyMineSpritePath = _T("../Resources/Enemy/mine_11_0");
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
	Mine의 돌아가는 애니메이션을 위해 CalcProc 오버로딩.
	함수 내부에서 Enemy::CalcProc 호출.
*/
void EnemyMine::CalcProc(const _In_ FLOAT dt)
{
	Enemy::CalcProc(dt);
	
	// RecordFrameTime에 시간 누적.
	m_RecordFrameTime += dt;

	// 누적된 시간이 Frame당 배분된 시간보다 크다면 다음 Frame 호출.
	if (m_RecordFrameTime > m_TimePerOneFrame)
	{
		
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
		m_IsEnemyExplode = TRUE;
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
	// FrameNum을 다음 Frame으로.
	m_FrameNum = (++m_FrameNum) % (m_MaxFrameNum + 1);

	ImgLoad(m_pSprite, enemyMineSpritePath, m_FrameNum, enemyMineFileExtension, TRUE);
	ImgLoad(m_pShadeSprite, enemyMineShadePath, m_FrameNum, enemyMineFileExtension, TRUE);
	return;
}