#pragma once

// ���漱��
class Missile;


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
	void Move(const _In_ BYTE*, const _In_ FLOAT);
	void MissileFly(const _In_ FLOAT);

private :

	void init();

	FLOAT m_PosX;
	FLOAT m_PosY;
	CImage* m_pSprite;
	CImage* m_pShapeSprite;
	Missile* m_pMissile;

};