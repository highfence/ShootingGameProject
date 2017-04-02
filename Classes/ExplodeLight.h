#pragma once
#include "Effect.h"

class ExplodeLight : public Effect
{
public :
	ExplodeLight() = delete;
	ExplodeLight(const _In_ Vec);
	ExplodeLight(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);
	~ExplodeLight();

private :

	void init();
	void LoadInitialImg() override;
	void InitialDataSubstitude() override;
};