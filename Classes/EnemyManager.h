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
	
	// TODO :: ����ü�� �����ڷ� ��������.
	void ActivateEnemy(
		const _In_ FLOAT activateTime, 
		_In_ CreateOption& flightOption,
		_In_ FireOption& fireOption);

	void CalcProc(const _In_ FLOAT);
	//void MakeProc();
	void DrawProc(_Inout_ HDC);
	void SetPlayerInfo(_Inout_ Player*);
	Player& getPlayerInfo();
	Enemy* FindEnemyColideWith(const _In_ Vec, const _In_ Vec);
	Enemy* FindDeactivatedEnemy(const _In_ ENEMY::ENEMY_TYPE);

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
	void RegisterFunctionPointer();

	template <typename T>
	void AllocEnemyMemory(const _In_ INT);

	// ���� �Լ� ������ �ڵ鷯.
	BOOL(EnemyManager::*m_pActivateHandler[ENEMY_TYPE_NUM])(
		_In_ CreateOption&,
		_In_ FireOption&);

	// �Լ� �����Ϳ� �� �Լ�
	BOOL ActivateEnemyItem(
		_In_ CreateOption&,
		_In_ FireOption&);

	BOOL ActivateItem(
		_In_ CreateOption&,
		_In_ FireOption&);

	BOOL ActivateZaco(
		_In_ CreateOption&,
		_In_ FireOption&);

	BOOL ActivateHandShot(
		_In_ CreateOption&,
		_In_ FireOption&);

	FLOAT m_AccTime;
	FLOAT m_RecordCreateTime;
	
	Player* m_pPlayerInfo;

	// Enemy �޸� Ǯ.
	std::vector<Enemy*> m_EnemyMemoryVector;
};