#pragma once
#include "Missile.h"

class EnemyMissile : public Missile
{
public :
	EnemyMissile(ENEMY::MISSILE_SIZE);
	~EnemyMissile() override;

	void Fly(const _In_ FLOAT, const _In_ FLOAT, const _In_ FLOAT, const _In_ FLOAT) override;
	void SetPlayerPos(const _In_ FLOAT, const _In_ FLOAT);
	BOOL CheckColideWithPlayer();

private :

	EnemyMissile();
	void init();
	FLOAT m_PlayerPosX;
	FLOAT m_PlayerPosY;
};