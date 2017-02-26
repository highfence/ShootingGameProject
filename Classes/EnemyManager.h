#pragma once
using namespace ENEMY;

// 전방 선언
class Enemy;

class EnemyManager
{
public :
	EnemyManager();
	~EnemyManager();
	
	void AccTime(const _In_ FLOAT);
	void MakeEnemy(const _In_ INT, const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);
	void Draw(_Inout_ HDC);
	void CalFly(const _In_ FLOAT);
	void ClearVec();

private :

	Enemy*(EnemyManager::*m_pMakeHandler[ENEMY_TYPE_NUM])
		(const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);

	void init();
	Enemy* MakeEnemyItem(const _In_ FLOAT, const _In_ FLOAT, const _In_ INT, const _In_opt_ BOOL);

	FLOAT m_AccTime;
	std::vector<Enemy*> m_EnemyVec;
};