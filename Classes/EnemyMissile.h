#pragma once
#include "Missile.h"

class EnemyMissile : public Missile
{
public :
	EnemyMissile(ENEMY::MISSILE_SIZE);
	EnemyMissile() = delete;
	~EnemyMissile() override;

	void CalcProc(const _In_ FLOAT);
	void Fly(
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT) override;
	void SetPlayerPos(const _In_ FLOAT, const _In_ FLOAT);
	void Draw(const _In_ HDC) override;
	BOOL CheckColideWithPlayer();

	BOOL Launch(
		const _In_ Vec,
		const _In_ FireOption&);

	FireOption GetOption() const;
	void SetFireOption(const _In_ FireOption&);

private :

	void init();
	void RegisterFunctionPointer();


	FLOAT m_PlayerPosX;
	FLOAT m_PlayerPosY;
	FireOption m_Option;

	// 미사일 진행 함수 포인터 핸들러.
	BOOL(EnemyMissile::*m_pMissileFlyHandler[MISSILE_TYPE_NUM])(const _In_ FLOAT);

	// 함수 포인터 핸들러에 등록될 함수.
	BOOL MissileFlyNormal(const _In_ FLOAT);
	BOOL MissileAccelerate(const _In_ FLOAT);
	BOOL MissileCircle(const _In_ FLOAT);
	
	// 보조 함수.
	void MoveLoopingBullet(const _In_ FLOAT, FireOption&, CircleShotData&);
	BOOL IsMissileOnDisplay() override;
	void MakeMissileInitialState();
};