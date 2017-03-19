#pragma once

/*
	Enemy�� Missile �����ÿ� �� ������ ��� Ŭ����.
*/

const INT maxShotTimes = 5;

struct NwayShotData
{
	NwayShotData() = default;
	NwayShotData(
		const _In_ INT maxShotTimes,
		const _In_ INT* shotNumberArr,
		const _In_ FLOAT* shotAngleArr,
		const _In_ BOOL isMissileShotToPlayer,
		const _In_ BOOL isMissileCircled);
	NwayShotData(const _In_ NwayShotData&) = default;
	NwayShotData(const _In_ char*);
	NwayShotData& operator=(const _In_ NwayShotData&);
	BOOL operator!=(const _In_ char*);
	BOOL GetNwayShotDataValid();
	
	INT ShotTimes = 0;
	INT ShotNumber[maxShotTimes] = { 0 };
	FLOAT ShotAngle[maxShotTimes] = { 0.f };
	BOOL IsMissileShotToPlayer = FALSE;
	BOOL IsMissileCircled = FALSE;

	// ��꿡 �ʿ��� ����.
	INT RecordShotTimes = 0;
	BOOL IsMissileNeedDelay = FALSE;

};

struct CircleShotData
{
	CircleShotData() = default;
	CircleShotData(
		const _In_ Vec centerPos,
		const _In_ INT missileNum,
		const _In_ FLOAT rotateDistance,
		const _In_ FLOAT initRotatePerSec,
		const _In_ FLOAT accRotatePerSec,
		const _In_ FLOAT maxRotatePerSec,
		const _In_ BOOL isRotateClockWise,
		const _In_ FLOAT rotateTime,
		const _In_ FLOAT shotSpeedWhenTheRotateEnd
		);

	CircleShotData(const _In_ CircleShotData&) = default;
	CircleShotData(const _In_ char*);
	CircleShotData& operator=(const _In_ CircleShotData&);

	Vec CenterPos = Vec(0.f, 0.f);
	INT MissileNum = 0;
	FLOAT RotateDistance = 0;
	FLOAT InitRotateAnglePerSec = 0.f;
	FLOAT AccRotateAnglePerSec = 0.f;
	FLOAT MaxRotateAngelPerSec = 0.f;
	BOOL IsRotateClockWise = TRUE;
	FLOAT RotateTime = 0.f;
	FLOAT ShotSpeedWhenTheRotateEnd = 0.f;
};

class FireOption
{
public :
	FireOption(
		const _In_ ENEMY::FIRE_TYPE& fireType,
		const _In_ ENEMY::MISSILE_TYPE& missileType,
		const _In_ ENEMY::MISSILE_SIZE& missileSize,
		const _In_ FLOAT&  missileSpeed,
		const _In_ FLOAT&  accMissileSpeed,
		const _In_ FLOAT&  waitingTime,
		const _In_ Vec&  missileVec,
		const _In_ FLOAT&  initShootDelay,
		const _In_ FLOAT&  intervalShootDelay,
		const _In_ INT&	missileNumber,
		const _In_ FLOAT&  randomRange,
		const _In_ NwayShotData& shotData);
	FireOption(const _In_ std::nullptr_t);
	FireOption();
	~FireOption();

	FireOption& operator=(const _In_ FireOption);

	/*
		Getter, Setter
	*/
	FireOption&			GetOption();
	BOOL                GetIsOptionCanUse()     const;
	ENEMY::FIRE_TYPE    GetFireType()           const;
	ENEMY::MISSILE_TYPE GetMissileType()        const;
	ENEMY::MISSILE_SIZE GetMissileSize()        const;
	FLOAT               GetMissileSpeed()       const;
	FLOAT               GetAccMissileSpeed()    const;
	FLOAT               GetWaitingTime()        const;
	Vec                 GetMissileVec()         const;
	FLOAT               GetInitShootDelay()     const;
	FLOAT               GetIntervalShootDelay() const;
	INT					GetMissileShotNumber()  const;
	FLOAT               GetRandomRange()        const;
	NwayShotData        GetNwayShotData()       const;
	CircleShotData		GetCircleShotDate()		const;

	void SetFireType          (const _In_ ENEMY::FIRE_TYPE&);
	void SetMissileType       (const _In_ ENEMY::MISSILE_TYPE&);
	void SetMissileSize       (const _In_ ENEMY::MISSILE_SIZE&);
	void SetMissileSpeed      (const _In_ FLOAT&);
	void SetAccMissileSpeed   (const _In_ FLOAT&);
	void SetWaitingTime       (const _In_ FLOAT&);
	void SetMissileVec        (const _In_ Vec&);
	void SetInitShootDelay    (const _In_ FLOAT&);
	void SetIntervalShootDelay(const _In_ FLOAT&);
	void SetMissileShotNumber (const _In_ INT&);
	void SetRandomRange       (const _In_ FLOAT&);
	void SetNwayShotData      (const _In_ NwayShotData&);
	void SetCircleShotData	  (const _In_ CircleShotData&);


private :

	/*
		IsOptionCanUse�� ���� ���θ� �ܺο��� ������ �� ������ Setter�� ������ �ʴ´�.	
	*/
	BOOL m_IsOptionCanUse;
	ENEMY::FIRE_TYPE m_FireType;
	ENEMY::MISSILE_TYPE m_MissileType;
	ENEMY::MISSILE_SIZE m_MissileSize;
	FLOAT m_MissileSpeed;
	FLOAT m_AccMissileSpeed;
	FLOAT m_WaitingTime;
	Vec m_MissileVec;
	FLOAT m_InitShootDelay;
	FLOAT m_IntervalShootDelay;
	INT	  m_MissileShootNumber;
	FLOAT m_RandomRange;
	NwayShotData m_NwayShotData;
	CircleShotData m_CircleShotData;

};