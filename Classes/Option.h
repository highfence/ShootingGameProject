#pragma once

/*
	Enemy 생성시에 들어갈 여러가지 정보를 담는 클래스.
*/

class CreateOption
{
public :
	CreateOption(
		const _In_opt_ BOOL IsItemLaunched,
		const _In_opt_ FLOAT AccSpeed,
		const _In_opt_ FLOAT InitSpeed,
		const _In_opt_ FLOAT SlowedSpeed,
		const _In_opt_ FLOAT TimeToSlow,
		const _In_opt_ FLOAT SlowedTime);
	CreateOption(const _In_ std::nullptr_t);
	CreateOption();
	~CreateOption();

	CreateOption& operator=(const _In_ CreateOption);

	BOOL m_IsItemLaunched;
	FLOAT m_AccSpeedPerSec;
	FLOAT m_InitSpeed;
	FLOAT m_SlowedSpeed;
	FLOAT m_TimeToSlow;
	FLOAT m_SlowedTime;


};