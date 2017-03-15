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

	// �̻��� ���� �Լ� ������ �ڵ鷯.
	BOOL(EnemyMissile::*m_pMissileFlyHandler[MISSILE_TYPE_NUM])(const _In_ FLOAT);

	// �Լ� ������ �ڵ鷯�� ��ϵ� �Լ�.
	BOOL MissileFlyNormal(const _In_ FLOAT);
	
};