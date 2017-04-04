#pragma once

/*
	Enemy 생성시에 들어갈 여러가지 정보를 담는 클래스.
*/

struct GoAndSlowData
{
	GoAndSlowData();
	GoAndSlowData(
		const _In_ FLOAT& slowDownStartTime,
		const _In_ FLOAT& slowDownDurationTime,
		const _In_ Vec& slowDonwMoveVec,
		const _In_ FLOAT& slowDownMoveSpeed
	);
	GoAndSlowData(int);
	GoAndSlowData& operator=(const GoAndSlowData&);
	GoAndSlowData& operator=(const _In_ wchar_t*){};
	FLOAT m_SlowDownStartTime;
	FLOAT m_SlowDownDurationTime;
	Vec m_SlowDownMoveVec;
	FLOAT m_SlowDownMoveSpeed;
};

struct MoveOnlySide
{
	MoveOnlySide() = default;
	MoveOnlySide(
		const _In_ FLOAT& yAxisMoveDistance,
		const _In_ FLOAT& yAxisMoveSpeed,
		const _In_ FLOAT& xAxisMoveSpeed,
		const _In_ FLOAT& xAxisMoveTimeInterval,
		const _In_ FLOAT& moveTimeRandomRange)
	{
		m_YAxisMoveDistance = yAxisMoveDistance;
		m_YAxisMoveSpeed = yAxisMoveSpeed;
		m_XAxisMoveSpeed = xAxisMoveSpeed;
		m_XAxisMoveTimeInterval = xAxisMoveTimeInterval;
		m_MoveTimeRandomRange = moveTimeRandomRange;
	};
	MoveOnlySide(const _In_ INT) {};
	MoveOnlySide& operator=(const _In_ MoveOnlySide& opt)
	{
		m_YAxisMoveDistance = opt.m_YAxisMoveDistance;
		m_YAxisMoveSpeed = opt.m_YAxisMoveSpeed;
		m_XAxisMoveSpeed = opt.m_XAxisMoveSpeed;
		m_XAxisMoveTimeInterval = opt.m_XAxisMoveTimeInterval;
		m_MoveTimeRandomRange = opt.m_MoveTimeRandomRange;
		m_IsYAxisMoveEnded = opt.m_IsYAxisMoveEnded;
	};
	MoveOnlySide& operator=(const _In_ char*) {};

	FLOAT m_YAxisMoveDistance = 0.f;
	FLOAT m_YAxisMoveSpeed = 0.f;
	FLOAT m_XAxisMoveSpeed = 0.f;
	FLOAT m_XAxisMoveTimeInterval = 0.f;
	FLOAT m_MoveTimeRandomRange = 0.f;
	BOOL m_IsYAxisMoveEnded = FALSE;
};

class CreateOption
{
public :
	CreateOption(
		const _In_ INT& enemyHp,
		const _In_ ENEMY::ENEMY_TYPE& enemyType,
		const _In_ ENEMY::FLIGHT_TYPE& flightType,
		const _In_ Vec& flightVec,
		const _In_ FLOAT& flightSpeed,
		const _In_ FLOAT& accFlightSpeed,
		const _In_ GoAndSlowData& goAndSlowData,
		const _In_ BOOL& isItemLaunched);
	CreateOption(
		const _In_ INT& enemyHp,
		const _In_ ENEMY::ENEMY_TYPE& enemyType,
		const _In_ ENEMY::FLIGHT_TYPE& flightType,
		const _In_ Vec& flightVec,
		const _In_ FLOAT& flightSpeed,
		const _In_ FLOAT& accFlightSpeed,
		const _In_ MoveOnlySide& moveOnlySide,
		const _In_ BOOL& isItemLaunched);
	CreateOption(
		const _In_ INT& enemyHp,
		const _In_ ENEMY::ENEMY_TYPE& enemyType,
		const _In_ ENEMY::FLIGHT_TYPE& flightType,
		const _In_ Vec& flightVec,
		const _In_ FLOAT& flightSpeed,
		const _In_ FLOAT& accFlightSpeed,
		const _In_ std::nullptr_t null,
		const _In_ BOOL& isItemLaunched);
	CreateOption(const _In_ std::nullptr_t);
	CreateOption();
	~CreateOption();

	CreateOption& operator=(const _In_ CreateOption&);

	// Getter, Setter
	CreateOption&	   GetOption();
	BOOL               GetIsOptionCanUse() const;
	INT                GetEnemyHp()        const;
	ENEMY::ENEMY_TYPE  GetEnemyType()      const;
	ENEMY::FLIGHT_TYPE GetFlightType()     const;
	Vec                GetFlightVec()      const;
	FLOAT              GetFlightSpeed()    const;
	FLOAT              GetAccFlightSpeed() const;
	GoAndSlowData      GetGoAndSlowData()  const;
	MoveOnlySide	   GetMoveOnlySide()   const;
	BOOL               GetIsItemLaunched() const;

	void SetEnemyHp       (const _In_ INT&);
	void SetEnemyType     (const _In_ ENEMY::ENEMY_TYPE&);
	void SetFlightType    (const _In_ ENEMY::FLIGHT_TYPE&);
	void SetFlightVec     (const _In_ Vec&);
	void SetFlightSpeed   (const _In_ FLOAT&);
	void SetAccFlightSpeed(const _In_ FLOAT&);
	void SetGoAndSlowData (const _In_ GoAndSlowData&);
	void SetMoveOnlySide  (const _In_ MoveOnlySide&);
	void SetIsItemLaunched(const _In_ BOOL&);

private :

	/*
		m_IsOptionCanUse의 Setter는 만들지 않는다.
		(외부에서 Option의 사용가능여부를 변경할 수 없음)
	*/
	BOOL m_IsOptionCanUse;
	INT m_EnemyHp;
	ENEMY::ENEMY_TYPE m_EnemyType;
	ENEMY::FLIGHT_TYPE m_FlightType;
	Vec m_FlightVec;
	FLOAT m_FlightSpeed;
	FLOAT m_AccFlightSpeed;
	GoAndSlowData m_GoAndSlowData;
	MoveOnlySide m_MoveOnlySide;
	BOOL m_IsItemLaunched;
};