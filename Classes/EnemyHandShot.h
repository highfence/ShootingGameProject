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
	//void Fire() override;
	
	void GetDamage(const _In_ INT, const _In_ Vec);

private :

	const vRESULT init();
	const vRESULT InitialImgLoad();
	//const vRESULT NWayBulletLaunch(const _In_ INT);
	Vec GetLaunchPos() const;
	/*void FindBulletAndLaunch(
		const _In_ Vec,
		const _In_ FireOption);*/

	Vec m_RightHandPos;
	Vec m_LeftHandPos;
	BOOL m_IsLaunchRightHand;
	INT m_ShotNum;

};