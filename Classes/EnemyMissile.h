#pragma once
#include "Missile.h"

class EnemyMissile : public Missile
{
public :
	EnemyMissile(ENEMY::MISSILE_SIZE);
	~EnemyMissile() override;

	void Fly(const _In_ FLOAT, const _In_ FLOAT, const _In_ FLOAT, const _In_ FLOAT) override;

private :

	EnemyMissile();
	void init();
};