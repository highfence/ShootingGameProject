#pragma once
#include "Missile.h"


class Missile 
{
public : 
	Missile();
	virtual ~Missile();

	virtual void Fly(
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT) = 0;
	void Draw(_Inout_ HDC);

	BOOL Launch(
		const _In_ Vec);
	BOOL Launch(
		const _In_ ENEMY::MISSILE_TYPE,
		const _In_ Vec);


	BOOL GetMissileLaunched() const;
	void SetMissileType(const _In_ ENEMY::MISSILE_TYPE);
	ENEMY::MISSILE_TYPE GetMissileType() const;

	CImage* m_pSprite;
	CImage* m_pShapeSprite;
	BOOL m_IsMissileLaunched;
	BOOL IsMissileOnDisplay();
	Vec m_Pos;
	FLOAT m_AccTime = 0.f;
	INT m_Width;
	INT m_Height;
	INT m_Damage;
	ENEMY::MISSILE_TYPE m_MissileType;

private :

	void init();

};