#include "stdafx.h"
#include "Enemy.h"
#include "EnemyItem.h"
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

// 싱글톤을 지워주는 함수.
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

void EnemyManager::init()
{
	m_pMakeHandler[ENEMY_TYPE::ENEMY_ITEM] = &EnemyManager::MakeEnemyItem;
	return;
}

Enemy * EnemyManager::MakeEnemyItem(const _In_ FLOAT x, const _In_ FLOAT y, 
	const _In_ INT flightType, const _In_opt_ BOOL IsItemLaunched)
{
	Enemy* newEnemy = new EnemyItem(x, y, flightType, IsItemLaunched);
	return newEnemy;
}

// TODO :: 에너미 매니저 소멸자 호출시 벡터 비워주기.
EnemyManager::~EnemyManager()
{
	deleteInstance();
}

void EnemyManager::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	return;
}

void EnemyManager::MakeEnemyWithTime(const _In_ FLOAT createTime, const _In_ INT enemyType,
	const _In_ FLOAT x, const _In_ FLOAT y, const _In_ INT flightType, const _In_opt_ BOOL option)
{
	if ((m_AccTime > createTime) && (m_RecordCreateTime < createTime))
	{
		auto newEnemy = (this->*m_pMakeHandler[enemyType])(x, y, flightType, option);
		m_EnemyVec.push_back(newEnemy);
		m_RecordCreateTime = createTime;
	}

	return;
}

void EnemyManager::Draw(_Inout_ HDC drawDC)
{
	for (auto i : m_EnemyVec)
	{
		if (!i->m_IsEnemyDead)
		{
			i->Draw(drawDC);
		}
		else
		{
			i->DeadProc(drawDC);
		}
	}

	return;
}

void EnemyManager::CalFly(const _In_ FLOAT dt)
{
	for (auto i : m_EnemyVec)
	{
		i->Fly(dt);
	}

	return;
}

void EnemyManager::ClearVec()
{
	std::vector<Enemy*>::iterator iter = m_EnemyVec.begin();
	while (iter != m_EnemyVec.end())
	{
		if ((!(*iter)->CheckEnemyIsOnDisplay()) || ((*iter)->m_IsEnemyDead))
		{
			iter = m_EnemyVec.erase(iter);
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
	DistributeTime(dt);
	MakeProc();
	CalFly(dt);
	ClearVec();
	CheckEnemyDead();
	return;
}

void EnemyManager::DrawProc(_Inout_ HDC drawDC)
{
	Draw(drawDC);
	return;
}

std::vector<Enemy*>& EnemyManager::getEnemyVec()
{
	return m_EnemyVec;
}

void EnemyManager::CheckEnemyDead()
{
	for (auto i : m_EnemyVec)
	{
		if (i->m_Hp <= 0)
		{
			i->m_IsEnemyDead = TRUE;
		}
	}

	return;
}

void EnemyManager::MakeProc()
{
	MakeEnemyWithTime(3.0f , ENEMY_ITEM, 450, 0, FLY_STRAIGHT, FALSE);
	MakeEnemyWithTime(3.25f, ENEMY_ITEM, 350, 0, FLY_STRAIGHT, FALSE);
	MakeEnemyWithTime(3.5f , ENEMY_ITEM, 250, 0, FLY_STRAIGHT, FALSE);
	MakeEnemyWithTime(3.75f, ENEMY_ITEM, 150, 0, FLY_STRAIGHT, TRUE );

	return;
}

void EnemyManager::DistributeTime(const _In_ FLOAT dt)
{
	for (auto i : m_EnemyVec)
	{
		i->AccTime(dt);
	}
	
	return;
}

void EnemyManager::SetPlayerPos(const _In_ FLOAT playerPosX, const _In_ FLOAT playerPosY)
{
	for (auto i : m_EnemyVec)
	{
		i->m_PlayerX = playerPosX;
		i->m_PlayerY = playerPosY;
	}

	return;
}