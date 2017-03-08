#pragma once
#include "Effect.h"

class ExplodeLight : public Effect
{
public :
	ExplodeLight(const _In_ Vec);
	ExplodeLight(const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);
	~ExplodeLight();

private :
	// 인자 없이 생성 불가.
	ExplodeLight();

	void init();
	void LoadInitialImg() override;
};