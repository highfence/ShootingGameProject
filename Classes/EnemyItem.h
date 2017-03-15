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