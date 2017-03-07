#pragma once
#include "Enemy.h"

class Item : public Enemy 
{
public :
	Item(
		const _In_ FLOAT createPosX,
		const _In_ FLOAT createPosY,
		const _In_ INT flightType,
		const _In_ Vec flightVec);
	~Item();

	virtual void CalProc(const _In_ FLOAT dt) override;
	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;
	void Fire() override;

private :

	Item();
	void init();

	BOOL CheckPlayerGetItem();
};