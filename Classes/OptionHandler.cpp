#include "stdafx.h"
#include "OptionHandler.h"

OptionHandler* OptionHandler::m_pInstance = nullptr;

// OptionHandler 싱글톤 구현.
OptionHandler* OptionHandler::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new OptionHandler();
	}
	return m_pInstance;
}

// 싱글톤 삭제 함수.
void OptionHandler::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

/*
	CreateOption 아이디를 넣으면 그에 해당하는 옵션의 참조자를 반환해주는 함수.
*/
CreateOption & OptionHandler::GetCreateOption(const ENEMY::CREATE_OPTION createOptionId)
{
	auto iter = m_CreateOptionMap.find(createOptionId); 
	return (*iter).second.GetOption();
}

/*
	FireOption 아이디를 넣으면 그에 해당하는 옵션의 참조자를 반환해주는 함수.
*/
FireOption & OptionHandler::GetFireOption(const ENEMY::FIRE_OPTION fireOptionId)
{
	auto iter = m_FireOptionMap.find(fireOptionId);
	return (*iter).second.GetOption();
}

/*
	생성자. init호출.
*/
OptionHandler::OptionHandler()
{
	Init();
}

/*
	소멸자. deleteInstance 호출.
*/
OptionHandler::~OptionHandler()
{
	DeleteInstance();
}

/*
	초기화 함수.
*/
void OptionHandler::Init()
{
	using namespace ENEMY;

	GoAndSlowData enemyItemData = GoAndSlowData(0.5f, 5.f, Vec(0.f, 1.f), 50.f);
	CreateOption enemyItemNormal = CreateOption(1, ENEMY_ITEM, FLY_GO_AND_SLOW, Vec(0, 1), 300.f, 0.f, enemyItemData, FALSE);
	CreateOption enemyItemLaunched = CreateOption(1, ENEMY_ITEM, FLY_GO_AND_SLOW, Vec(0, 1), 300.f, 0.f, enemyItemData, TRUE);
	FireOption enemyFireFront = FireOption(FIRE_TYPE::NORMAL_FIRE, MISSILE_TYPE::STRAIGHT_FIRE, SMALL, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 1.5f, 1.5f, 1, 0.f, nullptr);
	FireOption enemyFireAimed = FireOption(FIRE_TYPE::AIMED_FIRE, MISSILE_TYPE::STRAIGHT_FIRE, SMALL, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 1.5f, 1.5f, 1, 50.f, nullptr);

	INT shotTimes[] = { 6, 5, 6, 0, 0 };
	FLOAT shotAngle[] = { 22.5f, 22.5f, 22.5f, 0, 0 };
	INT MissileNumber[] = { 16, 17, 16, 0, 0 };

	GoAndSlowData enemyHandShotGASData = GoAndSlowData(0.5f, 15.f, Vec(0.f, 1.f), 50.f);
	NwayShotData enemyHandShotNwayData = NwayShotData(3, shotTimes, shotAngle, FALSE, FALSE);
	NwayShotData enemyHandShotNwayToPlayerData = NwayShotData(3, shotTimes, shotAngle, TRUE, FALSE);
	CreateOption enemyHandShotCreate = CreateOption(380, ENEMY_HAND_SHOT, FLY_GO_AND_SLOW, Vec(0, 1), 300.f, 0.f, enemyHandShotGASData, FALSE);
	FireOption enemyHandShotFire = FireOption(FIRE_TYPE::N_WAY_FIRE, MISSILE_TYPE::STRAIGHT_FIRE, LARGE, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 1.0f, 0.3f, 0, 0.f, enemyHandShotNwayData);
	FireOption enemyNwayShotToPlayer = FireOption(FIRE_TYPE::N_WAY_FIRE, MISSILE_TYPE::STRAIGHT_FIRE, MEDIUM, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 1.0f, 0.3f, 0, 0.f, enemyHandShotNwayToPlayerData);
	
	NwayShotData enemyHandShotCircleData = NwayShotData(3, MissileNumber, nullptr, FALSE, TRUE);
	FireOption enemyMultiOption = FireOption(FIRE_TYPE::MULTI_FIRE, MISSILE_TYPE::STRAIGHT_FIRE, MEDIUM, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 1.0f, 0.3f, 0, 0.f, enemyHandShotCircleData);
	CircleShotData enemyCircleShotData = CircleShotData(Vec(0.f, 0.f), 15, 300.f, 0.f, 50.f, 0.f, 300.f, TRUE, 10.f, 300.f);
	FireOption enemyRotateOption = FireOption(FIRE_TYPE::CIRCLE_FIRE, MISSILE_TYPE::CIRCLE_TYPE, MEDIUM, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 0.5f, 4.f, 0, 0.f, enemyCircleShotData);

	// 생성 옵션 등록.
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(ENEMY_ITEM_TRUE, enemyItemLaunched));
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(ENEMY_ITEM_FALSE, enemyItemNormal));
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(ENEMY_HAND_SHOT_CREATE, enemyHandShotCreate));

	// 발사 옵션 등록.
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(FIRE_FRONT, enemyFireFront));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(FIRE_AIMED, enemyFireAimed));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(N_WAY_FIRE_OPTION, enemyHandShotFire));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(N_WAY_FIRE_TO_PLAYER, enemyNwayShotToPlayer));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(MULTI_FIRE_OPTION, enemyMultiOption));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(ROTATE_FIRE_OPTION, enemyRotateOption));

	return;
}
