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
	FLOAT SlowDownStartTime;
	FLOAT SlowDownDurationTime;
	Vec SlowDownMoveVec;
	FLOAT SlowDownMoveSpeed;
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
	CreateOption(const _In_ std::nullptr_t);
	CreateOption();
	~CreateOption();

	CreateOption& operator=(const _In_ CreateOption&);

	// Getter, Setter
	BOOL               GetIsOptionCanUse() const;
	INT                GetEnemyHp()        const;
	ENEMY::ENEMY_TYPE  GetEnemyType()      const;
	ENEMY::FLIGHT_TYPE GetFlightType()     const;
	Vec                GetFlightVec()      const;
	FLOAT              GetFlightSpeed()    const;
	FLOAT              GetAccFlightSpeed() const;
	GoAndSlowData      GetGoAndSlowData()  const;
	BOOL               GetIsItemLaunched() const;

	void SetEnemyHp       (const _In_ INT&);
	void SetEnemyType     (const _In_ ENEMY::ENEMY_TYPE&);
	void SetFlightType    (const _In_ ENEMY::FLIGHT_TYPE&);
	void SetFlightVec     (const _In_ Vec&);
	void SetFlightSpeed   (const _In_ FLOAT&);
	void SetAccFlightSpeed(const _In_ FLOAT&);
	void SetGoAndSlowData (const _In_ GoAndSlowData&);
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
	BOOL m_IsItemLaunched;
};