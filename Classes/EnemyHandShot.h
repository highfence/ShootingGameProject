#pragma once
#include "Enemy.h"

/*
	EnemyHandShot
	손에서 미사일을 쏘는게 특징인 Enemy. 체력을 높게 설정해두자.
*/

class EnemyHandShot : public Enemy
{
public :
	EnemyHandShot();
	~EnemyHandShot() override;

	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;
	
	void GetDamage(const _In_ INT, const _In_ Vec);
	
protected :

	void CalcLaunchPos() override;

private :

	void Init();
	const vRESULT InitialImgLoad();
	Vec GetLaunchPos() const;
	void ChangeHand();

	Vec m_RightHandPos;
	Vec m_LeftHandPos;
	BOOL m_IsLaunchRightHand;
	INT m_ShotNum;

};