#pragma once
#include "Enemy.h"

class EnemyMine : public Enemy
{
public :
	EnemyMine();
	~EnemyMine() override;

	void CalcProc(const _In_ FLOAT) override;
	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;

private :
	void Init();
	void InitialImgLoad();
	void MakeSpriteNextThing();

	FLOAT m_RecordFrameTime = 0.f;
	FLOAT m_TimePerOneFrame = 0.15f;
	INT m_FrameNum = 1;
	INT m_MaxFrameNum = 9;

};