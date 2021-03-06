#include "stdafx.h"
#include "CreateOption.h"

CreateOption::CreateOption(
	const INT& enemyHp,
	const ENEMY::ENEMY_TYPE& enemyType,
	const ENEMY::FLIGHT_TYPE& flightType,
	const Vec& flightVec,
	const FLOAT& flightSpeed,
	const FLOAT& accFlightSpeed,
	const GoAndSlowData& goAndSlowData,
	const BOOL& isItemLaunched)
	: m_IsOptionCanUse(TRUE)
{
	SetEnemyHp(enemyHp);
	SetEnemyType(enemyType);
	SetFlightType(flightType);
	SetFlightVec(flightVec);
	SetFlightSpeed(flightSpeed);
	SetAccFlightSpeed(accFlightSpeed);
	SetGoAndSlowData(goAndSlowData);
	SetMoveSideOnly(NULL);
	SetIsItemLaunched(isItemLaunched);
}

CreateOption::CreateOption(
	const INT & enemyHp,
	const ENEMY::ENEMY_TYPE & enemyType,
	const ENEMY::FLIGHT_TYPE & flightType,
	const Vec & flightVec,
	const FLOAT & flightSpeed,
	const FLOAT & accFlightSpeed,
	const MoveSideOnly & moveOnlySide,
	const BOOL & isItemLaunched)
	: m_IsOptionCanUse(TRUE)
{
	SetEnemyHp(enemyHp);
	SetEnemyType(enemyType);
	SetFlightType(flightType);
	SetFlightVec(flightVec);
	SetFlightSpeed(flightSpeed);
	SetAccFlightSpeed(accFlightSpeed);
	SetGoAndSlowData(NULL);
	SetMoveSideOnly(moveOnlySide);
	SetIsItemLaunched(isItemLaunched);
}

CreateOption::CreateOption(
	const INT & enemyHp,
	const ENEMY::ENEMY_TYPE & enemyType,
	const ENEMY::FLIGHT_TYPE & flightType,
	const Vec & flightVec,
	const FLOAT & flightSpeed,
	const FLOAT & accFlightSpeed,
	const std::nullptr_t null,
	const BOOL & isItemLaunched)
	: m_IsOptionCanUse(TRUE)
{
	SetEnemyHp(enemyHp);
	SetEnemyType(enemyType);
	SetFlightType(flightType);
	SetFlightVec(flightVec);
	SetFlightSpeed(flightSpeed);
	SetAccFlightSpeed(accFlightSpeed);
	SetGoAndSlowData(NULL);
	SetMoveSideOnly(NULL);
	SetIsItemLaunched(isItemLaunched);
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
	SetEnemyHp(op.GetEnemyHp());
	SetEnemyType(op.GetEnemyType());
	SetFlightType(op.GetFlightType());
	SetFlightVec(op.GetFlightVec());
	SetFlightSpeed(op.GetFlightSpeed());
	SetAccFlightSpeed(op.GetAccFlightSpeed());
	SetGoAndSlowData(op.GetGoAndSlowData());
	SetMoveSideOnly(op.GetMoveSideOnly());
	SetIsItemLaunched(op.GetIsItemLaunched());
	return *this;
}

/*
	Getter, Setter Zone
*/
CreateOption & CreateOption::GetOption()
{
	return *this;
}

BOOL CreateOption::GetIsOptionCanUse() const
{
	return m_IsOptionCanUse;
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

MoveSideOnly CreateOption::GetMoveSideOnly() const
{
	return m_MoveOnlySide;
}

BOOL CreateOption::GetIsItemLaunched() const
{
	return m_IsItemLaunched;
}

void CreateOption::SetEnemyHp(const INT& hp)
{
	m_EnemyHp = hp;
}

void CreateOption::SetEnemyType(const _In_ ENEMY::ENEMY_TYPE& enemyType)
{
	m_EnemyType = enemyType;
}

void CreateOption::SetFlightType(const _In_ ENEMY::FLIGHT_TYPE& flightType)
{
	m_FlightType = flightType;
}

void CreateOption::SetFlightVec(const _In_ Vec& flightVec)
{
	m_FlightVec = flightVec;
}

void CreateOption::SetFlightSpeed(const _In_ FLOAT& flightSpeed)
{
	m_FlightSpeed = flightSpeed;
}

void CreateOption::SetAccFlightSpeed(const _In_ FLOAT& accFlightSpeed)
{
	m_AccFlightSpeed = accFlightSpeed;
}

void CreateOption::SetGoAndSlowData(const _In_ GoAndSlowData& data)
{
	m_GoAndSlowData = data;
}

void CreateOption::SetMoveSideOnly(const MoveSideOnly & data)
{
	m_MoveOnlySide = data;
}

void CreateOption::SetIsItemLaunched(const BOOL& isItemLaunched)
{
	m_IsItemLaunched = isItemLaunched;
}

GoAndSlowData::GoAndSlowData()
{
}

GoAndSlowData::GoAndSlowData(
	const FLOAT& slowDownStartTime,
	const FLOAT& slowDownDurationTime,
	const Vec& slowDownMoveVec,
	const FLOAT& slowDownMoveSpeed)
{
	m_SlowDownStartTime = slowDownStartTime;
	m_SlowDownDurationTime = slowDownDurationTime;
	m_SlowDownMoveVec = slowDownMoveVec;
	m_SlowDownMoveSpeed = slowDownMoveSpeed;
}

/*
	int값이 들어올시 모두 0으로 세팅.	
*/
GoAndSlowData::GoAndSlowData(int trashValue)
{
	m_SlowDownStartTime = 0.f;
	m_SlowDownDurationTime = 0.f;
	m_SlowDownMoveVec = Vec(0.f, 0.f);
	m_SlowDownMoveSpeed = 0.f;
}

GoAndSlowData & GoAndSlowData::operator=(const GoAndSlowData& data)
{
	m_SlowDownStartTime = data.m_SlowDownStartTime;
	m_SlowDownDurationTime = data.m_SlowDownDurationTime;
	m_SlowDownMoveVec = data.m_SlowDownMoveVec;
	m_SlowDownMoveSpeed = data.m_SlowDownMoveSpeed;
	return *this;
}

MoveSideOnly::MoveSideOnly(
	const FLOAT & yAxisMoveDistance,
	const FLOAT & yAxisMoveSpeed,
	const FLOAT & xAxisMoveSpeed,
	const FLOAT & xAxisMoveTimeInterval,
	const FLOAT & moveTimeRandomRange)
{
	m_YAxisMoveDistance = yAxisMoveDistance;
	m_YAxisMoveSpeed = yAxisMoveSpeed;
	m_XAxisMoveSpeed = xAxisMoveSpeed;
	m_XAxisMoveTimeInterval = xAxisMoveTimeInterval;
	m_MoveTimeRandomRange = moveTimeRandomRange;
};

MoveSideOnly & MoveSideOnly::operator=(const MoveSideOnly& data)
{
	m_YAxisMoveDistance = data.m_YAxisMoveDistance;
	m_YAxisMoveSpeed = data.m_YAxisMoveSpeed;
	m_XAxisMoveSpeed = data.m_XAxisMoveSpeed;
	m_XAxisMoveTimeInterval = data.m_XAxisMoveTimeInterval;
	m_MoveTimeRandomRange = data.m_MoveTimeRandomRange;
	m_IsYAxisMoveEnded = data.m_IsYAxisMoveEnded;
	m_IsGoingRight = data.m_IsGoingRight;
	m_InitialCreatePosition = data.m_InitialCreatePosition;
	m_XAxisPostionBeforeMove = data.m_XAxisPostionBeforeMove;
	m_XAxisMoveDistance = data.m_XAxisMoveDistance;
	return *this;
}