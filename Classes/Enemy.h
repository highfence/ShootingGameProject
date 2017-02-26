#pragma once
using namespace ENEMY;

/*
	Enemy
		: 생성인자 (생성좌표 x, y, 비행 타입)
	적군을 표현하기위한 기본 클래스.
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