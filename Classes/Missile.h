#pragma once
#include "Missile.h"

/*
	PlayerMissile
	플레이어의 미사일을 표현하는 클래스. 
*/

class Missile 
{
public : 
	Missile();
	~Missile();

	BOOL Launch(const _In_ FLOAT, const _In_ FLOAT);
	void Fly(const _In_ FLOAT);
	void Draw(_Inout_ HDC);

private :

	void init();
	BOOL IsMissileOnDisplay();

	CImage* m_pSprite;
	CImage* m_pShapeSprite;
	BOOL m_IsMissileLaunched;
	FLOAT m_PosX;
	FLOAT m_PosY;
};