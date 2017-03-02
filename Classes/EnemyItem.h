#pragma once
#include "Enemy.h"

/*
	EnemyItem
		: 생성인자 (생성좌표 x, y, 비행 타입, 아이템이 있는지)
	- 직선 비행
	- 미사일은 쏘지 않는다.
	- 4개 편대로 다니면서 마지막 비행기가 아이템을 준다. (빨간색)
*/

class EnemyItem : public Enemy
{
public : 
	EnemyItem(const _In_ FLOAT x, const _In_ FLOAT y, const _In_ INT flightType, const _In_ BOOL IsItemLaunched);
	~EnemyItem() override;

	void Draw(_Inout_ HDC) override;
	void Explode(_Inout_ HDC) override;
	void DeadProc(_Inout_ HDC) override;
	void Fire() override;

private :

	void init();

	BOOL m_IsItemLaunched;
};