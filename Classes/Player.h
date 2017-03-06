#pragma once

// 전방선언
class Missile;
class PlayerMissile;
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
	INT GetPosition(_Out_ FLOAT*, _Out_ FLOAT*);
	FLOAT GetCollisionPixel() const;
	BOOL GetIsPlayerAlived() const;
	void PlayerDamaged();
	void PlayerPowerUp();

private :

	void init();
	INT InitialImgLoad();
	INT AccTime(const _In_ FLOAT);
	void MissileLoad();
	void MissileDraw(_Inout_ HDC);
	void LaunchMissile(const _In_ FLOAT);
	void LoadImgWithDirection();
	void DeleteMissile();
	void CheckMissileColide();
	void ChangeMissilesAccordWithPower();
	INT CalDirection(const _In_ INT);


	FLOAT m_PosX;
	FLOAT m_PosY;
	FLOAT m_Width;
	FLOAT m_Height;
	FLOAT m_CollisionPixel;
	FLOAT m_AccTime;
	FLOAT m_RecordAccTime;
	INT m_PowerTier;
	CImage* m_pSprite;
	CImage* m_pShadeSprite;
	Missile* m_pMissile;
	BOOL m_IsPlayerAlive;
	INT m_Direction;

	std::vector<PlayerMissile*> m_MissileVec;

#ifdef _DEBUG
	INT PrintDebugLabel(_Inout_ HDC);
#endif
};