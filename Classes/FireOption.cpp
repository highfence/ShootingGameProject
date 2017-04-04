#include "stdafx.h"
#include "FireOption.h"

NwayShotData::NwayShotData(
	const INT shotTimes,
	const INT* shotNumberArr,
	const FLOAT* shotAngleArr,
	const BOOL isMissileShotToPlayer,
	const BOOL isMissileCircled)
{
	// shotNumberArr이 널포인터일 경우 잘못된 진입.
	if (shotNumberArr == nullptr)
	{
		return;
	}

	m_ShotTimes = shotTimes;
	for (int i = 0; i < m_ShotTimes; ++i)
	{
		m_ShotNumber[i] = shotNumberArr[i];
	}
	// ShotAngle은 널포인터가 들어올 수 있음.
	if (shotAngleArr != nullptr)
	{
		for (int i = 0; i < m_ShotTimes; ++i)
		{
			m_ShotAngle[i] = shotAngleArr[i];
		}
	}

	m_IsMissileShotToPlayer = isMissileShotToPlayer;
	m_IsMissileCircled = isMissileCircled;
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
	m_ShotTimes = data.m_ShotTimes;
	for (int i = 0; i < m_ShotTimes; ++i)
	{
		m_ShotNumber[i] = data.m_ShotNumber[i];
		m_ShotAngle[i] = data.m_ShotAngle[i];
	}
	m_IsMissileShotToPlayer = data.m_IsMissileShotToPlayer;
	m_IsMissileCircled = data.m_IsMissileCircled;
	m_IsMissileNeedDelay = data.m_IsMissileNeedDelay;
	m_RecordShotTimes = data.m_RecordShotTimes;
	
	return *this;
}

/*
	널 포인터와의 비교를 위해 만들어진 연산자 오버로딩
*/
BOOL NwayShotData::operator!=(const char *null)
{
	// ShotTimes가 0인 경우 nullptr과 같다고 인식하여 FALSE반환.
	if (m_ShotTimes == 0)
	{
		return FALSE;
	}
	// 아니라면 같지 않으므로 TRUE반환.
	return TRUE;
}

/*
	들어온 NwayShotData가 유효한지를 반환해주는 함수.
	발사횟수(ShotTimes)가 적어도 1이상 maxShotTime이하여야 하고,
	ShotTimes만큼의 배열에는 의미있는 숫자가 들어가 있어야 함.
*/
BOOL NwayShotData::GetNwayShotDataValid()
{
	if (m_ShotTimes <= 0)
	{
		return FALSE;
	}
	for (int i = 0; i < m_ShotTimes; ++i)
	{
		if (m_ShotNumber[i] == 0)
		{
			return FALSE;
		}
	}

	return TRUE;
}

CircleShotData::CircleShotData(
	const Vec centerPos,
	const INT missileNum,
	const FLOAT radius,
	const FLOAT theta,
	const FLOAT initRotatePerSec,
	const FLOAT accRotatePerSec,
	const FLOAT maxRotatePerSec,
	const BOOL isRotateClockWise,
	const FLOAT rotateTime,
	const FLOAT shotSpeedWhenTheRotateEnd)
{
	m_CenterPos = centerPos;
	m_MissileNum = missileNum;
	m_Radius = radius;
	m_Theta = theta;
	m_InitRotateAnglePerSec = initRotatePerSec;
	m_AccRotateAnglePerSec = accRotatePerSec;
	m_MaxRotateAngelPerSec = maxRotatePerSec;
	m_IsRotateClockWise = isRotateClockWise;
	m_RotateTime = rotateTime;
	m_ShotSpeedWhenTheRotateEnd = shotSpeedWhenTheRotateEnd;
}

CircleShotData & CircleShotData::operator=(const CircleShotData & dt)
{
	m_CenterPos = dt.m_CenterPos;
	m_MissileNum = dt.m_MissileNum;
	m_Radius = dt.m_Radius;
	m_Theta = dt.m_Theta;
	m_InitRotateAnglePerSec = dt.m_InitRotateAnglePerSec;
	m_AccRotateAnglePerSec = dt.m_AccRotateAnglePerSec;
	m_MaxRotateAngelPerSec = dt.m_MaxRotateAngelPerSec;
	m_IsRotateClockWise = dt.m_IsRotateClockWise;
	m_RotateTime = dt.m_RotateTime;
	m_ShotSpeedWhenTheRotateEnd = dt.m_ShotSpeedWhenTheRotateEnd;
	m_RecordRotateTime = dt.m_RecordRotateTime;
	m_IsMissileNeedDelay = dt.m_IsMissileNeedDelay;
	return *this;
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
	const INT& missileNumber,
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
	SetMissileShotNumber(missileNumber);
	SetRandomRange(randomRange);
	SetNwayShotData(shotData);
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
	const INT& missileNumber,
	const FLOAT& randomRange,
	const CircleShotData& shotData)
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
	SetMissileShotNumber(missileNumber);
	SetRandomRange(randomRange);
	SetCircleShotData(shotData);
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
	SetMissileShotNumber(op.GetMissileShotNumber());
	SetRandomRange(op.GetRandomRange());
	SetNwayShotData(op.GetNwayShotData());
	SetCircleShotData(op.GetCircleShotData());
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

INT FireOption::GetMissileShotNumber() const
{
	return m_MissileShootNumber;
}

FLOAT FireOption::GetRandomRange() const
{
	return m_RandomRange;
}

NwayShotData FireOption::GetNwayShotData() const
{
	return m_NwayShotData;
}

CircleShotData FireOption::GetCircleShotData() const
{
	return m_CircleShotData;
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
	m_MissileVec.x = missileVec.x;
	m_MissileVec.y = missileVec.y;
}

void FireOption::SetInitShootDelay(const FLOAT& time)
{
	m_InitShootDelay = time;
}

void FireOption::SetIntervalShootDelay(const FLOAT& time)
{
	m_IntervalShootDelay = time;
}

void FireOption::SetMissileShotNumber(const INT & number)
{
	m_MissileShootNumber = number;
}

void FireOption::SetRandomRange(const FLOAT& range)
{
	m_RandomRange = range;
}

void FireOption::SetNwayShotData(const NwayShotData & data)
{
	m_NwayShotData = data;
}

void FireOption::SetCircleShotData(const CircleShotData & data)
{
	m_CircleShotData = data;
}

