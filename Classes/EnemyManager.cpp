#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "EnemyItem.h"
#include "EnemyZaco.h"
#include "EnemyHandShot.h"
#include "EnemyManager.h"
#include "OptionHandler.h"

EnemyManager* EnemyManager::m_pInstance = nullptr;

// EnemyManager 싱글톤 호출 함수.
EnemyManager* EnemyManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new EnemyManager();
	}
	return m_pInstance;
}

/*
	deleteInstance
*/
void EnemyManager::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

EnemyManager::EnemyManager()
	: m_AccTime(0.f), m_RecordCreateTime(0.f), m_pPlayerInfo(nullptr)
{
	Init();
}

/*
	초기화 함수. 메모리 풀 잡아 높고 함수 포인터 등록.
*/
void EnemyManager::Init()
{
	SetEnemyMemoryPool();
	RegisterFunctionPointer();
	return;
}

/*
	�Լ� �����͸� �������ִ� �Լ�. (init���� ȣ��)
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
	EnemyItem�� �������ִ� �Լ� �����Ϳ� ���ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateEnemyItem(
	const _In_ Vec createPos,
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_ITEM);
	if (newEnemy != nullptr)
	{
		newEnemy->Activate(createPos, createOption, fireOption);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
	Item�� ������ �Լ� �����Ϳ� ���ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateItem(
	const _In_ Vec createPos,
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ITEM);
	if (newEnemy != nullptr)
	{
		newEnemy->Activate(createPos, createOption, fireOption);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
	EnemyZaco�� ������ �Լ� �����Ϳ� ���ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateZaco(
	const _In_ Vec createPos,
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_ZACO);
	if (newEnemy != nullptr)
	{
		newEnemy->Activate(createPos, createOption, fireOption);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
	EnemyHandShot�� ������ �Լ� �����Ϳ� ���ϵ� �Լ�.
*/
BOOL EnemyManager::ActivateHandShot(
	const _In_ Vec createPos,
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_HAND_SHOT);
	if (newEnemy != nullptr)
	{
		newEnemy->Activate(createPos, createOption, fireOption);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

EnemyManager::~EnemyManager()
{
	DeleteInstance();
}

void EnemyManager::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	return;
}

void EnemyManager::ActivateEnemy(
	const _In_ FLOAT activateTime,
	const _In_ Vec createPos,
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
{
	if ((m_AccTime > activateTime) && (m_RecordCreateTime < activateTime))
	{
		(this->*m_pActivateHandler[createOption.GetEnemyType()])
			(createPos, createOption, fireOption);
		m_RecordCreateTime = activateTime;
	}

	return;
}

void EnemyManager::ActivateEnemyOnce(
	const _In_ Vec createPos,
	_In_ CreateOption& createOption,
	_In_ FireOption& fireOption)
{

	(this->*m_pActivateHandler[createOption.GetEnemyType()])
		(createPos, createOption, fireOption);

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
	������ DistributeTime�� DistributePlayerInfo�� �����Ѵ�.
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
	DistributeData(dt);
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
	auto OptGenerater = OptionHandler::GetInstance();
	
	FLOAT line1 = 4.f;
	auto enemyItemFalseCreate = OptGenerater->GetCreateOption(ENEMY_ITEM_FALSE);
	auto enemyItemTrueCreate = OptGenerater->GetCreateOption(ENEMY_ITEM_TRUE);
	auto enemyItemFire = OptGenerater->GetFireOption(FIRE_FRONT);
	ActivateEnemy(line1, Vec(350.f, 0.f), enemyItemFalseCreate, enemyItemFire);
	ActivateEnemy(line1 + 0.25f, Vec(275.f, 0.f), enemyItemFalseCreate, enemyItemFire);
	ActivateEnemy(line1 + 0.50f, Vec(200.f, 0.f), enemyItemFalseCreate, enemyItemFire);
	ActivateEnemy(line1 + 0.75f, Vec(125.f, 0.f), enemyItemTrueCreate, enemyItemFire);

	FLOAT line2 = 6.f;
	auto enemyHandShotCreate = OptGenerater->GetCreateOption(ENEMY_HAND_SHOT_CREATE);
	auto enemyHandShotFire = OptGenerater->GetFireOption(N_WAY_FIRE_OPTION);
	ActivateEnemy(line2, Vec(650.f, 0.f), enemyHandShotCreate, enemyHandShotFire);

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

	AllocEnemyMemory<EnemyHandShot>(enemyHandShotAllocTime);
	AllocEnemyMemory<EnemyItem>(enemyItemAllocTime);
	AllocEnemyMemory<Item>(ItemAllocTime);
	AllocEnemyMemory<EnemyZaco>(enemyZacoAllocTime);

	return;
}

/*
	EnemyManager ������ �޸���Ǯ�� ���Ƴ��� �Լ�.
*/
template <typename T>
void EnemyManager::AllocEnemyMemory(const _In_ INT allocTime)
{
	// �Ҵ� ȸ����ŭ for���� ����
	for (int i = 0; i < allocTime; ++i)
	{
		// ������ ������ EnemyŸ���� �������� vector�� push�ϱ� ���� Enemy*�� ���·� ĳ����.
		T* newEnemy = new T();
		m_EnemyMemoryVector.push_back((Enemy*)newEnemy);
	}

	return;
}

/*
	���ڷ� ���� ENEMY_TYPE�� ��ġ�ϰ�, Activated���°� �ƴ� Enemy�� ��ȯ���ִ� �Լ�.
*/
Enemy * EnemyManager::FindDeactivatedEnemy(const ENEMY::ENEMY_TYPE findEnemyType)
{
	std::vector<Enemy*>::iterator iter = m_EnemyMemoryVector.begin();
	while (iter != m_EnemyMemoryVector.end())
	{
		// Enemy Type�� ��ġ�ϴ��� �켱 Ȯ��.
		if ((*iter)->GetEnemyType() == findEnemyType)
		{
			// Enemy�� Deactivated �������� Ȯ��.
			if (!(*iter)->GetIsEnemyActivated())
			{
				// �´ٸ� ��ȯ.
				return *iter;
			}
		}
		// �ƴ� ���� iterator�� ���� ���ҷ�.
		++iter;
	}
	// �ش��ϴ� Enemy�� ���ٸ� nullptr ��ȯ.
	return nullptr;
}

/*
	�߽� ��ġ�� ���� ���� ���̸� ���� Vec �ڷ����� ������ �׿� �浹�� Enemy�� ��ȯ���ִ� �Լ�.
	�浹�� Enemy�� ���� ���� nullptr ��ȯ.
*/
Enemy * EnemyManager::FindEnemyColideWith(const Vec position, const Vec range)
{
	for (auto& i : m_EnemyMemoryVector)
	{
		if (i->GetEnemyType() == ENEMY_TYPE::ITEM)
		{
			continue;
		}
		// Ȱ��ȭ ���� & �����ִ� ������ Enemy�� ���� �˻�.
		if (i->GetIsEnemyActivated() && !i->GetIsEnemyDead())
		{
			// �浹 �˻�
			if (IsObjectColided(position, range, i->GetPosition(), i->GetColideRange()))
			{
				// �浹���� ���� ��ȯ.
				return i;
			}
		}
	}
	return nullptr;
}
