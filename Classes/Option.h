#pragma once

class CreateOption
{
public :
	CreateOption(
		const _In_opt_ BOOL IsItemLaunched,
		const _In_opt_ FLOAT AccSpeed,
		const _In_opt_ FLOAT InitSpeed,
		const _In_opt_ FLOAT SlowSpeed,
		const _In_opt_ FLOAT SlowDistance,
		const _In_opt_ FLOAT SlowTime);
	CreateOption(const _In_ std::nullptr_t);
	CreateOption();
	~CreateOption();

	CreateOption& operator=(const _In_ CreateOption);

	BOOL m_IsItemLaunched;
	FLOAT m_AccSpeed;
	FLOAT m_InitSpeed;
	FLOAT m_SlowedSpeed;
	FLOAT m_DistanceToSlow;
	FLOAT m_SlowedTime;


};