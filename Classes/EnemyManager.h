#pragma once
using namespace ENEMY;
#include "Option.h"

// 전방 선언
class Enemy;
class Player;

/*
	EnemyManager
	Enemy들을 관리하는 싱글톤 클래스.
	Player와의 정보 교환 또한 담당한다.
*/

class EnemyManager
{
public :
	static EnemyManager* getInstance();
	void deleteInstance();

	EnemyManager();
	~EnemyManager();
	
	void MakeEnemyWithTime(
		const _In_ FLOAT createTime,
		const _In_ INT enemyType,
		const _In_ Vec createPos,
		const _In_ INT flightType,
		const _In_opt_ Vec flightVec,
		const _In_opt_ ::CreateOption flightOption);

	void MakeEnemyOneTime(
		const _In_ INT enemyType,
		const _In_ Vec createPos,
		const _In_ INT flightType,
		const _In_opt_ Vec flightVec,
		const _In_opt_ ::CreateOption flightOption);

	void CalProc(const _In_ FLOAT);
	void MakeProc();
	void DrawProc(_Inout_ HDC);
	void SetPlayerInfo(_Inout_ Player*);
	std::list<Enemy*>& getEnemyList();
	Player& getPlayerInfo();

private :

	// 싱글톤 인스턴스
	static EnemyManager* _instance;
	
	void init();
	void AccTime(const _In_ FLOAT);
	void Draw(_Inout_ HDC);
	void ClearList();
	void DistributeTime(const _In_ FLOAT);
	void DistributePlayerInfo();
	void SetPlayerPos(const _In_ FLOAT, const _In_ FLOAT);

	// 생성 함수 포인터 핸들러.
	Enemy*(EnemyManager::*m_pMakeHandler[ENEMY_TYPE_NUM])(
		const _In_ Vec,
		const _In_ INT,
		const _In_opt_ Vec,
		const _In_opt_ ::CreateOption);

	// 함수 포인터에 들어갈 함수
	Enemy* MakeEnemyItem(
		const _In_ Vec,
		const _In_ INT,
		const _In_opt_ Vec,
		const _In_opt_ ::CreateOption);
	Enemy* MakeItem(
		const _In_ Vec,
		const _In_ INT,
		const _In_opt_ Vec,
		const _In_opt_ ::CreateOption);

	std::list<Enemy*> m_EnemyList;

	FLOAT m_AccTime;
	FLOAT m_RecordCreateTime;
	
	Player* m_pPlayerInfo;
};