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