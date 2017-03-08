#pragma once
#include "Enemy.h"

/*
	EnemyHandShot
	�տ��� �̻����� ��°� Ư¡�� Enemy. ü���� ���� �����ص���.
*/

class EnemyHandShot : public Enemy
{
public :
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
};