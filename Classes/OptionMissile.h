#pragma once
#include "Missile.h"

class OptionMissile : public Missile
{
public :
	OptionMissile();
	~OptionMissile();

	void Fly(
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT,
		const _In_ FLOAT) override;



private :

	void init();



};