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
CreateOption* OptionHandler::GetCreateOption(const ENEMY::CREATE_OPTION createOptionId)
{
	auto iter = m_CreateOptionMap.find(createOptionId); 
	return &(*iter).second.GetOption();
}

/*
	FireOption 아이디를 넣으면 그에 해당하는 옵션의 참조자를 반환해주는 함수.
*/
FireOption* OptionHandler::GetFireOption(const ENEMY::FIRE_OPTION fireOptionId)
{
	auto iter = m_FireOptionMap.find(fireOptionId);
	return &(*iter).second.GetOption();
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

	/* 빈 데이터. */
	GoAndSlowData emptyData;

	/* 쏘지 않는 FireOption */
	FireOption enemyNoFire = FireOption(
		FIRE_TYPE::FIRE_TYPE_NUM,
		MISSILE_TYPE::NONE,
		MISSILE_SIZE::SMALL,
		0.f, 0.f, 0.f,
		Vec(0.f, 0.f),
		0.f, 0.f, 0, 0.f, 0);

	/* 직선, 조준탄 FireOption */
	FireOption enemyFireFront = FireOption(
		FIRE_TYPE::NORMAL_FIRE,
		MISSILE_TYPE::STRAIGHT_FIRE,
		MISSILE_SIZE::SMALL,
		500.f, 0.f, 0.f,
		Vec(0.f, 1.f),
		1.5f, 1.5f, 1, 0.f, nullptr);

	FireOption enemyFireAimed = FireOption(
		FIRE_TYPE::AIMED_FIRE,
		MISSILE_TYPE::STRAIGHT_FIRE,
		MISSILE_SIZE::SMALL,
		500.f, 0.f, 0.f,
		Vec(0.f, 1.f),
		1.5f, 1.5f, 1, 50.f, nullptr);

	FireOption enemyMineAimed = FireOption(
		FIRE_TYPE::AIMED_FIRE,
		MISSILE_TYPE::STRAIGHT_FIRE,
		MISSILE_SIZE::SMALL,
		300.f, 0.f, 0.f,
		Vec(0.f, 1.f),
		0.25f, 3.0f, 1, 150.f, nullptr);

	/* Data 생성을 위한 정보. */
	INT shotTimes[] = { 6, 5, 6, 0, 0 };
	FLOAT shotAngle[] = { 22.5f, 22.5f, 22.5f, 0, 0 };
	INT MissileNumber[] = { 16, 17, 16, 0, 0 };

	/* Nway탄 발사 FireOption */
	NwayShotData enemyHandShotNwayData = NwayShotData(3, shotTimes, shotAngle, FALSE, FALSE);
	NwayShotData enemyHandShotNwayToPlayerData = NwayShotData(3, shotTimes, shotAngle, TRUE, FALSE);
	FireOption enemyHandShotFire = FireOption(FIRE_TYPE::N_WAY_FIRE, MISSILE_TYPE::STRAIGHT_FIRE, MISSILE_SIZE::LARGE, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 1.0f, 0.3f, 0, 0.f, enemyHandShotNwayData);
	FireOption enemyNwayShotToPlayer = FireOption(FIRE_TYPE::N_WAY_FIRE, MISSILE_TYPE::STRAIGHT_FIRE, MISSILE_SIZE::MEDIUM, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 1.0f, 0.3f, 0, 0.f, enemyHandShotNwayToPlayerData);
	
	/* Multi 발사 FireOption */
	NwayShotData enemyHandShotCircleData = NwayShotData(3, MissileNumber, nullptr, FALSE, TRUE);
	FireOption enemyMultiOption = FireOption(FIRE_TYPE::MULTI_FIRE, MISSILE_TYPE::STRAIGHT_FIRE, MISSILE_SIZE::MEDIUM, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 1.0f, 0.3f, 0, 0.f, enemyHandShotCircleData);

	/* Circle 발사 FireOption */
	CircleShotData enemyCircleShotData = CircleShotData(Vec(0.f, 0.f), 15, 300.f, 0.f, 50.f, 0.f, 300.f, TRUE, 5.f, 300.f);
	FireOption enemyRotateOption = FireOption(FIRE_TYPE::CIRCLE_FIRE, MISSILE_TYPE::CIRCLE_TYPE, MISSILE_SIZE::MEDIUM, 500.f, 0.f, 0.f, Vec(0.f, 1.f), 0.5f, 4.f, 0, 0.f, enemyCircleShotData);

	/* EnemyItem 관련 CreateOption */
	GoAndSlowData enemyItemData = GoAndSlowData(0.5f, 5.f, Vec(0.f, 1.f), 50.f);
	CreateOption enemyItemNormal = CreateOption(1, ENEMY_TYPE::ENEMY_ITEM, FLIGHT_TYPE::FLY_GO_AND_SLOW, Vec(0, 1), 300.f, 0.f, enemyItemData, FALSE);
	CreateOption enemyItemLaunched = CreateOption(1, ENEMY_TYPE::ENEMY_ITEM, FLIGHT_TYPE::FLY_GO_AND_SLOW, Vec(0, 1), 300.f, 0.f, enemyItemData, TRUE);

	/* Item 관련 CreateOption */
	CreateOption itemOption = CreateOption(100000, ENEMY_TYPE::ITEM, FLIGHT_TYPE::FLY_ITEM, Vec(0, 0), 150.f, 0, NULL, FALSE);

	/* EnemyMine 관련 CreateOption*/
	CreateOption enemyMineDiagonal = CreateOption(1, ENEMY_TYPE::ENEMY_MINE, FLIGHT_TYPE::FLY_ACCELERATE, Vec(-0.5f, 0.5f), 250.f, 150.f, emptyData, FALSE);
	CreateOption enemyMineStraight = CreateOption(1, ENEMY_TYPE::ENEMY_MINE, FLIGHT_TYPE::FLY_ACCELERATE, Vec(0.f, 1.f), 50.f, 20.f, emptyData, FALSE);
	CreateOption enemyMineStraightWithItem = CreateOption(1, ENEMY_TYPE::ENEMY_MINE, FLIGHT_TYPE::FLY_ACCELERATE, Vec(0.f, 1.f), 50.f, 20.f, emptyData, TRUE);

	/* EnemyHandShot 관련 CreateOption */
	GoAndSlowData enemyHandShotGASData = GoAndSlowData(0.5f, 15.f, Vec(0.f, 1.f), 50.f);
	CreateOption enemyHandShotCreate = CreateOption(380, ENEMY_TYPE::ENEMY_HAND_SHOT, FLIGHT_TYPE::FLY_GO_AND_SLOW, Vec(0, 1), 300.f, 0.f, enemyHandShotGASData, FALSE);

	/* EnemyBoss 관련 Option */
	// 임시 데이터
	GoAndSlowData enemyBossGASData = GoAndSlowData(0.5f, 99.f, Vec(0.f, 0.f), 0.f);
	CreateOption enemyBossCreate = CreateOption(2000, ENEMY_TYPE::ENEMY_BOSS, FLIGHT_TYPE::FLY_GO_AND_SLOW, Vec(0, 1), 300.f, 0.f, enemyBossGASData, FALSE);


	// 생성 옵션 등록.
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(CREATE_OPTION::ENEMY_ITEM_TRUE, enemyItemLaunched));
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(CREATE_OPTION::ENEMY_ITEM_FALSE, enemyItemNormal));
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(CREATE_OPTION::ENEMY_HAND_SHOT_CREATE, enemyHandShotCreate));
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(CREATE_OPTION::ENEMY_MINE_DIAGONAL, enemyMineDiagonal));
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(CREATE_OPTION::ENEMY_MINE_STRAIGHT, enemyMineStraight));
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(CREATE_OPTION::ENEMY_MINE_STRAIGHT_WITH_ITEM, enemyMineStraightWithItem));
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(CREATE_OPTION::ITEM_CREATE, itemOption));
	m_CreateOptionMap.insert(std::unordered_map<ENEMY::CREATE_OPTION, CreateOption>::value_type(CREATE_OPTION::ENEMY_BOSS_CREATE, enemyBossCreate));

	// 발사 옵션 등록.
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(FIRE_OPTION::FIRE_FRONT, enemyFireFront));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(FIRE_OPTION::FIRE_AIMED, enemyFireAimed));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(FIRE_OPTION::MINE_AIMED, enemyMineAimed));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(FIRE_OPTION::N_WAY_FIRE_OPTION, enemyHandShotFire));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(FIRE_OPTION::N_WAY_FIRE_TO_PLAYER, enemyNwayShotToPlayer));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(FIRE_OPTION::MULTI_FIRE_OPTION, enemyMultiOption));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(FIRE_OPTION::ROTATE_FIRE_OPTION, enemyRotateOption));
	m_FireOptionMap.insert(std::unordered_map<ENEMY::FIRE_OPTION, FireOption>::value_type(FIRE_OPTION::NO_FIRE, enemyNoFire));


	return;
}
