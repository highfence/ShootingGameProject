#pragma once
using namespace ENEMY;
#include "Option.h"

// ���� ����
class Enemy;
class Player;

/*
	EnemyManager
	Enemy���� �����ϴ� �̱��� Ŭ����.
	Player���� ���� ��ȯ ���� ����Ѵ�.
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

	// �̱��� �ν��Ͻ�
	static EnemyManager* _instance;
	
	void init();
	void AccTime(const _In_ FLOAT);
	void Draw(_Inout_ HDC);
	void ClearList();
	void DistributeTime(const _In_ FLOAT);
	void DistributePlayerInfo();
	void SetPlayerPos(const _In_ FLOAT, const _In_ FLOAT);

	// ���� �Լ� ������ �ڵ鷯.
	Enemy*(EnemyManager::*m_pMakeHandler[ENEMY_TYPE_NUM])(
		const _In_ Vec,
		const _In_ INT,
		const _In_opt_ Vec,
		const _In_opt_ ::CreateOption);

	// �Լ� �����Ϳ� �� �Լ�
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