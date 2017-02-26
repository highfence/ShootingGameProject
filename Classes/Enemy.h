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

	FLOAT m_PosX;
	FLOAT m_PosY;
	INT m_FlightType;
	FLOAT m_FlightSpeed;

	BOOL(Enemy::*m_pFlightHandler[ENEMY::FLIGHT_TYPE_NUM])(const _In_ FLOAT);

private :

	BOOL FlyStraight(const _In_ FLOAT);
	
	void init();
};