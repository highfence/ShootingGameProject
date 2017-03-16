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
	static EnemyManager* GetInstance();
	void DeleteInstance();

	EnemyManager();
	~EnemyManager();
	
	// TODO :: ����ü�� �����ڷ� ��������.
	void ActivateEnemy(
		const _In_ FLOAT activateTime, 
		const _In_ Vec createPos,
		_In_ CreateOption& createOption,
		_In_ FireOption& fireOption);

	void ActivateEnemyOnce(
		const _In_ Vec createPos,
		_In_ CreateOption& createOption,
		_In_ FireOption& fireOption);

	void CalcProc(const _In_ FLOAT);
	void MakeProc();
	void DrawProc(_Inout_ HDC);
	void SetPlayerInfo(_Inout_ Player&);
	Player& getPlayerInfo();
	Enemy* FindEnemyColideWith(const _In_ Vec, const _In_ Vec);
	Enemy* FindDeactivatedEnemy(const _In_ ENEMY::ENEMY_TYPE);

private :

	// �̱��� �ν��Ͻ�
	static EnemyManager* m_pInstance;
	
	void Init();
	void AccTime(const _In_ FLOAT);
	void Draw(_Inout_ HDC);
	void DistributeData(const _In_ FLOAT);
	void SetEnemyMemoryPool();
	void RegisterFunctionPointer();

	template <typename T>
	void AllocEnemyMemory(const _In_ INT);

	// ���� �Լ� ������ �ڵ鷯.
	BOOL(EnemyManager::*m_pActivateHandler[ENEMY_TYPE_NUM])(
		const _In_ Vec,
		_In_ CreateOption&,
		_In_ FireOption&);

	// �Լ� �����Ϳ� �� �Լ�
	BOOL ActivateEnemyItem(
		const _In_ Vec,
		_In_ CreateOption&,
		_In_ FireOption&);

	BOOL ActivateItem(
		const _In_ Vec,
		_In_ CreateOption&,
		_In_ FireOption&);

	BOOL ActivateZaco(
		const _In_ Vec,
		_In_ CreateOption&,
		_In_ FireOption&);

	BOOL ActivateHandShot(
		const _In_ Vec,
		_In_ CreateOption&,
		_In_ FireOption&);

	FLOAT m_AccTime;
	FLOAT m_RecordCreateTime;
	
	Player* m_pPlayerInfo;

	// Enemy �޸� Ǯ.
	std::vector<Enemy*> m_EnemyMemoryVector;
};