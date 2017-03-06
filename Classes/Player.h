#pragma once

// ���漱��
class Missile;
class PlayerMissile;
class Enemy;

/*
	Player
	����ڰ� �����ϰ� �Ǵ� ����� Ŭ����.
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
	void GetPosition(_Out_ FLOAT*, _Out_ FLOAT*);
	FLOAT GetCollisionPixel() const;
	BOOL GetIsPlayerAlived() const;
	void PlayerDamaged();

private :

	void init();
	void MissileLoad();
	void MissileDraw(_Inout_ HDC);
	void LaunchMissile(const _In_ FLOAT);
	void CalDirection();
	void DeleteMissile();
	void CheckMissileColide();

	FLOAT m_PosX;
	FLOAT m_PosY;
	FLOAT m_Width;
	FLOAT m_Height;
	FLOAT m_CollisionPixel;
	FLOAT m_AccTime;
	CImage* m_pSprite;
	CImage* m_pShapeSprite;
	Missile* m_pMissile;
	BOOL m_IsPlayerAlive;
	INT m_Direction;

	std::vector<PlayerMissile*> m_MissileVec;
};