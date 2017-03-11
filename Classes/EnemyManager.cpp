#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "EnemyItem.h"
#include "EnemyZaco.h"
#include "EnemyHandShot.h"
#include "EnemyManager.h"

EnemyManager* EnemyManager::_instance = nullptr;

// EnemyManager �̱��� ����.
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
	�̱��� �Ҹ� �Լ�.
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
	Enemy ���� �Լ� ������ �ڵ鷯�� �Լ��� ����� �ִ� �Լ�.
*/
void EnemyManager::init()
{
	SetEnemyMemoryPool();
	RegisterFunctionPointer();
	return;
}

/*
	�Լ� �����͸� ������ִ� �Լ�. (init���� ȣ��)
*/
void EnemyManager::RegisterFunctionPointer()
{
	m_pActivateHandler[ENEMY_TYPE::ENEMY_ITEM] = &EnemyManager::ActivateEnemyItem;
	m_pActivateHandler[ENEMY_TYPE::ITEM] = &EnemyManager::ActivateItem;
	m_pActivateHandler[ENEMY_TYPE::ENEMY_ZACO] = &EnemyManager::ActivateZaco;
	m_pActivateHandler[ENEMY_TYPE::ENEMY_HAND_SHOT] = &EnemyManager::ActivateHandShot;
	return;
}

/*
	EnemyItem�� ������ִ� �Լ� �����Ϳ� ��ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateEnemyItem(
	const _In_ CreateOption createOption,
	const _In_ FireOption fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_ITEM);
	newEnemy->Activate(createOption, fireOption);
	return TRUE;
}
 
/*
	Item�� ����� �Լ� �����Ϳ� ��ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateItem(
	const _In_ CreateOption createOption,
	const _In_ FireOption fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ITEM);
	newEnemy->Activate(createOption, fireOption);
	return TRUE;
}

/*
	EnemyZaco�� ����� �Լ� �����Ϳ� ��ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateZaco(
	const _In_ CreateOption createOption,
	const _In_ FireOption fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_ZACO);
	newEnemy->Activate(createOption, fireOption);
	return TRUE;
}

/*
	EnemyHandShot�� ����� �Լ� �����Ϳ� ��ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateHandShot(
	const _In_ CreateOption createOption,
	const _In_ FireOption fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_HAND_SHOT);
	newEnemy->Activate(createOption, fireOption);
	return TRUE;
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

void EnemyManager::ActivateEnemy(
	const _In_ FLOAT activateTime,
	const _In_ CreateOption createOption,
	const _In_opt_ FireOption fireOption)
{
	if ((m_AccTime > activateTime) && (m_RecordCreateTime < activateTime))
	{
		(this->*m_pActivateHandler[createOption.GetEnemyType()])(createOption, fireOption);
	}

	return;
}

void EnemyManager::Draw(_Inout_ HDC drawDC)
{
	for (auto i : m_EnemyMemoryVector)
	{
		i->DrawProc(drawDC);
	}

	return;
}

void EnemyManager::CalcProc(const _In_ FLOAT dt)
{
	AccTime(dt);
	//MakeProc();
	DistributeTime(dt);
	DistributePlayerInfo();
	return;
}

void EnemyManager::DrawProc(_Inout_ HDC drawDC)
{
#ifdef _DEBUG
	//SetTextAlign(drawDC, TA_LEFT);
	//std::wstring DebugLabel = _T("Enemy List Size : ") + std::to_wstring(m_EnemyList.size());
	//TextOut(drawDC, 10, 10, DebugLabel.c_str(), wcslen(DebugLabel.c_str()));
#endif
	Draw(drawDC);
	return;
}

Player& EnemyManager::getPlayerInfo() 
{
	return *m_pPlayerInfo;
}

/*
void EnemyManager::MakeProc()
{ 
	CreateOption enemyItemOptionFalse((FALSE), 0, 0, 0, 0, 0);
	CreateOption enemyItemOptionTrue((TRUE), 0, 0, 0, 0, 0);
	CreateOption flyAccelerate((FALSE), 150, 200, 0, 0, 0);
	CreateOption flyGoAndSlowItemFalse((FALSE), 0, 400, 75, 0.5f, 2.5f);
	CreateOption flyGoAndSlowItemTrue((TRUE), 0, 400, 75, 0.5f, 2.5f);
	CreateOption flyGoAndSlowQuiteLong((FALSE), 0, 400, 30, 0.3f, 15.f);

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

	FLOAT enemyZacoThirdCreateTime = 9.4f;
	MakeEnemyWithTime(enemyZacoThirdCreateTime, ENEMY_ZACO, Vec(400.f, 0.f), FLY_STRAIGHT, Vec(0.f, 1.f), enemyItemOptionFalse);
	MakeEnemyWithTime(enemyZacoThirdCreateTime + 0.25f, ENEMY_ZACO, Vec(400.f, 0.f), FLY_STRAIGHT, Vec(0.f, 1.f), enemyItemOptionFalse);
	MakeEnemyWithTime(enemyZacoThirdCreateTime + 0.5f, ENEMY_ZACO, Vec(400.f, 0.f), FLY_STRAIGHT, Vec(0.f, 1.f), enemyItemOptionFalse);
	MakeEnemyWithTime(enemyZacoThirdCreateTime + 0.75f, ENEMY_ZACO, Vec(400.f, 0.f), FLY_STRAIGHT, Vec(0.f, 1.f), enemyItemOptionFalse);
	MakeEnemyWithTime(enemyZacoThirdCreateTime + 1.f, ENEMY_ZACO, Vec(400.f, 0.f), FLY_STRAIGHT, Vec(0.f, 1.f), enemyItemOptionFalse);
	MakeEnemyWithTime(enemyZacoThirdCreateTime + 0.01f, ENEMY_ZACO, Vec(320.f, 0.f), FLY_STRAIGHT, Vec(0.f, 1.f), enemyItemOptionFalse);
	MakeEnemyWithTime(enemyZacoThirdCreateTime + 0.26f, ENEMY_ZACO, Vec(320.f, 0.f), FLY_STRAIGHT, Vec(0.f, 1.f), enemyItemOptionFalse);
	MakeEnemyWithTime(enemyZacoThirdCreateTime + 0.51f, ENEMY_ZACO, Vec(320.f, 0.f), FLY_STRAIGHT, Vec(0.f, 1.f), enemyItemOptionFalse);
	MakeEnemyWithTime(enemyZacoThirdCreateTime + 0.76f, ENEMY_ZACO, Vec(320.f, 0.f), FLY_STRAIGHT, Vec(0.f, 1.f), enemyItemOptionFalse);
	MakeEnemyWithTime(enemyZacoThirdCreateTime + 1.01f, ENEMY_ZACO, Vec(320.f, 0.f), FLY_STRAIGHT, Vec(0.f, 1.f), enemyItemOptionFalse);

	FLOAT enemyHandShotCreateTime = 15.f;
	MakeEnemyWithTime(enemyHandShotCreateTime, ENEMY_HAND_SHOT, Vec(650.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowQuiteLong);
	MakeEnemyWithTime(enemyHandShotCreateTime + 4.f, ENEMY_HAND_SHOT, Vec(250.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowQuiteLong);
	MakeEnemyWithTime(enemyHandShotCreateTime + 7.5f, ENEMY_HAND_SHOT, Vec(550.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowQuiteLong);

	FLOAT enemyItemSecondCreateTime = 19.5f;
	MakeEnemyWithTime(enemyItemSecondCreateTime, ENEMY_ITEM, Vec(450.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowItemFalse);
	MakeEnemyWithTime(enemyItemSecondCreateTime + 0.25f, ENEMY_ITEM, Vec(525.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowItemFalse);
	MakeEnemyWithTime(enemyItemSecondCreateTime + 0.5f, ENEMY_ITEM, Vec(600.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowItemFalse);
	MakeEnemyWithTime(enemyItemSecondCreateTime + 0.75f, ENEMY_ITEM, Vec(675.f, 0.f), FLY_GO_AND_SLOW, Vec(0, 1), flyGoAndSlowItemTrue);


	return;
}
*/

/*
	�� Enemy�� CalcProc�� �����Ű�� �Լ�.
*/
void EnemyManager::DistributeTime(const _In_ FLOAT dt)
{
	for (auto i : m_EnemyMemoryVector)
	{
		i->CalcProc(dt);
	}
	
	return;
}

void EnemyManager::DistributePlayerInfo()
{
	Vec playerPos;
	m_pPlayerInfo->GetPosition(&playerPos);
	SetPlayerPos(playerPos);
	return;
}

/*
	GameManager�κ��� �Է¹��� player�� ��ġ ������ �������ִ� �Լ�.
*/
void EnemyManager::SetPlayerPos(const _In_ Vec playerPos)
{
	for (auto i : m_EnemyMemoryVector)
	{
		i->m_PlayerPos = playerPos;
	}

	return;
}

void EnemyManager::SetPlayerInfo(Player* playerInfo)
{
	m_pPlayerInfo = playerInfo;
	return;
}

/*
	������ Enemy Ÿ�Ժ� ������ŭ ���Ϳ� �̸� �Ҵ��س��� �Լ�.
*/
void EnemyManager::SetEnemyMemoryPool()
{
	const INT enemyItemAllocTime = 5;
	const INT ItemAllocTime = 3;
	const INT enemyZacoAllocTime = 15;
	const INT enemyHandShotAllocTime = 5;

	AllocEnemyMemory<EnemyItem>(enemyItemAllocTime);
	AllocEnemyMemory<Item>(ItemAllocTime);
	AllocEnemyMemory<EnemyZaco>(enemyZacoAllocTime);
	AllocEnemyMemory<EnemyHandShot>(enemyHandShotAllocTime);

	return;
}

/*
	EnemyManager ������ �޸�Ǯ�� ��Ƴ��� �Լ�.
*/
template <typename T>
void EnemyManager::AllocEnemyMemory(const _In_ INT allocTime)
{
	// �Ҵ� ȸ����ŭ for���� ����
	for (int i = 0; i < allocTime; ++i)
	{
		// ������ ���ø� �������� vector���� Enemy*�� ���·� ĳ����.
		T* newEnemy = new T();
		m_EnemyMemoryVector.push_back((Enemy*)newEnemy);
	}
	
	return;
}

/*
	���ڷ� ���� ENEMY_TYPE�� �°�, Activated���°� �ƴ� Enemy�� ��ȯ���ִ� �Լ�. 
*/
Enemy * EnemyManager::FindDeactivatedEnemy(const ENEMY::ENEMY_TYPE findEnemyType)
{
	std::vector<Enemy*>::iterator iter = m_EnemyMemoryVector.begin();
	while (iter != m_EnemyMemoryVector.end())
	{
		// Enemy Type�� ��ġ�ϴ��� �켱 Ȯ��.
		if ((*iter)->GetCreateOption().GetEnemyType == findEnemyType)
		{
			// Enemy�� Deactivated �������� Ȯ��.
			if (!(*iter)->GetIsEnemyActivated())
			{
				// �´ٸ� ��ȯ.
				return *iter;
			}
		}
		// �ƴ� ��� iterator�� ���� ���ҷ�. 
		++iter;
	}
	// �ش��ϴ� Enemy�� ���ٸ� nullptr ��ȯ.
	return nullptr;
}

/*
	�߽� ��ġ�� ���� ���� ���̸� ���� Vec �ڷ����� ������ �׿� �浹�� Enemy�� ��ȯ���ִ� �Լ�.
	�浹�� Enemy�� ���� ��� nullptr ��ȯ.
*/
Enemy * EnemyManager::FindEnemyColideWith(const Vec position, const Vec range)
{
	for (auto i : m_EnemyMemoryVector)
	{
		// Ȱ��ȭ ������ Enemy�� ���� �˻�.
		if (i->GetIsEnemyActivated())
		{
			// �浹 �˻�
			if (IsObjectColided(position, range, i->GetPosition(), i->GetColideRange()))
			{
				// �浹���� ��� ��ȯ.
				return i;
			}
		}
	}
	return nullptr;
}
