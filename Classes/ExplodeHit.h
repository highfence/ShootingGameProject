#pragma once
#include "Effect.h"

class ExplodeHit : public Effect
{
public :
	ExplodeHit(const _In_ Vec);
	ExplodeHit(const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);
	~ExplodeHit();

private :
	// ���� ���� ���� �Ұ�.
	ExplodeHit();

	void init();
	void LoadInitialImg() override;
};