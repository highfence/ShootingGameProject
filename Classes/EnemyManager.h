#pragma once
using namespace ENEMY;

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
	static EnemyManager* GetInstance();
	void DeleteInstance();

	EnemyManager();
	~EnemyManager();

	//template <typename T>
	//void Activate(
	//	const _In_ FLOAT activateTime,
	//	const _In_ Vec createPos,
	//	const _In_ ENEMY::CREATE_OPTION createOption,
	//	const _In_ ENEMY::FIRE_OPTION fireOption);
	
	void ActivateEnemy(
		const _In_ FLOAT activateTime, 
		const _In_ Vec createPos,
		const _In_ ENEMY::CREATE_OPTION createOption,
		const _In_ ENEMY::FIRE_OPTION fireOption);

	void ActivateEnemyOnce(
		const _In_ Vec createPos,
		const _In_ ENEMY::CREATE_OPTION createOption,
		const _In_ ENEMY::FIRE_OPTION fireOption);

	void CalcProc(const _In_ FLOAT);
	void MakeProc();
	void DrawProc(_Inout_ HDC);
	void SetPlayerInfo(_Inout_ Player&);
	Player& getPlayerInfo();
	Enemy* FindEnemyColideWith(const _In_ Vec, const _In_ Vec);
	Enemy* FindDeactivatedEnemy(const _In_ ENEMY::ENEMY_TYPE);

private :

	// 싱글톤 인스턴스
	static EnemyManager* m_pInstance;
	
	void Init();
	void AccTime(const _In_ FLOAT);
	void Draw(_Inout_ HDC);
	void DistributeData(const _In_ FLOAT);
	void SetEnemyMemoryPool();
	void RegisterFunctionPointer();
	void GetOptionPointer();

	template <typename T>
	void AllocEnemyMemory(const _In_ INT);

	// 생성 함수 포인터 핸들러.
	BOOL(EnemyManager::*m_pActivateHandler[ENEMY_TYPE_NUM])(
		const _In_ Vec,
		const _In_ ENEMY::CREATE_OPTION,
		const _In_ ENEMY::FIRE_OPTION);

	// 함수 포인터에 들어갈 함수
	BOOL ActivateEnemyItem(
		const _In_ Vec,
		const _In_ ENEMY::CREATE_OPTION,
		const _In_ ENEMY::FIRE_OPTION);

	BOOL ActivateItem(
		const _In_ Vec,
		const _In_ ENEMY::CREATE_OPTION,
		const _In_ ENEMY::FIRE_OPTION);

	BOOL ActivateZaco(
		const _In_ Vec,
		const _In_ ENEMY::CREATE_OPTION,
		const _In_ ENEMY::FIRE_OPTION);

	BOOL ActivateHandShot(
		const _In_ Vec,
		const _In_ ENEMY::CREATE_OPTION,
		const _In_ ENEMY::FIRE_OPTION);

	BOOL ActivateEnemyMine(
		const _In_ Vec,
		const _In_ ENEMY::CREATE_OPTION,
		const _In_ ENEMY::FIRE_OPTION);

	BOOL ActivateEnemyBoss(
		const _In_ Vec,
		const _In_ ENEMY::CREATE_OPTION,
		const _In_ ENEMY::FIRE_OPTION);

	FLOAT m_AccTime;
	FLOAT m_RecordCreateTime;
	
	Player* m_pPlayerInfo;

	// Enemy 메모리 풀.
	std::vector<Enemy*> m_EnemyMemoryVector;

	// Enemy Option 포인터 배열.
	CreateOption* m_pCreateOptionArray[ENEMY::CREATE_OPTION::CREATE_OPTION_NUM];
	FireOption* m_pFireOptionArray[ENEMY::FIRE_OPTION::FIRE_OPTION_NUM];
};