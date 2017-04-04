#pragma once

/*
	Enemy의 Missile 생성시에 들어갈 정보를 담는 클래스.
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
	
	INT m_ShotTimes = 0;
	INT m_ShotNumber[maxShotTimes] = { 0 };
	FLOAT m_ShotAngle[maxShotTimes] = { 0.f };
	BOOL m_IsMissileShotToPlayer = FALSE;
	BOOL m_IsMissileCircled = FALSE;

	// 계산에 필요한 인자.
	INT m_RecordShotTimes = 0;
	BOOL m_IsMissileNeedDelay = FALSE;

};

struct CircleShotData
{
	CircleShotData() = default;
	CircleShotData(
		const _In_ Vec centerPos,
		const _In_ INT missileNum,
		const _In_ FLOAT radius,
		const _In_ FLOAT theta,
		const _In_ FLOAT initRotatePerSec,
		const _In_ FLOAT accRotatePerSec,
		const _In_ FLOAT maxRotatePerSec,
		const _In_ BOOL isRotateClockWise,
		const _In_ FLOAT rotateTime,
		const _In_ FLOAT shotSpeedWhenTheRotateEnd
		);

	CircleShotData(const _In_ CircleShotData&) = default;
	CircleShotData& operator=(const _In_ CircleShotData&);
	void SetCenterPos(const _In_ Vec& pos) { m_CenterPos = pos; };
	void SetTheta(const _In_ FLOAT& theta) { m_Theta = theta; };

	Vec m_CenterPos = Vec(0.f, 0.f);
	INT m_MissileNum = 0;
	FLOAT m_Radius = 0;
	FLOAT m_Theta = 0.f;
	FLOAT m_InitRotateAnglePerSec = 0.f;
	FLOAT m_AccRotateAnglePerSec = 0.f;
	FLOAT m_MaxRotateAngelPerSec = 0.f;
	BOOL m_IsRotateClockWise = TRUE;
	FLOAT m_RotateTime = 0.f;
	FLOAT m_ShotSpeedWhenTheRotateEnd = 0.f;

	// 내부 계산용 멤버.
	FLOAT m_RecordRotateTime = 0.f;
	BOOL m_IsMissileNeedDelay = FALSE;
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
		const _In_ CircleShotData& shotData);
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
	CircleShotData		GetCircleShotData()		const;

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
		IsOptionCanUse에 대한 여부를 외부에서 지정할 수 없도록 Setter를 만들지 않는다.	
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