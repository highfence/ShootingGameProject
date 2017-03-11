#include "stdafx.h"
#include "CreateOption.h"

CreateOption::CreateOption(
	const Vec createPos,
	const INT enemyHp,
	const ENEMY::ENEMY_TYPE enemyType,
	const ENEMY::FLIGHT_TYPE flightType,
	const Vec flightVec,
	const FLOAT flightSpeed,
	const FLOAT accFlightSpeed,
	const GoAndSlowData goAndSlowData)
	: m_IsOptionCanUse(TRUE)
{
	SetCreatePos(createPos);
	SetEnemyHp(enemyHp);
	SetEnemyType(enemyType);
	SetFlightType(flightType);
	SetFlightVec(flightVec);
	SetFlightSpeed(flightSpeed);
	SetAccFlightSpeed(accFlightSpeed);
	SetGoAndSlowData(goAndSlowData);
}

CreateOption::CreateOption(const std::nullptr_t)
{
	m_IsOptionCanUse = FALSE;
}

CreateOption::CreateOption()
{
	m_IsOptionCanUse = FALSE;
}

CreateOption::~CreateOption()
{

}

CreateOption& CreateOption::operator=(const _In_ CreateOption& op)
{
	m_IsOptionCanUse = TRUE;
	SetCreatePos(op.GetCreatePos());
	SetEnemyHp(op.GetEnemyHp());
	SetEnemyType(op.GetEnemyType());
	SetFlightType(op.GetFlightType());
	SetFlightVec(op.GetFlightVec());
	SetFlightSpeed(op.GetFlightSpeed());
	SetAccFlightSpeed(op.GetAccFlightSpeed());
	SetGoAndSlowData(op.GetGoAndSlowData());
	return *this;
}

/*
	Getter, Setter Zone
*/
BOOL CreateOption::GetIsOptionCanUse() const
{
	return m_IsOptionCanUse;
}

Vec CreateOption::GetCreatePos() const
{
	return m_CreatePosition;
}

INT CreateOption::GetEnemyHp() const
{
	return m_EnemyHp;
}

ENEMY::ENEMY_TYPE CreateOption::GetEnemyType() const
{
	return m_EnemyType;
}

ENEMY::FLIGHT_TYPE CreateOption::GetFlightType() const
{
	return m_FlightType;
}

Vec CreateOption::GetFlightVec() const
{
	return m_FlightVec;
}

FLOAT CreateOption::GetFlightSpeed() const
{
	return m_FlightSpeed;
}

FLOAT CreateOption::GetAccFlightSpeed() const
{
	return m_AccFlightSpeed;
}

GoAndSlowData CreateOption::GetGoAndSlowData() const
{
	return m_GoAndSlowData;
}

void CreateOption::SetCreatePos(const _In_ Vec createPos)
{
	m_CreatePosition = createPos;
}

void CreateOption::SetEnemyHp(const INT hp)
{
	m_EnemyHp = hp;
}

void CreateOption::SetEnemyType(const _In_ ENEMY::ENEMY_TYPE enemyType)
{
	m_EnemyType = enemyType;
}

void CreateOption::SetFlightType(const _In_ ENEMY::FLIGHT_TYPE flightType)
{
	m_FlightType = flightType;
}

void CreateOption::SetFlightVec(const _In_ Vec flightVec)
{
	m_FlightVec = flightVec;
}

void CreateOption::SetFlightSpeed(const _In_ FLOAT flightSpeed)
{
	m_FlightSpeed = flightSpeed;
}

void CreateOption::SetAccFlightSpeed(const _In_ FLOAT accFlightSpeed)
{
	m_AccFlightSpeed = accFlightSpeed;
}

void CreateOption::SetGoAndSlowData(const _In_ GoAndSlowData data)
{
	m_GoAndSlowData = data;
}

GoAndSlowData::GoAndSlowData()
{
}

GoAndSlowData::GoAndSlowData(
	const FLOAT slowDownStartTime,
	const FLOAT slowDownDurationTime,
	const Vec slowDownMoveVec,
	const FLOAT slowDownMoveSpeed)
{
	SlowDownStartTime = slowDownStartTime;
	SlowDownDurationTime = slowDownDurationTime;
	SlowDownMoveVec = slowDownMoveVec;
	SlowDownMoveSpeed = slowDownMoveSpeed;
}

GoAndSlowData & GoAndSlowData::operator=(const GoAndSlowData data)
{
	SlowDownStartTime = data.SlowDownStartTime;
	SlowDownDurationTime = data.SlowDownDurationTime;
	SlowDownMoveVec = data.SlowDownMoveVec;
	SlowDownMoveSpeed = data.SlowDownMoveSpeed;
	return *this;
}
