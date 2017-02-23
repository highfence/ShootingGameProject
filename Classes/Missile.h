#pragma once

/*
	Missile
	미사일을 표현하는 클래스. 
	옵션을 주어 적군과 아군의 미사일을 구분해서 생성할 수 있도록 해야할 것 같다.
	혹은 상속을 할까?
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