#pragma once
#include "Missile.h"


class Missile 
{
public : 
	Missile();
	virtual ~Missile();

	virtual void Fly(const _In_ FLOAT, const _In_ FLOAT, const _In_ FLOAT, const _In_ FLOAT) = 0;
	void Draw(_Inout_ HDC);

	BOOL Launch(const _In_ FLOAT, const _In_ FLOAT);
	BOOL Launch(const _In_ ENEMY::MISSILE_TYPE, const _In_ FLOAT, const _In_ FLOAT);
	BOOL GetMissileLaunched() const;
	void SetMissileType(const _In_ ENEMY::MISSILE_TYPE);
	ENEMY::MISSILE_TYPE GetMissileType() const;

	CImage* m_pSprite;
	CImage* m_pShapeSprite;
	INT m_Damage;
	BOOL m_IsMissileLaunched;
	BOOL IsMissileOnDisplay();
	FLOAT m_PosX;
	FLOAT m_PosY;
	FLOAT m_Width;
	FLOAT m_Height;
	ENEMY::MISSILE_TYPE m_MissileType;

private :

	void init();

};