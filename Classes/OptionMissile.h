#pragma once
#include "Missile.h"

class OptionMissile : public Missile
{
public :
	OptionMissile(const _In_ PLAYER::OPTION_COLOR);
	~OptionMissile();

	void Fly(
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT) override;
	BOOL CheckColide();


private :

	void Init();
	void SmallSizeImgLoad(const _In_ BOOL);
	void NormalSizeImgLoad(const _In_ BOOL);
	void CheckMissileFlyEnough();
	void AccTime(const _In_ FLOAT);
	void MissileDestroy();

	INT m_Damage = 0;
	FLOAT m_AccTime = 0.f;
	PLAYER::OPTION_COLOR m_MissileColor = PLAYER::OPTION_COLOR::RED;

};