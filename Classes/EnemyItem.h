#pragma once
#include "Enemy.h"

/*
	EnemyItem
		: �������� (������ǥ x, y, ���� Ÿ��, �������� �ִ���)
*/

class EnemyItem : public Enemy
{
public : 
	EnemyItem();
	EnemyItem(
		const _In_ Vec createPos,
		const _In_ INT flightType,
		const _In_opt_ Vec flightVec,
		const _In_opt_ ::CreateOption flightOption);
	~EnemyItem() override;

	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;
	void Fire() override;

private :

	const vRESULT init();
	const vRESULT InitialImgLoad();

};