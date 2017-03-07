#include "stdafx.h"
#include "Option.h"

CreateOption::CreateOption(
	const _In_opt_ BOOL  IsItemLaunched,
	const _In_opt_ FLOAT AccSpeed,
	const _In_opt_ FLOAT InitSpeed,
	const _In_opt_ FLOAT SlowSpeed,
	const _In_opt_ FLOAT SlowDistance,
	const _In_opt_ FLOAT SlowTime)
	: m_IsItemLaunched(IsItemLaunched),
	m_AccSpeed(AccSpeed),
	m_InitSpeed(InitSpeed),
	m_SlowedSpeed(SlowSpeed),
	m_DistanceToSlow(SlowDistance),
	m_SlowedTime(SlowTime)
{

}

/*
	Option 생성에 nullptr대입할 경우 Option을 사용하지 않는다는 의미.
*/
CreateOption::CreateOption(const std::nullptr_t)
{
}

CreateOption::CreateOption()
{

}

CreateOption::~CreateOption()
{

}

CreateOption & CreateOption::operator=(const _In_ CreateOption option)
{
	m_IsItemLaunched = option.m_IsItemLaunched;
	m_AccSpeed = option.m_AccSpeed;
	m_InitSpeed = option.m_InitSpeed;
	m_SlowedSpeed = option.m_SlowedSpeed;
	m_DistanceToSlow = option.m_DistanceToSlow;
	m_SlowedTime = option.m_SlowedTime;

	return *this;
}
