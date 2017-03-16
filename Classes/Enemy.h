#pragma once
using namespace ENEMY;

class EnemyMissile;

/*
	Enemy
		: 생성인자 (생성좌표 x, y, 비행 타입)
	적군을 표현하기위한 기본 클래스.
*/

// TODO :: Protected 멤버 결정하기.

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

	// 상속 클래스에서도 쓸 일이 있을 변수들.
	BOOL		 m_IsEnemyActivated;
	CreateOption m_CreateOption;
	FireOption	 m_FireOption;

	// 기존 멤버 변수 (지워야할 것을 찾자)
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

	// Protected 함수.
	EnemyMissile* GetLaunchableMissile();

private :

	// 가상 함수.
	virtual void Draw(_Inout_ HDC) = 0;
	virtual void Explode() = 0;
	virtual void DeadProc() = 0;
	virtual void Fire();
	
	// Flight 타입 함수 포인터.
	BOOL FlyStraight(const _In_ FLOAT);
	BOOL FlyItem(const _In_ FLOAT);
	BOOL FlyAccelerate(const _In_ FLOAT);
	BOOL FlyGoAndSlow(const _In_ FLOAT);

	// Fire 타입 함수 포인터.
	BOOL FireNormal();
	BOOL FireAimed();
	BOOL FireNways();

	// Fire 보조 함수.
	BOOL SetOptionMissileVecToPlayer();
	BOOL LaunchOddNumberWaysMissiles();
	BOOL LaunchEvenNumberWaysMissiles();

	// 그 외 사용 함수.
	void init();
	void DeleteAllElementsMissileVector();
	void FixUnitVecForRemainOnDisplay();
	void FunctionPointerRegist();
	void DistributeFireOption();
};