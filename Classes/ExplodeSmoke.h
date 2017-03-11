#pragma once
#include "Effect.h"

class ExplodeSmoke : public Effect
{
public :
	ExplodeSmoke(const _In_ Vec);
	ExplodeSmoke(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);
	~ExplodeSmoke();

private :
	ExplodeSmoke();

	void init();
	void InitialDataSubstitude();
	void LoadInitialImg() override;
};