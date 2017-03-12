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

	virtual void Draw(_Inout_ HDC) = 0;
	virtual void Explode() = 0;
	virtual void DeadProc() = 0;
	virtual void Fire() = 0;

	virtual void CalcProc(const _In_ FLOAT);
	        void DrawProc(_Inout_ HDC);

	        void Fly(const _In_ FLOAT);
	        void MissileFly(const _In_ FLOAT);
	virtual void GetDamage(const _In_ INT, const _In_ Vec);
	        void AccTime(const _In_ FLOAT);
	        void LoadMissiles(const _In_ ENEMY::MISSILE_SIZE);
	        void DrawMissiles(_Inout_ HDC);
			void ReleaseCImages();

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

	virtual void Activate(const _In_ Vec, _In_ CreateOption&, _In_ FireOption&);
	void Deactivate();
	BOOL IsAllMissilesEndFly();
	BOOL CheckDead();
	BOOL CheckActEnd();
	BOOL CheckEnemyIsOnDisplay();
	vRESULT FunctionPointerRegist();
	EnemyMissile* GetLaunchableMissile();


protected :
	// �����丵���� ���� �� �κе�
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
	FLOAT	     m_AccTime;
	FLOAT	     m_RecordAccTime;
	FLOAT	     m_RecordFlyTime;
	Vec			 m_FlightUnitVec;
	BOOL	     m_IsEnemyDead;
	BOOL	     m_IsEnemyExplode;
	CImage*      m_pSprite;
	CImage*      m_pShadeSprite;

	BOOL(Enemy::*m_pFlightHandler[ENEMY::FLIGHT_TYPE_NUM])(const _In_ FLOAT);
	BOOL(Enemy::*m_pMissileFlyHandler[ENEMY::MISSILE_TYPE_NUM])(
		EnemyMissile*,
		const _In_ FLOAT);
	std::vector<EnemyMissile*> m_MissileVec;


private :

	// Flight Ÿ�� �Լ� ������.
	BOOL FlyStraight(const _In_ FLOAT);
	BOOL FlyItem(const _In_ FLOAT);
	BOOL FlyAccelerate(const _In_ FLOAT);
	BOOL FlyGoAndSlow(const _In_ FLOAT);

	// MissileFly Ÿ�� �Լ� ������.
	BOOL MissileFlyStraight(EnemyMissile*, const _In_ FLOAT);
	BOOL MissileFlyAimed(EnemyMissile*, const _In_ FLOAT);

	void init();
	void DeleteAllElementsMissileVector();
	void FixUnitVecForRemainOnDisplay();
};