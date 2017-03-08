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
	// 인자 없이 생성 불가.
	ExplodeHit();

	void init();
	void LoadInitialImg() override;
};