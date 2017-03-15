#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "EnemyItem.h"
#include "EnemyZaco.h"
#include "EnemyHandShot.h"
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
	: m_AccTime(0.f), m_RecordCreateTime(0.f), m_pPlayerInfo(nullptr)
{
	init();
}

/*
	Enemy 생성 함수 포인터 핸들러에 함수를 등록해 주는 함수.
*/
void EnemyManager::init()
{
	SetEnemyMemoryPool();
	RegisterFunctionPointer();
	return;
}

/*
	함수 포인터를 등록해주는 함수. (init에서 호출)
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
	EnemyItem을 만들어주는 함수 포인터에 등록될 함수.
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
	Item을 만드는 함수 포인터에 등록될 함수.
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
	EnemyZaco를 만드는 함수 포인터에 등록될 함수.
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
	EnemyHandShot를 만드는 함수 포인터에 등록될 함수.
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
	deleteInstance();
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
	활성화 된 Enemy들에게 정보를 전파해주는 함수.
	이전의 DistributeTime과 DistributePlayerInfo를 계승한다.
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
	GoAndSlowData enemyItemData = GoAndSlowData(0.5f, 5.f, Vec(0.f, 1.f), 50.f);
	CreateOption enemyItemNormal = CreateOption(1, ENEMY_ITEM, FLY_GO_AND_SLOW, Vec(0, 1), 300.f, 0.f, enemyItemData, FALSE);
	CreateOption enemyItemLaunched = CreateOption(1, ENEMY_ITEM, FLY_GO_AND_SLOW, Vec(0, 1), 300.f, 0.f, enemyItemData, TRUE);
	FireOption enemyFireFront = FireOption(FIRE_TYPE::NORMAL_FIRE, MISSILE_TYPE::STRAIGHT_FIRE, SMALL, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 1.5f, 1.5f, 0.f, 0);
	FireOption enemyFireAimed = FireOption(FIRE_TYPE::AIMED_FIRE, MISSILE_TYPE::STRAIGHT_FIRE, SMALL, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 1.5f, 1.5f, 50.f, 0);

	FLOAT line1 = 4.f;
	ActivateEnemy(line1, Vec(350.f, 0.f), enemyItemNormal, enemyFireAimed);
	ActivateEnemy(line1 + 0.25f, Vec(275.f, 0.f), enemyItemNormal, enemyFireAimed);
	ActivateEnemy(line1 + 0.50f, Vec(200.f, 0.f), enemyItemNormal, enemyFireAimed);
	ActivateEnemy(line1 + 0.75f, Vec(125.f, 0.f), enemyItemLaunched, enemyFireAimed);
	return;
}

void EnemyManager::SetPlayerInfo(Player& playerInfo)
{
	m_pPlayerInfo = &playerInfo;
	return;
}

/*
	일정한 Enemy 타입별 개수만큼 벡터에 미리 할당해놓는 함수.
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
	EnemyManager 생성시 메모리풀을 잡아놓는 함수.
*/
template <typename T>
void EnemyManager::AllocEnemyMemory(const _In_ INT allocTime)
{
	// 할당 회수만큼 for문을 루프
	for (int i = 0; i < allocTime; ++i)
	{
		// 생성은 각각의 Enemy타입의 형태지만 vector에 push하기 위해 Enemy*의 형태로 캐스팅.
		T* newEnemy = new T();
		m_EnemyMemoryVector.push_back((Enemy*)newEnemy);
	}
	
	return;
}

/*
	인자로 받은 ENEMY_TYPE과 일치하고, Activated상태가 아닌 Enemy를 반환해주는 함수. 
*/
Enemy * EnemyManager::FindDeactivatedEnemy(const ENEMY::ENEMY_TYPE findEnemyType)
{
	std::vector<Enemy*>::iterator iter = m_EnemyMemoryVector.begin();
	while (iter != m_EnemyMemoryVector.end())
	{
		// Enemy Type이 일치하는지 우선 확인.
		if ((*iter)->GetEnemyType() == findEnemyType)
		{
			// Enemy가 Deactivated 상태인지 확인.
			if (!(*iter)->GetIsEnemyActivated())
			{
				// 맞다면 반환.
				return *iter;
			}
		}
		// 아닐 경우 iterator를 다음 원소로. 
		++iter;
	}
	// 해당하는 Enemy가 없다면 nullptr 반환.
	return nullptr;
}

/*
	중심 위치와 가로 세로 길이를 가진 Vec 자료형을 넣으면 그와 충돌한 Enemy를 반환해주는 함수.
	충돌한 Enemy가 없을 경우 nullptr 반환.
*/
Enemy * EnemyManager::FindEnemyColideWith(const Vec position, const Vec range)
{
	for (auto& i : m_EnemyMemoryVector)
	{
		// 활성화 상태 & 살아있는 상태인 Enemy만 조건 검사.
		if (i->GetIsEnemyActivated() && !i->GetIsEnemyDead())
		{
			// 충돌 검사
			if (IsObjectColided(position, range, i->GetPosition(), i->GetColideRange()))
			{
				// 충돌했을 경우 반환.
				return i;
			}
		}
	}
	return nullptr;
}
