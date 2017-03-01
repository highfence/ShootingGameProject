#pragma once
using namespace ENEMY;

// ���� ����
class Enemy;

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
	
	void MakeEnemyWithTime(const _In_ FLOAT, const _In_ INT, const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);
	void CalProc(const _In_ FLOAT);
	void MakeProc();
	void DrawProc(_Inout_ HDC);
	void SetPlayerPos(const _In_ FLOAT, const _In_ FLOAT);
	std::vector<Enemy*>& getEnemyVec();

private :

	// �̱��� �ν��Ͻ�
	static EnemyManager* _instance;
	
	void init();
	void AccTime(const _In_ FLOAT);
	void Draw(_Inout_ HDC);
	void CalFly(const _In_ FLOAT);
	void ClearVec();
	void CheckEnemyDead();
	void DistributeTime(const _In_ FLOAT);

	// ���� �Լ� ������ �ڵ鷯.
	Enemy*(EnemyManager::*m_pMakeHandler[ENEMY_TYPE_NUM])
		(const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);

	// �Լ� �����Ϳ� �� �Լ�
	Enemy* MakeEnemyItem(const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);

	std::vector<Enemy*> m_EnemyVec;

	FLOAT m_AccTime;
	FLOAT m_RecordCreateTime;
	
	FLOAT m_PlayerPosX;
	FLOAT m_PlayerPosY;
};