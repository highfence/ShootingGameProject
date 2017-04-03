#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "EnemyItem.h"
#include "EnemyZaco.h"
#include "EnemyHandShot.h"
#include "EnemyMine.h"
#include "Boss.h"
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
	GetOptionPointer();
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
	m_pActivateHandler[ENEMY_TYPE::ENEMY_MINE] = &EnemyManager::ActivateEnemyMine;
	m_pActivateHandler[ENEMY_TYPE::ENEMY_BOSS] = &EnemyManager::ActivateEnemyBoss;
	return;
}

/*
	초기화 작업시에 Option Handler로 부터 옵션들의 포인터를 받아두는 함수.
*/
void EnemyManager::GetOptionPointer()
{
	auto optHandler = OptionHandler::GetInstance();
	for (int i = 0; (CREATE_OPTION)i < CREATE_OPTION::CREATE_OPTION_NUM; ++i)
	{
		auto opt = optHandler->GetCreateOption((CREATE_OPTION)i);
		m_pCreateOptionArray[i] = opt;
	}
	
	for (INT i = 0; (FIRE_OPTION)i < FIRE_OPTION::FIRE_OPTION_NUM; ++i)
	{
		auto opt = optHandler->GetFireOption((FIRE_OPTION)i);
		m_pFireOptionArray[i] = opt;
	}

	return;
}

/*
	EnemyItem을 만들어주는 함수.
*/
BOOL EnemyManager::ActivateEnemyItem(
	const _In_ Vec createPos,
	const _In_ ENEMY::CREATE_OPTION createOptionNumber,
	const _In_ ENEMY::FIRE_OPTION fireOptionNumber)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_ITEM);
	if (newEnemy != nullptr)
	{
		newEnemy->Activate(
			createPos,
			*m_pCreateOptionArray[createOptionNumber],
			*m_pFireOptionArray[fireOptionNumber]);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
	Item을 만들어주는 함수.
*/
BOOL EnemyManager::ActivateItem(
	const _In_ Vec createPos,
	const _In_ ENEMY::CREATE_OPTION createOptionNumber,
	const _In_ ENEMY::FIRE_OPTION fireOptionNumber)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ITEM);
	if (newEnemy != nullptr)
	{
		newEnemy->Activate(
			createPos,
			*m_pCreateOptionArray[createOptionNumber],
			*m_pFireOptionArray[fireOptionNumber]);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
	EnemyZaco를 만들어주는 함수.
*/
BOOL EnemyManager::ActivateZaco(
	const _In_ Vec createPos,
	const _In_ ENEMY::CREATE_OPTION createOptionNumber,
	const _In_ ENEMY::FIRE_OPTION fireOptionNumber)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_ZACO);
	if (newEnemy != nullptr)
	{
		newEnemy->Activate(
			createPos,
			*m_pCreateOptionArray[createOptionNumber],
			*m_pFireOptionArray[fireOptionNumber]);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
	EnemyHandShot을 만들어 주는 함수.
*/
BOOL EnemyManager::ActivateHandShot(
	const _In_ Vec createPos,
	const _In_ ENEMY::CREATE_OPTION createOptionNumber,
	const _In_ ENEMY::FIRE_OPTION fireOptionNumber)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_HAND_SHOT);
	if (newEnemy != nullptr)
	{
		newEnemy->Activate(
			createPos,
			*m_pCreateOptionArray[createOptionNumber],
			*m_pFireOptionArray[fireOptionNumber]);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
	EnemyMine을 만들어 주는 함수.
*/
BOOL EnemyManager::ActivateEnemyMine(
	const _In_ Vec createPos,
	const _In_ ENEMY::CREATE_OPTION createOptionNumber,
	const _In_ ENEMY::FIRE_OPTION fireOptionNumber)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_MINE);
	if (newEnemy != nullptr)
	{
		newEnemy->Activate(
			createPos,
			*m_pCreateOptionArray[createOptionNumber],
			*m_pFireOptionArray[fireOptionNumber]);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
	EnemyBoss를 만들어 주는 함수.
*/
BOOL EnemyManager::ActivateEnemyBoss(
	const _In_ Vec createPos,
	const _In_ ENEMY::CREATE_OPTION createOptionNumber,
	const _In_ ENEMY::FIRE_OPTION fireOptionNumber)
{
	auto newEnemy = FindDeactivatedEnemy(ENEMY::ENEMY_TYPE::ENEMY_BOSS);
	if (newEnemy != nullptr)
	{
		newEnemy->Activate(
			createPos,
			*m_pCreateOptionArray[createOptionNumber],
			*m_pFireOptionArray[fireOptionNumber]);
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
	const _In_ ENEMY::CREATE_OPTION createOptionNumber,
	const _In_ ENEMY::FIRE_OPTION fireOptionNumber)
{
	if ((m_AccTime > activateTime) && (m_RecordCreateTime < activateTime))
	{
		auto opt = m_pCreateOptionArray[createOptionNumber];
		(this->*m_pActivateHandler[opt->GetEnemyType()])
			(createPos, createOptionNumber, fireOptionNumber);
		m_RecordCreateTime = activateTime;
	}

	return;
}

void EnemyManager::ActivateEnemyOnce(
	const _In_ Vec createPos,
	const _In_ ENEMY::CREATE_OPTION createOptionNumber,
	const _In_ ENEMY::FIRE_OPTION fireOptionNumber)
{
	auto opt = m_pCreateOptionArray[createOptionNumber];
	(this->*m_pActivateHandler[opt->GetEnemyType()])
		(createPos, createOptionNumber, fireOptionNumber);

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
	이전의 DistributeTime과 DistributePlayerInfo를 대체.
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
	FLOAT line1 = 4.f;
	ActivateEnemy(line1		   , Vec(350.f, 0.f), CREATE_OPTION::ENEMY_ITEM_FALSE, FIRE_OPTION::FIRE_FRONT);
	ActivateEnemy(line1 + 0.25f, Vec(275.f, 0.f), CREATE_OPTION::ENEMY_ITEM_FALSE, FIRE_OPTION::FIRE_FRONT);
	ActivateEnemy(line1 + 0.50f, Vec(200.f, 0.f), CREATE_OPTION::ENEMY_ITEM_FALSE, FIRE_OPTION::FIRE_FRONT);
	ActivateEnemy(line1 + 0.75f, Vec(125.f, 0.f), CREATE_OPTION::ENEMY_ITEM_TRUE, FIRE_OPTION::FIRE_FRONT);

	FLOAT line2 = 6.f;
	ActivateEnemy(line2		   , Vec(winWidth, 125.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line2 + 0.25f, Vec(winWidth, 125.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line2 + 0.50f, Vec(winWidth, 125.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line2 + 0.75f, Vec(winWidth, 125.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line2 + 1.00f, Vec(winWidth, 125.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line2 + 1.25f, Vec(winWidth, 125.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line2 + 1.50f, Vec(winWidth, 125.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line2 + 1.75f, Vec(winWidth, 125.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);

	FLOAT line3 = line2 + 0.01;
	ActivateEnemy(line3 + 0.50f, Vec(winWidth, 55.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line3 + 0.75f, Vec(winWidth, 55.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line3 + 1.00f, Vec(winWidth, 55.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line3 + 1.25f, Vec(winWidth, 55.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line3 + 1.50f, Vec(winWidth, 55.f), CREATE_OPTION::ENEMY_MINE_DIAGONAL, FIRE_OPTION::MINE_AIMED);

	FLOAT line4 = line3 + 2.f;
	ActivateEnemy(line4, Vec(350.f, 0.f), CREATE_OPTION::ENEMY_HAND_SHOT_CREATE, FIRE_OPTION::N_WAY_FIRE_OPTION);

	FLOAT line5 = line4 + 2.5;
	ActivateEnemy(line5		   , Vec(550.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5	+ 0.01f, Vec(500.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5 + 0.25f, Vec(550.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5 + 0.26f, Vec(500.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5 + 0.50f, Vec(550.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5 + 0.51f, Vec(500.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5 + 0.75f, Vec(550.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5 + 0.76f, Vec(500.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5 + 1.00f, Vec(550.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5 + 1.01f, Vec(500.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5 + 1.25f, Vec(550.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT, FIRE_OPTION::MINE_AIMED);
	ActivateEnemy(line5 + 1.26f, Vec(500.f, 0.f), CREATE_OPTION::ENEMY_MINE_STRAIGHT_WITH_ITEM, FIRE_OPTION::MINE_AIMED);

	FLOAT line6 = line5 + 4.5;
	ActivateEnemy(line6 + 3.f, Vec(250.f, 0.f), CREATE_OPTION::ENEMY_HAND_SHOT_CREATE, FIRE_OPTION::ROTATE_FIRE_OPTION);

	FLOAT line7 = line6 + 6.0f;
	ActivateEnemy(3.0f, Vec(450.f, 300.f), CREATE_OPTION::ENEMY_BOSS_CREATE, FIRE_OPTION::N_WAY_FIRE_OPTION);

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
	const INT enemyMineAllocTime = 30;
	const INT enemyBossAllocTime = 1;
	const INT wholeAllocTime = 
		enemyItemAllocTime +
		ItemAllocTime +
		enemyZacoAllocTime +
		enemyHandShotAllocTime +
		enemyMineAllocTime +
		enemyBossAllocTime;

	m_EnemyMemoryVector.reserve(wholeAllocTime);
	AllocEnemyMemory<EnemyHandShot>(enemyHandShotAllocTime);
	AllocEnemyMemory<EnemyItem>(enemyItemAllocTime);
	AllocEnemyMemory<Item>(ItemAllocTime);
	AllocEnemyMemory<EnemyZaco>(enemyZacoAllocTime);
	AllocEnemyMemory<EnemyMine>(enemyMineAllocTime);
	AllocEnemyMemory<EnemyBoss>(enemyBossAllocTime);

	return;
}

/*
	EnemyManager 생성시 메모리풀을 잡아 놓는 함수.
*/
template <typename T>
void EnemyManager::AllocEnemyMemory(const _In_ INT allocTime)
{
	// 할당 받은 회수만큼 for문 루프
	for (int i = 0; i < allocTime; ++i)
	{
		// 생성은 각각 Enemy타입의 형태이지만, vector에 넣기 위해 Enemy*형태로 캐스팅.
		T* newEnemy = new T();
		m_EnemyMemoryVector.emplace_back((Enemy*)newEnemy);
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
	// 해당하는 Enemy가 없다면 nullptr반환.
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
		// ENEMY_TYPE이 ITEM인 경우에는 검사를 실행하지 않음.
		if (i->GetEnemyType() == ENEMY_TYPE::ITEM)
		{
			continue;
		}
		// 활성화 상태 & 살아있는 상태인 Enemy만 조건 검ㅅ.
		if (i->GetIsEnemyActivated() && !i->GetIsEnemyDead())
		{
			// 충돌 검사.
			if (IsObjectColided(position, range, i->GetPosition(), i->GetColideRange()))
			{
				// 충돌했을 경우 반환.
				return i;
			}
		}
	}
	return nullptr;
}
