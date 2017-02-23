#pragma once

/*
	Missile
	미사일을 표현하는 클래스. 
	옵션을 주어 적군과 아군의 미사일을 구분해서 생성할 수 있도록 해야할 것 같다.
*/

class Missile
{
public : 
	Missile();
	~Missile();

private :

	void init();

	CImage* m_pSprite;
	CImage* m_pShapeSprite;
};