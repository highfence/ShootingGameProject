#pragma once
#include "Enemy.h"

class EnemyBoss : public Enemy
{
public :
	EnemyBoss();
	~EnemyBoss() override;

	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;
	void CalcProc(const _In_ FLOAT) override;

	void GetDamage(const _In_ INT, const _In_ Vec);

private :

	void Init();
	void InitialImgLoad();
	void MakeBossColorAccordWithHp();

	INT m_FrameNum = 0;
	INT m_FrameIntervalNum = 0;
	INT m_MaxFrameNum = 0;
	DOUBLE m_LostedHpPercent = 0.f;
	DOUBLE m_ColorChangeProgress = 0.f;
};