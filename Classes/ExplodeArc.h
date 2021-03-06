#pragma once
#include "Effect.h"

class ExplodeArc : public Effect
{
public:
	ExplodeArc() = delete;
	ExplodeArc(const _In_ Vec);
	ExplodeArc(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);
	~ExplodeArc();

private:

	void Init();
	void InitialDataSubstitude() override;
	void LoadInitialImg() override;

};