#include "stdafx.h"
#include "Boss.h"
#include "EnemyMissile.h"
#include "EffectManager.h"
#include "UIManager.h"
#include "ExplodeBig.h"
#include "ExplodeHit.h"

const std::wstring enemyBossSpritePath = _T("../Resources/Boss/");
const std::wstring enemyBossShadePath = _T("../Resources/Boss/BossShade.png");
const std::wstring enemyBossFileExtension = _T(".png");
const INT enemyBossWidth = 122;
const INT enemyBossHeight = 101;
const INT enemyBossHp = 2000;
const INT enemyBossLoadedMissileNumber = 60;
const INT enemyBossFrameInterval = 5;
const INT enemyBossMaxFrame = 355;

EnemyBoss::EnemyBoss()
{
	Init();
}

void EnemyBoss::Init()
{
	m_EnemyType = ENEMY::ENEMY_TYPE::ENEMY_BOSS;
	m_SpriteRange.x = enemyBossWidth;
	m_SpriteRange.y = enemyBossHeight;
	m_ColideRange = m_SpriteRange;
	m_Hp = enemyBossHp;
	m_FrameIntervalNum = enemyBossFrameInterval;
	m_MaxFrameNum = enemyBossMaxFrame;
	m_LoadedMissileNumber = enemyBossLoadedMissileNumber;
	LoadMissiles(ENEMY::MISSILE_SIZE::EXTRA);
	InitialImgLoad();

	return;
}

void EnemyBoss::InitialImgLoad()
{
	ImgLoad(m_pSprite, enemyBossSpritePath, m_FrameNum, enemyBossFileExtension, FALSE);
	/* 보스의 Shade는 변하지 않으므로, 그냥 Load로 처리 */
	m_pShadeSprite->Load(enemyBossShadePath.c_str());
}

EnemyBoss::~EnemyBoss()
{

}

void EnemyBoss::Draw(_Inout_ HDC drawDC)
{
#pragma warning(push)
#pragma warning(disable : 4244)

	std::wstring hpLabel = _T("BOSS remainHp : ") + std::to_wstring(m_Hp);
	std::wstring lossPercent = _T("Lost HP Percent : ") + std::to_wstring(m_LostedHpPercent);
	std::wstring colorProgress = _T("Color Progress : ") + std::to_wstring(m_ColorChangeProgress);
	std::wstring frameNum = _T("Frame Num : ") + std::to_wstring(m_FrameNum);

	TextOut(drawDC, 10, 110, hpLabel.c_str(), wcslen(hpLabel.c_str()));
	TextOut(drawDC, 10, 130, lossPercent.c_str(), wcslen(lossPercent.c_str()));
	TextOut(drawDC, 10, 150, colorProgress.c_str(), wcslen(colorProgress.c_str()));
	TextOut(drawDC, 10, 170, frameNum.c_str(), wcslen(frameNum.c_str()));

	m_pShadeSprite->BitBlt(drawDC, m_Pos.x - m_SpriteRange.x / 2, m_Pos.y - m_SpriteRange.y / 2,
		m_SpriteRange.x, m_SpriteRange.y, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_Pos.x - m_SpriteRange.x / 2, m_Pos.y - m_SpriteRange.y / 2,
		m_SpriteRange.x, m_SpriteRange.y, 0, 0, SRCPAINT);

#pragma warning(pop)
	return;
}

/*
	Enemy::CalcProc 오버라이딩
	기본적으로는 같고, 추가적으로는 Hp에 따라 이미지를 바꿔주는 역할을 수행한다.
*/
void EnemyBoss::CalcProc(const _In_ FLOAT deltaTime)
{
	Enemy::CalcProc(deltaTime);
	MakeBossColorAccordWithHp();

	return;
}

/*
	보스 체력의 남은 잔량을 확인하고 그에 맞추어 색을 바꿔준다.
*/
void EnemyBoss::MakeBossColorAccordWithHp()
{
	/* Divide by Zero 방지 */
	if (!enemyBossHp || !m_MaxFrameNum || !m_FrameIntervalNum)
	{
		return;
	}

	m_LostedHpPercent = (enemyBossHp - m_Hp) / enemyBossHp;
	m_ColorChangeProgress = m_FrameNum / m_MaxFrameNum;
	BOOL isImgChangedAtLeastOnce = FALSE;

	while (m_LostedHpPercent> m_ColorChangeProgress)
	{
		m_FrameNum += m_FrameIntervalNum;
		m_ColorChangeProgress = m_FrameNum / m_MaxFrameNum;
		isImgChangedAtLeastOnce = TRUE;
	}

	/* 이미지가 한 번이라도 바뀌어야 한다면, */
	if (isImgChangedAtLeastOnce)
	{
		ImgLoad(m_pSprite, enemyBossSpritePath, m_FrameNum, enemyBossFileExtension, TRUE);
	}

	return;
}

/*
	보스가 터질 경우 여러 개의 폭발을 일으키고 싶다.
*/
void EnemyBoss::Explode()
{
	const INT bossExplodeNumber = 20;
	std::mt19937 rng((unsigned int)time(NULL));
	std::uniform_real_distribution<float> dist(-enemyBossWidth / 2, enemyBossWidth / 2);

	EffectManager* effectManager = EffectManager::GetInstance();
	for (int i = 0; i < bossExplodeNumber; ++i)
	{
		float explodeX = dist(rng);
		float explodeY = dist(rng);
		Vec explodeVec = m_Pos + Vec(explodeX, explodeY);

		effectManager->MakeEffect<ExplodeBig>(m_Pos);
	}

	return;
}

void EnemyBoss::DeadProc()
{
	if ((!m_IsEnemyExplode) && (m_IsEnemyDead))
	{
		// TODO :: 점수 Definition에 정리해 놓기.
		UIManager::GetInstance()->PlusScore(10000);
		Explode();
		this->m_IsEnemyExplode = TRUE;
	}

	return;
}

void EnemyBoss::GetDamage(
	const _In_ INT damage,
	const _In_ Vec playerMissileVec)
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