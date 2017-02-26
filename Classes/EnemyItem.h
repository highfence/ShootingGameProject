#pragma once
#include "Enemy.h"

/*
	EnemyItem
		: �������� (������ǥ x, y, ���� Ÿ��, �������� �ִ���)
	- ���� ����
	- �̻����� ���� �ʴ´�.
	- 4�� ����� �ٴϸ鼭 ������ ����Ⱑ �������� �ش�. (������)
*/

class EnemyItem : public Enemy
{
public : 
	EnemyItem(const _In_ FLOAT x, const _In_ FLOAT y, const _In_ INT flightType, const _In_ BOOL IsItemLaunched);
	~EnemyItem() override;

	void Draw(_Inout_ HDC) override;

private :

	void init();

	CImage* m_pSprite;
	CImage* m_pShadeSprite;
	BOOL m_IsItemLaunched;
};