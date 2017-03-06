#pragma once
#include "Enemy.h"

class Item : public Enemy 
{
public :
	Item(const _In_ FLOAT, const _In_ FLOAT, const _In_ INT);
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