#pragma once

// ���漱��
class MyTimer;
class BackGroundScroller;
class Player;
class EnemyManager;
class EffectManager;

/*
	GameManager
	������ ��� ���� ���������� �����ϴ� Ŭ����.
	������ �� ������ �ڵ��� ���ڷ� �޴´�.
	
	�� ���� �޽��� �������� Update�� ��� ȣ��.
	Update ���ο��� ����� ����ϴ� CalProc�� ������ ����ϴ� DrawProc�� ����ؼ� ȣ���Ѵ�.

	TODO :: 60fps�� DrawProc ȣ��.
*/

class GameManager
{
public :

	GameManager(_Inout_ HWND);
	~GameManager();

	void Update();

private :

	// ���� ���� ���� �Ұ�.
	GameManager();

	// Private Function
	void init();
	void CalProc(const _In_ FLOAT);
	void DrawProc(const _In_ FLOAT);
	void GetKeyState();
	void ExchangeInfo();

	HWND m_hWnd;
	HDC m_hdc;
	MyTimer* m_pTimer;
	BackGroundScroller* m_pScroller;
	Player* m_pPlayer;
	EnemyManager* m_pEnemyManager;
	EffectManager* m_pEffectManager;

	BYTE m_ByKey[keyboardNumber];
	BYTE m_OldKey[keyboardNumber];
};