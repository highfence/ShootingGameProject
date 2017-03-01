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
	
	void MakeEnemyWithTime(const _In_ FLOAT, const _In_ INT, const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);
	void CalProc(const _In_ FLOAT);
	void MakeProc();
	void DrawProc(_Inout_ HDC);
	void SetPlayerPos(const _In_ FLOAT, const _In_ FLOAT);
	std::vector<Enemy*>& getEnemyVec();

private :

	// 싱글톤 인스턴스
	static EnemyManager* _instance;
	
	void init();
	void AccTime(const _In_ FLOAT);
	void Draw(_Inout_ HDC);
	void CalFly(const _In_ FLOAT);
	void ClearVec();
	void CheckEnemyDead();
	void DistributeTime(const _In_ FLOAT);

	// 생성 함수 포인터 핸들러.
	Enemy*(EnemyManager::*m_pMakeHandler[ENEMY_TYPE_NUM])
		(const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);

	// 함수 포인터에 들어갈 함수
	Enemy* MakeEnemyItem(const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);

	std::vector<Enemy*> m_EnemyVec;

	FLOAT m_AccTime;
	FLOAT m_RecordCreateTime;
	
	FLOAT m_PlayerPosX;
	FLOAT m_PlayerPosY;
};