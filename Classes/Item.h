#pragma once
#include "Enemy.h"

class Item : public Enemy 
{
public :
	Item(void);

	~Item();

	virtual void CalcProc(const _In_ FLOAT dt) override;
	void Draw(_Inout_ HDC) override;
	void Explode() override;
	void DeadProc() override;
	//void Fire() override;

private :

	void init();

	BOOL CheckPlayerGetItem();
};