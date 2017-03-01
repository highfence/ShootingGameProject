#pragma once
#include "Missile.h"

/*
	PlayerMissile
	플레이어의 미사일을 표현하는 클래스. 
*/

class PlayerMissile : public Missile
{
public :
	PlayerMissile();
	~PlayerMissile();

	void Fly(const _In_ FLOAT) override;
	BOOL CheckColide();

private :

	BOOL IsColideWithEnemy(const _In_ FLOAT, const _In_ FLOAT, const _In_ FLOAT, const _In_ FLOAT);
	void init();
};