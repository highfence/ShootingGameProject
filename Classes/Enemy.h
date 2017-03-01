#pragma once
using namespace ENEMY;

/*
	Enemy
		: �������� (������ǥ x, y, ���� Ÿ��)
	������ ǥ���ϱ����� �⺻ Ŭ����.
*/

class Enemy
{
public :
	Enemy(const _In_ FLOAT, const _In_ FLOAT, const _In_ INT);
	virtual ~Enemy();

	void Fly(const _In_ FLOAT);
	virtual void Draw(_Inout_ HDC) = 0;
	virtual void Explode(_Inout_ HDC) = 0;
	virtual void DeadProc(_Inout_ HDC) = 0;
	void GetDamage(const _In_ INT);
	void AccTime(const _In_ FLOAT);
	BOOL CheckEnemyIsOnDisplay();

	FLOAT m_PosX;
	FLOAT m_PosY;
	INT m_FlightType;
	FLOAT m_FlightSpeed;
	FLOAT m_Width;
	FLOAT m_Height;
	INT m_Hp;
	FLOAT m_AccTime;
	BOOL m_IsEnemyDead;
	BOOL m_IsEnemyExplode;
	CImage* m_pSprite;
	CImage* m_pShadeSprite;

	BOOL(Enemy::*m_pFlightHandler[ENEMY::FLIGHT_TYPE_NUM])(const _In_ FLOAT);

private :

	BOOL FlyStraight(const _In_ FLOAT);
	
	void init();
};