#pragma once

/*
	Player
	����ڰ� �����ϰ� �Ǵ� ����� Ŭ����.
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