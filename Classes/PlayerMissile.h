#pragma once
#include "Missile.h"

/*
	PlayerMissile
	�÷��̾��� �̻����� ǥ���ϴ� Ŭ����. 
*/

class PlayerMissile : public Missile
{
public :
	PlayerMissile();
	~PlayerMissile();

	void Fly(
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT) override;
	BOOL CheckColide();
	BOOL ChangeMissileTier(const _In_ INT);

private :

	BOOL IsColideWithEnemy(
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT);
	INT InitialImgLoad();

	void init();
};