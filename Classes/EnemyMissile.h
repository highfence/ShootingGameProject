#pragma once
#include "Missile.h"

class EnemyMissile : public Missile
{
public :
	EnemyMissile();
	~EnemyMissile() override;

	void Fly(const _In_ FLOAT, const _In_ FLOAT, const _In_ FLOAT, const _In_ FLOAT) override;

private :

	void init();
};