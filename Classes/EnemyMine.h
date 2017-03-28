#pragma once
#include "Enemy.h"

class EnemyMine : public Enemy
{
public :
	EnemyMine();
	~EnemyMine() override;

	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;

private :
	void Init();
	void InitialImgLoad();

};