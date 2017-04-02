#pragma once
#include "Effect.h"

class ExplodeSmoke : public Effect
{
public :
	ExplodeSmoke() = delete;
	ExplodeSmoke(const _In_ Vec);
	ExplodeSmoke(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);
	~ExplodeSmoke();

private :

	void init();
	void LoadInitialImg() override;
	void InitialDataSubstitude() override;
};