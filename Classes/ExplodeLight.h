#pragma once
#include "Effect.h"

class ExplodeLight : public Effect
{
public :
	ExplodeLight(const _In_ FLOAT, const _In_ FLOAT);
	~ExplodeLight();

private :
	// ���� ���� ���� �Ұ�.
	ExplodeLight();

	void init();
	void LoadInitialImg() override;
};