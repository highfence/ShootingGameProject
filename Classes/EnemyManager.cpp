#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "EnemyItem.h"
#include "EnemyZaco.h"
#include "EnemyManager.h"

EnemyManager* EnemyManager::_instance = nullptr;

// EnemyManager 싱글톤 구현.
EnemyManager* EnemyManager::getInstance()
{
	if (!_instance)
	{
		_instance = new EnemyManager();
	}
	return _instance;
}

/*
	deleteInstance
	싱글톤 소멸 함수.
*/
void EnemyManager::deleteInstance()
{
	delete _instance;
	_instance = nullptr;
	return;
}

EnemyManager::EnemyManager()
	: m_AccTime(0.f), m_RecordCreateTime(0.f)
{
	init();
}

/*
	init
	Enemy 생성 함수 포인터 핸들러에 함수를 등록해 주는 함수.
*/
void EnemyManager::init()
{
	m_pMakeHandler[ENEMY_TYPE::ENEMY_ITEM] = &EnemyManager::MakeEnemyItem;
	m_pMakeHandler[ENEMY_TYPE::ITEM] = &EnemyManager::MakeItem;
	m_pMakeHandler[ENEMY_TYPE::ENEMY_ZACO] = &EnemyManager::MakeZaco;
	return;
}

/*
	MakeEnemyItem
	EnemyItem을 만들어주는 함수 포인터에 등록될 함수.
*/
Enemy * EnemyManager::MakeEnemyItem(
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_ Vec flightVec,
	const _In_opt_ ::CreateOption flightOption)
{
	Enemy* newEnemy = new EnemyItem(createPos, flightType, flightVec, flightOption);
	return newEnemy;
}
 
/*
	MakeItem
	Item을 만드는 함수 포인터에 등록될 함수.
*/
Enemy* EnemyManager::MakeItem(
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_ Vec flightVec,
	const _In_opt_ ::CreateOption flightOption)
{
	Enemy* newEnemy = new Item(createPos, flightType, flightVec);
	return newEnemy;
}

/*
	MakeZaco
	EnemyZaco를 만드는 함수 포인터에 등록될 함수.
*/
Enemy* EnemyManager::MakeZaco(
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_ Vec flightVec,
	const _In_opt_::CreateOption flightOption)
{
	Enemy* newEnemy = new EnemyZaco(createPos, flightType, flightVec, flightOption);
	return newEnemy;
}

EnemyManager::~EnemyManager()
{
	deleteInstance();
}

void EnemyManager::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	return;
}

void EnemyManager::MakeEnemyWithTime(
	const _In_ FLOAT createTime,
	const _In_ INT enemyType,
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_opt_ Vec flightVec,
	const _In_opt_ ::CreateOption flightOption)
{
	if ((m_AccTime > createTime) && (m_RecordCreateTime < createTime))
	{
		auto newEnemy = (this->*m_pMakeHandler[enemyType])(
			createPos, flightType, flightVec, flightOption);

		m_EnemyList.push_back(newEnemy);
		m_RecordCreateTime = createTime;
	}

	return;
}

/*
	MakeEnemyOneTime
	시간에 구애받지 않고 Enemy를 생성해야만 할 때 사용하는 함수.
	기본적으로 MakeEnemyWithTime과 시간을 제외한 인자가 모두 같다.
*/
void EnemyManager::MakeEnemyOneTime(
	const _In_ INT enemyType, 
	const _In_ Vec createPos,
	const _In_ INT flightType, 
	const _In_opt_ Vec flightVec,
	const _In_opt_ ::CreateOption flightOption)
{
	auto newEnemy = (this->*m_pMakeHandler[enemyType])(
		createPos, flightType, flightVec, flightOption);

	m_EnemyList.push_back(newEnemy);
	return;
}

void EnemyManager::Draw(_Inout_ HDC drawDC)
{
	for (auto i : m_EnemyList)
	{
		if (!i->m_IsEnemyDead)
		{
			i->DrawProc(drawDC);
		}
	}

	return;
}

void EnemyManager::ClearList()
{
	std::list<Enemy*>::iterator iter = m_EnemyList.begin();
	while (iter != m_EnemyList.end())
	{
		if ((!(*iter)->CheckEnemyIsOnDisplay())
			|| ((*iter)->m_IsEnemyDead))
		{
			(*iter)->DeadProc();
			delete (*iter);
			iter = m_EnemyList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	return;
}

void EnemyManager::CalProc(const _In_ FLOAT dt)
{
	AccTime(dt);
	MakeProc();
	ClearList();
	DistributeTime(dt);
	return;
}

void EnemyManager::DrawProc(_Inout_ HDC drawDC)
{
	Draw(drawDC);
	return;
}

std::list<Enemy*>& EnemyManager::getEnemyList() 
{
	return m_EnemyList;
}

Player& EnemyManager::getPlayerInfo() 
{
	return *m_pPlayerInfo;
}

void EnemyManager::MakeProc()
{ 
	CreateOption enemyItemOptionFalse((FALSE), 0, 0, 0, 0, 0);
	CreateOption enemyItemOptionTrue((TRUE), 0, 0, 0, 0, 0);
	CreateOption flyAccelerate((FALSE), 150, 200, 0, 0, 0);
	CreateOption flyGoAndSlowItemFalse((FALSE), 0, 400, 75, 0.5f, 2.5f);
	CreateOption flyGoAndSlowItemTrue((TRUE), 0, 400, 75, 0.5f, 2.5f);

	FLOAT enemyItemCreateTime = 3.0f;
	FLOAT createIntervalTime = 0.25f;
	MakeEnemyWithTime(enemyItemCreateTime , ENEMY_ITEM, Vec(400.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowItemFalse);
	MakeEnemyWithTime(enemyItemCreateTime + 0.25f, ENEMY_ITEM, Vec(325.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowItemFalse);
	MakeEnemyWithTime(enemyItemCreateTime + 0.5f , ENEMY_ITEM, Vec(250.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowItemFalse);
	MakeEnemyWithTime(enemyItemCreateTime + 0.75f, ENEMY_ITEM, Vec(175.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowItemTrue);

	FLOAT enemyZacoCreateTime = 7.f;
	MakeEnemyWithTime(enemyZacoCreateTime, ENEMY_ZACO, Vec(winWidth, 200.f), FLY_ACCELERATE, Vec(-1, 0.7), flyAccelerate);
	MakeEnemyWithTime(enemyZacoCreateTime + 0.25f, ENEMY_ZACO, Vec(winWidth, 200.f), FLY_ACCELERATE, Vec(-1, 0.7), flyAccelerate);
	MakeEnemyWithTime(enemyZacoCreateTime + 0.5f, ENEMY_ZACO, Vec(winWidth, 200.f), FLY_ACCELERATE, Vec(-1, 0.7), flyAccelerate);
	MakeEnemyWithTime(enemyZacoCreateTime + 0.75f, ENEMY_ZACO, Vec(winWidth, 200.f), FLY_ACCELERATE, Vec(-1, 0.7), flyAccelerate);
	MakeEnemyWithTime(enemyZacoCreateTime + 1.f, ENEMY_ZACO, Vec(winWidth, 200.f), FLY_ACCELERATE, Vec(-1, 0.7), flyAccelerate);

	FLOAT enemyZacoSecondCreateTime = 7.3f;
	MakeEnemyWithTime(enemyZacoSecondCreateTime, ENEMY_ZACO, Vec(winWidth, 130.f), FLY_ACCELERATE, Vec(-1, 0.7), flyAccelerate);
	MakeEnemyWithTime(enemyZacoSecondCreateTime + 0.25f, ENEMY_ZACO, Vec(winWidth, 130.f), FLY_ACCELERATE, Vec(-1, 0.7), flyAccelerate);
	MakeEnemyWithTime(enemyZacoSecondCreateTime + 0.5f, ENEMY_ZACO, Vec(winWidth, 130.f), FLY_ACCELERATE, Vec(-1, 0.7), flyAccelerate);
	MakeEnemyWithTime(enemyZacoSecondCreateTime + 0.75f, ENEMY_ZACO, Vec(winWidth, 130.f), FLY_ACCELERATE, Vec(-1, 0.7), flyAccelerate);
	MakeEnemyWithTime(enemyZacoSecondCreateTime + 1.f, ENEMY_ZACO, Vec(winWidth, 130.f), FLY_ACCELERATE, Vec(-1, 0.7), flyAccelerate);


/*	MakeEnemyWithTime(4.0f , ENEMY_ITEM, 450, 0, FLY_STRAIGHT, FALSE);
	MakeEnemyWithTime(4.25f, ENEMY_ITEM, 550, 0, FLY_STRAIGHT, FALSE);
	MakeEnemyWithTime(4.5f , ENEMY_ITEM, 650, 0, FLY_STRAIGHT, FALSE);
	MakeEnemyWithTime(4.75f, ENEMY_ITEM, 750, 0, FLY_STRAIGHT, TRUE );
	*/
	return;
}

void EnemyManager::DistributeTime(const _In_ FLOAT dt)
{
	for (auto i : m_EnemyList)
	{
		i->CalProc(dt);
	}
	
	return;
}

void EnemyManager::DistributePlayerInfo()
{
	FLOAT x;
	FLOAT y;
	m_pPlayerInfo->GetPosition(&x, &y);
	SetPlayerPos(x, y);
	return;
}

void EnemyManager::SetPlayerPos(const _In_ FLOAT playerPosX, const _In_ FLOAT playerPosY)
{
	for (auto i : m_EnemyList)
	{
		i->m_PlayerX = playerPosX;
		i->m_PlayerY = playerPosY;
	}

	return;
}

void EnemyManager::SetPlayerInfo(Player* playerInfo)
{
	m_pPlayerInfo = playerInfo;
	return;
}
