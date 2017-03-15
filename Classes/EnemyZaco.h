#pragma once
#include "Enemy.h"

class EnemyZaco : public Enemy
{
public :
	EnemyZaco();
	~EnemyZaco() override;

	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;
	//void Fire() override;

private :

	const vRESULT init();
	const vRESULT InitialImgLoad();
};