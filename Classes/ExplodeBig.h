#pragma once
#include "Effect.h"

class ExplodeBig : public Effect
{
public :
	ExplodeBig() = delete;
	ExplodeBig(const _In_ Vec);
	ExplodeBig(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);
	~ExplodeBig() = default;

private :

	void Init();
	void InitialDataSubstitude() override;
	void LoadInitialImg() override;

};