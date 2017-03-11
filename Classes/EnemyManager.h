#pragma once
using namespace ENEMY;

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
	//void MakeProc();
	void DrawProc(_Inout_ HDC);
	void SetPlayerInfo(_Inout_ Player*);
	Player& getPlayerInfo();

private :

	// �̱��� �ν��Ͻ�
	static EnemyManager* _instance;
	
	void init();
	void AccTime(const _In_ FLOAT);
	void Draw(_Inout_ HDC);
	void DistributeTime(const _In_ FLOAT);
	void DistributePlayerInfo();
	void SetPlayerPos(const _In_ Vec);
	void SetEnemyMemoryPool();

	template <typename T>
	void AllocEnemyMemory(const _In_ T, const _In_ INT);

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
	Enemy* MakeZaco(
		const _In_ Vec,
		const _In_ INT,
		const _In_opt_ Vec,
		const _In_opt_ ::CreateOption);
	Enemy* MakeHandShot(
		const _In_ Vec,
		const _In_ INT,
		const _In_opt_ Vec,
		const _In_opt_ ::CreateOption);


	FLOAT m_AccTime;
	FLOAT m_RecordCreateTime;
	
	Player* m_pPlayerInfo;

	// Enemy �޸� Ǯ.
	std::vector<Enemy*> m_EnemyMemoryVector;
};