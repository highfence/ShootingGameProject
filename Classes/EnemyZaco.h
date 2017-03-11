#pragma once
#include "Enemy.h"

class EnemyZaco : public Enemy
{
public :
	EnemyZaco();
	EnemyZaco(
		const _In_ Vec createPos,
		const _In_ INT flightType,
		const _In_opt_ Vec flightVec,
		const _In_opt_::CreateOption flightOption
	);
	~EnemyZaco() override;

	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;
	void Fire() override;

private :

	const vRESULT init();
	const vRESULT InitialImgLoad();
};