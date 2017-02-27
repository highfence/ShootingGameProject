#include "stdafx.h"
#include "Enemy.h"
#include "EnemyItem.h"
#include "EnemyManager.h"

EnemyManager* EnemyManager::_instance = nullptr;

// EnemyManager ½Ì±ÛÅæ ±¸Çö.
EnemyManager* EnemyManager::getInstance()
{
	if (!_instance)
	{
		_instance = new EnemyManager();
	}
	return _instance;
}

// ½Ì±ÛÅæÀ» Áö¿öÁÖ´Â ÇÔ¼ö.
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

EnemyManager::~EnemyManager()
{

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
		if (!(*iter)->CheckEnemyIsOnDisplay())
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
	MakeProc();
	CalFly(dt);
	ClearVec();
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

void EnemyManager::MakeProc()
{
	MakeEnemyWithTime(3.0f , ENEMY_ITEM, 450, 0, FLY_STRAIGHT, FALSE);
	MakeEnemyWithTime(3.25f, ENEMY_ITEM, 350, 0, FLY_STRAIGHT, FALSE);
	MakeEnemyWithTime(3.5f , ENEMY_ITEM, 250, 0, FLY_STRAIGHT, FALSE);
	MakeEnemyWithTime(3.75f, ENEMY_ITEM, 150, 0, FLY_STRAIGHT, TRUE );

	return;
}