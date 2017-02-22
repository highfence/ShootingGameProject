#pragma once

/*
	Player
	사용자가 조종하게 되는 비행기 클래스.
*/


class Player
{
public :
	Player();
	~Player();

	void Draw(_Inout_ HDC, const _In_ FLOAT);

private :

	void init();

	FLOAT m_PosX;
	FLOAT m_PosY;
	CImage* m_pSprite;

};