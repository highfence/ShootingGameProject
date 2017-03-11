#pragma once
#include "Enemy.h"

/*
	EnemyHandShot
	�տ��� �̻����� ��°� Ư¡�� Enemy. ü���� ���� �����ص���.
*/

class EnemyHandShot : public Enemy
{
public :
	EnemyHandShot();
	EnemyHandShot(
		const _In_ Vec createPos,
		const _In_ INT flightType,
		const _In_opt_ Vec flightVec,
		const _In_opt_ ::CreateOption flightOption);
	~EnemyHandShot() override;

	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;
	void Fire() override;
	
	const vRESULT GetDamage(const _In_ INT, const _In_ Vec);

private :

	const vRESULT init();
	const vRESULT InitialImgLoad();
	const vRESULT NWayBulletLaunch(const _In_ INT);
	Vec GetLaunchPos() const;
	void FindBulletAndLaunch(
		const _In_ Vec,
		const _In_ MissileOption);

	Vec m_RightHandPos;
	Vec m_LeftHandPos;
	BOOL m_IsLaunchRightHand;
	INT m_ShotNum;

};