#pragma once

/*
	Enemy �����ÿ� �� �������� ������ ��� Ŭ����.
*/

typedef struct GoAndSlowData
{
	GoAndSlowData();
	GoAndSlowData(
		const _In_ FLOAT slowDownStartTime,
		const _In_ FLOAT slowDownDurationTime,
		const _In_ Vec slowDonwMoveVec,
		const _In_ FLOAT slowDownMoveSpeed
	);
	GoAndSlowData& operator=(const GoAndSlowData);
	FLOAT SlowDownStartTime;
	FLOAT SlowDownDurationTime;
	Vec SlowDownMoveVec;
	FLOAT SlowDownMoveSpeed;
};

class CreateOption
{
public :
	CreateOption(
		const _In_ Vec createPos,
		const _In_ ENEMY::ENEMY_TYPE enemyType,
		const _In_ ENEMY::FLIGHT_TYPE flightType,
		const _In_ Vec flightVec,
		const _In_ FLOAT flightSpeed,
		const _In_ FLOAT accFlightSpeed,
		const _In_ GoAndSlowData goAndSlowData);
	CreateOption();
	~CreateOption();

	CreateOption& operator=(const _In_ CreateOption);

	// Getter, Setter
	BOOL GetIsOptionCanUse() const;
	Vec GetCreatePos() const;
	ENEMY::ENEMY_TYPE GetEnemyType() const;
	ENEMY::FLIGHT_TYPE GetFlightType() const;
	Vec GetFlightVec() const;
	FLOAT GetFlightSpeed() const;
	FLOAT GetAccFlightSpeed() const;
	GoAndSlowData GetGoAndSlowData() const;

	void SetCreatePos(const _In_ Vec);
	void SetEnemyType(const _In_ ENEMY::ENEMY_TYPE);
	void SetFlightType(const _In_ ENEMY::FLIGHT_TYPE);
	void SetFlightVec(const _In_ Vec);
	void SetFlightSpeed(const _In_ FLOAT);
	void SetAccFlightSpeed(const _In_ FLOAT);
	void SetGoAndSlowData(const _In_ GoAndSlowData);

private :

	/*
		m_IsOptionCanUse�� Setter�� ������ �ʴ´�.
		(�ܺο��� Option�� ��밡�ɿ��θ� ������ �� ����)
	*/
	BOOL m_IsOptionCanUse;
	Vec m_CreatePosition;
	ENEMY::ENEMY_TYPE m_EnemyType;
	ENEMY::FLIGHT_TYPE m_FlightType;
	Vec m_FlightVec;
	FLOAT m_FlightSpeed;
	FLOAT m_AccFlightSpeed;
	GoAndSlowData m_GoAndSlowData;
};