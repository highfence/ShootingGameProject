#pragma once
using namespace ENEMY;

// 전방 선언
class Enemy;

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
	
	void AccTime(const _In_ FLOAT);
	void MakeEnemy(const _In_ INT, const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);
	void Draw(_Inout_ HDC);
	void CalFly(const _In_ FLOAT);
	void ClearVec();

	void CalProc(const _In_ FLOAT);
	void DrawProc(_Inout_ HDC);

private :

	static EnemyManager* _instance;

	Enemy*(EnemyManager::*m_pMakeHandler[ENEMY_TYPE_NUM])
		(const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);

	void init();
	Enemy* MakeEnemyItem(const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);

	FLOAT m_AccTime;
	std::vector<Enemy*> m_EnemyVec;
	
	FLOAT m_PlayerPosX;
	FLOAT m_PlayerPosY;
};