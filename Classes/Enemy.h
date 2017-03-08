#pragma once
using namespace ENEMY;

class EnemyMissile;

/*
	Enemy
		: 생성인자 (생성좌표 x, y, 비행 타입)
	적군을 표현하기위한 기본 클래스.
*/

class Enemy
{
public :
	Enemy(
		const _In_ Vec createPos,
		const _In_ INT flightType,
		const _In_opt_ Vec flightVec);
	
	virtual ~Enemy();

	virtual void Draw(_Inout_ HDC) = 0;
	virtual void Explode() = 0;
	virtual void DeadProc() = 0;
	virtual void Fire() = 0;

	virtual void CalProc(const _In_ FLOAT);
	        void DrawProc(_Inout_ HDC);

	        void Fly(const _In_ FLOAT);
	        void MissileFly(const _In_ FLOAT);
	virtual const vRESULT GetDamage(const _In_ INT, const _In_ Vec);
	        void AccTime(const _In_ FLOAT);
	        void LoadMissiles(const _In_ ENEMY::MISSILE_SIZE);
	        void DrawMissiles(_Inout_ HDC);

	BOOL IsAllMissilesEndFly();
	void CheckEnemyReadyToDelete();
	BOOL CheckDead();
	BOOL CheckEnemyIsOnDisplay();
	INT  RotateAccordWithVec();
	vRESULT FunctionPointerRegist();

	Vec		     m_Pos;
	FLOAT	     m_PlayerX;
	FLOAT	     m_PlayerY;
	INT		     m_FlightType;
	Vec		     m_FlightVec;
	FLOAT	     m_FlightSpeed;
	Vec		     m_SpriteRange;
	Vec		     m_ColideRange;
	FLOAT	     m_MissileSpeed;
	FLOAT	     m_MissileDamage;
	INT		     m_Hp;
	INT		     m_LoadedMissileNumber;
	FLOAT	     m_AccTime;
	FLOAT	     m_RecordAccTime;
	FLOAT	     m_RecordFlyTime;
	FLOAT	     m_UnitVecX;
	FLOAT	     m_UnitVecY;
	BOOL		 m_IsEnemyReadyToDelete;
	BOOL	     m_IsEnemyDead;
	BOOL	     m_IsEnemyExplode;
	CImage*      m_pSprite;
	CImage*      m_pShadeSprite;
	CreateOption m_Option;

	BOOL(Enemy::*m_pFlightHandler[ENEMY::FLIGHT_TYPE_NUM])(const _In_ FLOAT);
	BOOL(Enemy::*m_pMissileFlyHandler[ENEMY::MISSILE_TYPE_NUM])(
		EnemyMissile*,
		const _In_ FLOAT);
	std::vector<EnemyMissile*> m_MissileVec;

private :

	// Flight 타입 함수 포인터.
	BOOL FlyStraight(const _In_ FLOAT);
	BOOL FlyItem(const _In_ FLOAT);
	BOOL FlyAccelerate(const _In_ FLOAT);
	BOOL FlyGoAndSlow(const _In_ FLOAT);

	// MissileFly 타입 함수 포인터.
	BOOL MissileFlyStraight(EnemyMissile*, const _In_ FLOAT);
	BOOL MissileFlyAimed(EnemyMissile*, const _In_ FLOAT);

	void init();
	void DeleteAllElementsMissileVector();
};