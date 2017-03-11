#pragma once
#include "Enemy.h"

/*
	EnemyItem
		: 생성인자 (생성좌표 x, y, 비행 타입, 아이템이 있는지)
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