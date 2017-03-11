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
	// ���� ���� ���� �Ұ�.
	ExplodeArc();

	void init();
	void InitialDataSubstitude();
	void LoadInitialImg() override;

};