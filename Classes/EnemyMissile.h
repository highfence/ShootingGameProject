#pragma once
#include "Missile.h"

class EnemyMissile : public Missile
{
public :
	EnemyMissile(ENEMY::MISSILE_SIZE);
	~EnemyMissile() override;

	void Fly(
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT) override;
	void SetPlayerPos(const _In_ FLOAT, const _In_ FLOAT);
	BOOL CheckColideWithPlayer();

	BOOL Launch(
		const _In_ Vec,
		const _In_ ::MissileOption);

	::MissileOption GetOption() const;

private :

	EnemyMissile();
	void init();
	FLOAT m_PlayerPosX;
	FLOAT m_PlayerPosY;
	::MissileOption m_Option;
};