#pragma once
#include "Effect.h"

class ExplodeArc : public Effect
{
public:
	ExplodeArc(const _In_ Vec);
	ExplodeArc(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);
	~ExplodeArc();

private:
	// 인자 없이 생성 불가.
	ExplodeArc();

	void init();
	void InitialDataSubstitude();
	void LoadInitialImg() override;

};