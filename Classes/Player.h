#pragma once

// 전방선언
class Missile;
class Enemy;

/*
	Player
	사용자가 조종하게 되는 비행기 클래스.
*/

class Player
{
public :
	Player();
	~Player();

	void CalProc(const _In_ BYTE*, const _In_ FLOAT);
	void DrawProc(_Inout_ HDC);

	void Draw(_Inout_ HDC);
	void Move(const _In_ BYTE*, const _In_ FLOAT);
	void MissileFly(const _In_ FLOAT);
	void GetPosition(_Out_ INT*, _Out_ INT*);

private :

	void init();
	void MissileLoad();
	void MissileDraw(_Inout_ HDC);
	void LaunchMissile(const _In_ FLOAT);
	void DeleteMissile();
	void CheckMissileColide();

	FLOAT m_PosX;
	FLOAT m_PosY;
	FLOAT m_AccTime;
	CImage* m_pSprite;
	CImage* m_pShapeSprite;
	Missile* m_pMissile;

	std::vector<Missile*> m_MissileVec;
};