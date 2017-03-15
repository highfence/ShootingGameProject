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
	
	~EnemyItem() override;

	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;
	//void Fire() override;
	void Activate(
		const _In_ Vec,
		_In_ CreateOption&,
		_In_ FireOption&) override;

private :

	const vRESULT init();
	const vRESULT InitialImgLoad(const _In_ BOOL);

};