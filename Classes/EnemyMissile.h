#pragma once
#include "Missile.h"

class EnemyMissile : public Missile
{
public :
	EnemyMissile(ENEMY::MISSILE_SIZE);
	EnemyMissile() = delete;
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
		const _In_ FireOption&);

	FireOption GetOption() const;

private :

	void init();
	FLOAT m_PlayerPosX;
	FLOAT m_PlayerPosY;
	FireOption m_Option;
};