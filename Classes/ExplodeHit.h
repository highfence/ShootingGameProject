#pragma once
#include "Effect.h"

class ExplodeHit : public Effect
{
public :
	ExplodeHit() = delete;
	ExplodeHit(const _In_ Vec);
	ExplodeHit(const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);
	~ExplodeHit();

private :

	void init();
	void LoadInitialImg() override;
	void InitialDataSubstitude() override;
};