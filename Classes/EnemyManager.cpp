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
	: m_AccTime(0.f), m_RecordCreateTime(0.f), m_pPlayerInfo(nullptr)
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
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_ITEM);
	newEnemy->Activate(createOption, fireOption);
	return TRUE;
}
 
/*
	Item�� ����� �Լ� �����Ϳ� ��ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateItem(
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ITEM);
	newEnemy->Activate(createOption, fireOption);
	return TRUE;
}

/*
	EnemyZaco�� ����� �Լ� �����Ϳ� ��ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateZaco(
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_ZACO);
	newEnemy->Activate(createOption, fireOption);
	return TRUE;
}

/*
	EnemyHandShot�� ����� �Լ� �����Ϳ� ��ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateHandShot(
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
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
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
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

/*
	Ȱ��ȭ �� Enemy�鿡�� ������ �������ִ� �Լ�.
	������ DistributeTime�� DistributePlayerInfo�� ����Ѵ�.
*/
void EnemyManager::DistributeData(const FLOAT dt)
{
	Vec playerPos;
	m_pPlayerInfo->GetPosition(&playerPos);

	for (auto i : m_EnemyMemoryVector)
	{
		if (i->GetIsEnemyActivated())
		{
			i->SetPlayerPos(playerPos);
			i->CalcProc(dt);
		}
	}
}

void EnemyManager::CalcProc(const _In_ FLOAT dt)
{
	AccTime(dt);
	MakeProc();
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

void EnemyManager::MakeProc()
{
	return;
}

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

void EnemyManager::SetPlayerInfo(Player& playerInfo)
{
	m_pPlayerInfo = &playerInfo;
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
		if ((*iter)->GetCreateOption().GetEnemyType() == findEnemyType)
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
