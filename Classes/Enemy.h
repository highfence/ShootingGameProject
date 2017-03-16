#pragma once
using namespace ENEMY;

class EnemyMissile;

/*
	Enemy
		: �������� (������ǥ x, y, ���� Ÿ��)
	������ ǥ���ϱ����� �⺻ Ŭ����.
*/

// TODO :: Protected ��� �����ϱ�.

class Enemy
{
public :
	Enemy();
	virtual ~Enemy();

	virtual void CalcProc(const _In_ FLOAT);
	        void DrawProc(_Inout_ HDC);

	        void Fly(const _In_ FLOAT);
	        void MissileFly(const _In_ FLOAT);
	virtual void GetDamage(const _In_ INT, const _In_ Vec);
	virtual void Activate(const _In_ Vec, _In_ CreateOption&, _In_ FireOption&);
	        void AccTime(const _In_ FLOAT);
	        void LoadMissiles(const _In_ ENEMY::MISSILE_SIZE);
	        void DrawMissiles(_Inout_ HDC);
			void ReleaseCImages();
			void Deactivate();
			BOOL IsAllMissilesEndFly();
			BOOL CheckDead();
			BOOL CheckActEnd();
			BOOL CheckEnemyIsOnDisplay();

	// Getter, Setter
	BOOL GetIsEnemyActivated() const;
	CreateOption GetCreateOption() const;
	FireOption GetFireOption() const;
	Vec GetPosition() const;
	Vec GetColideRange() const;
	BOOL GetIsEnemyDead() const;
	ENEMY_TYPE GetEnemyType() const;
	void SetIsEnemyActivated(const _In_ BOOL);
	void SetCreateOption(const _In_ CreateOption);
	void SetFireOption(const _In_ FireOption);
	void SetPosition(const _In_ Vec);
	void SetColideRange(const _In_ Vec);
	void SetPlayerPos(const _In_ Vec);
	void SetIsEnemyDead(const _In_ BOOL);
	void SetEnemyType(const _In_ ENEMY_TYPE);


protected :

	// ��� Ŭ���������� �� ���� ���� ������.
	BOOL		 m_IsEnemyActivated;
	CreateOption m_CreateOption;
	FireOption	 m_FireOption;

	// ���� ��� ���� (�������� ���� ã��)
	Vec		     m_Pos;
	INT		     m_Hp;
	ENEMY_TYPE	 m_EnemyType;
	Vec			 m_PlayerPos;
	Vec		     m_SpriteRange;
	Vec		     m_ColideRange;
	INT		     m_LoadedMissileNumber;
	FLOAT	     m_AccTime = 0.f;
	FLOAT	     m_RecordAccTime = 0.f;
	FLOAT	     m_RecordFlyTime = 0.f;
	FLOAT		 m_RecordFireTime = 0.f;
	Vec			 m_FlightUnitVec = Vec(0.f, 0.f);
	BOOL	     m_IsEnemyDead = TRUE;
	BOOL	     m_IsEnemyExplode = FALSE;
	CImage*      m_pSprite = nullptr;
	CImage*      m_pShadeSprite = nullptr;

	BOOL(Enemy::*m_pFlightHandler[ENEMY::FLIGHT_TYPE_NUM])(const _In_ FLOAT);
	BOOL(Enemy::*m_pFireHandler[ENEMY::FIRE_TYPE_NUM])();

	std::vector<EnemyMissile*> m_MissileVec;

	// Protected �Լ�.
	EnemyMissile* GetLaunchableMissile();

private :

	// ���� �Լ�.
	virtual void Draw(_Inout_ HDC) = 0;
	virtual void Explode() = 0;
	virtual void DeadProc() = 0;
	virtual void Fire();
	
	// Flight Ÿ�� �Լ� ������.
	BOOL FlyStraight(const _In_ FLOAT);
	BOOL FlyItem(const _In_ FLOAT);
	BOOL FlyAccelerate(const _In_ FLOAT);
	BOOL FlyGoAndSlow(const _In_ FLOAT);

	// Fire Ÿ�� �Լ� ������.
	BOOL FireNormal();
	BOOL FireAimed();
	BOOL FireNways();

	// Fire ���� �Լ�.
	BOOL SetOptionMissileVecToPlayer();
	BOOL LaunchOddNumberWaysMissiles();
	BOOL LaunchEvenNumberWaysMissiles();

	// �� �� ��� �Լ�.
	void init();
	void DeleteAllElementsMissileVector();
	void FixUnitVecForRemainOnDisplay();
	void FunctionPointerRegist();
	void DistributeFireOption();
};