#include "stdafx.h"
#include "FireOption.h"

NwayShotData::NwayShotData(
	const INT shotTimes,
	const INT* shotNumberArr,
	const INT* shotAngleArr,
	const BOOL isMissileShotToPlayer)
{
	ShotTimes = shotTimes;
	for (int i = 0; i < ShotTimes; ++i)
	{
		ShotNumber[i] = shotNumberArr[i];
		ShotAngle[i] = shotAngleArr[i];
	}
	IsMissileShotToPlayer = isMissileShotToPlayer;
}

/*
	nullptr로 초기화할 경우, 아무것도 하지 않음.
*/
NwayShotData::NwayShotData(const char *)
{

}

/*
	Initialize with input data.
*/
NwayShotData & NwayShotData::operator=(const NwayShotData & data)
{
	ShotTimes = data.ShotTimes;
	for (int i = 0; i < ShotTimes; ++i)
	{
		ShotNumber[i] = data.ShotNumber[i];
		ShotAngle[i] = data.ShotAngle[i];
	}
	IsMissileShotToPlayer = data.IsMissileShotToPlayer;
	IsMissileNeedDelay = data.IsMissileNeedDelay;
	RecordShotTimes = data.RecordShotTimes;
	
	return *this;
}

/*
	들어온 NwayShotData가 유효한지를 반환해주는 함수.
	발사횟수(ShotTimes)가 적어도 1이상 maxShotTime이하여야 하고,
	ShotTimes만큼의 배열에는 의미있는 숫자가 들어가 있어야 함.
*/
BOOL NwayShotData::GetNwayShotDataValid()
{
	if (ShotTimes <= 0)
	{
		return FALSE;
	}
	for (int i = 0; i < ShotTimes; ++i)
	{
		if (ShotNumber[i] == 0 || ShotAngle[i] == 0.f)
		{
			return FALSE;
		}
	}

	return TRUE;
}


FireOption::FireOption()
	: m_IsOptionCanUse(FALSE)
{
}

FireOption::FireOption(
	const ENEMY::FIRE_TYPE& fireType,
	const ENEMY::MISSILE_TYPE& missileType,
	const ENEMY::MISSILE_SIZE& missileSize,
	const FLOAT& missileSpeed,
	const FLOAT& accMissileSpeed,
	const FLOAT& waitingTime,
	const Vec& missileVec,
	const FLOAT& initShootDelay,
	const FLOAT& intervalShootDelay,
	const FLOAT& randomRange,
	const NwayShotData& shotData)
	: m_IsOptionCanUse(TRUE)
{
	SetFireType(fireType);
	SetMissileType(missileType);
	SetMissileSize(missileSize);
	SetMissileSpeed(missileSpeed);
	SetAccMissileSpeed(accMissileSpeed);
	SetWaitingTime(waitingTime);
	SetMissileVec(missileVec);
	SetInitShootDelay(initShootDelay);
	SetIntervalShootDelay(intervalShootDelay);
	SetRandomRange(randomRange);
	SetNwayShotData(shotData);
}

FireOption::FireOption(const std::nullptr_t)
{
	m_IsOptionCanUse = FALSE;
}

FireOption::~FireOption()
{
}

FireOption & FireOption::operator=(const FireOption op)
{
	SetFireType(op.GetFireType());
	SetMissileType(op.GetMissileType());
	SetMissileSize(op.GetMissileSize());
	SetMissileSpeed(op.GetMissileSpeed());
	SetAccMissileSpeed(op.GetAccMissileSpeed());
	SetWaitingTime(op.GetWaitingTime());
	SetMissileVec(op.GetMissileVec());
	SetInitShootDelay(op.GetInitShootDelay());
	SetIntervalShootDelay(op.GetIntervalShootDelay());
	SetRandomRange(op.GetRandomRange());
	SetNwayShotData(op.GetNwayShotData());
	m_IsOptionCanUse = TRUE;
	return *this;
}

FireOption & FireOption::GetOption() 
{
	return *this;
}

/*
	Getter, Setter Zone
*/
BOOL FireOption::GetIsOptionCanUse() const
{
	return m_IsOptionCanUse;
}

ENEMY::FIRE_TYPE FireOption::GetFireType() const
{
	return m_FireType;
}

ENEMY::MISSILE_TYPE FireOption::GetMissileType() const
{
	return m_MissileType;
}

ENEMY::MISSILE_SIZE FireOption::GetMissileSize() const
{
	return m_MissileSize;
}

FLOAT FireOption::GetMissileSpeed() const
{
	return m_MissileSpeed;
}

FLOAT FireOption::GetAccMissileSpeed() const
{
	return m_AccMissileSpeed;
}

FLOAT FireOption::GetWaitingTime() const
{
	return m_WaitingTime;
}

Vec FireOption::GetMissileVec() const
{
	return m_MissileVec;
}

FLOAT FireOption::GetInitShootDelay() const
{
	return m_InitShootDelay;
}

FLOAT FireOption::GetIntervalShootDelay() const
{
	return m_IntervalShootDelay;
}

FLOAT FireOption::GetRandomRange() const
{
	return m_RandomRange;
}

NwayShotData FireOption::GetNwayShotData() const
{
	return m_NwayShotData;
}

void FireOption::SetFireType(const ENEMY::FIRE_TYPE& fireType)
{
	m_FireType = fireType;
}

void FireOption::SetMissileType(const ENEMY::MISSILE_TYPE& missileType)
{
	m_MissileType = missileType;
}

void FireOption::SetMissileSize(const ENEMY::MISSILE_SIZE& missileSize)
{
	m_MissileSize = missileSize;
}

void FireOption::SetMissileSpeed(const FLOAT& missileSpeed)
{
	m_MissileSpeed = missileSpeed;
}

void FireOption::SetAccMissileSpeed(const FLOAT& accMissileSpeed)
{
	m_AccMissileSpeed = accMissileSpeed;
}

void FireOption::SetWaitingTime(const FLOAT& waitingTime)
{
	m_WaitingTime = waitingTime;
}

void FireOption::SetMissileVec(const Vec& missileVec)
{
	m_MissileVec = missileVec;
}

void FireOption::SetInitShootDelay(const FLOAT& time)
{
	m_InitShootDelay = time;
}

void FireOption::SetIntervalShootDelay(const FLOAT& time)
{
	m_IntervalShootDelay = time;
}

void FireOption::SetRandomRange(const FLOAT& range)
{
	m_RandomRange = range;
}

void FireOption::SetNwayShotData(const NwayShotData & data)
{
	m_NwayShotData = data;
}

