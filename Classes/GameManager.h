#pragma once

// ���漱��
class MyTimer;
class BackGroundScroller;
class Player;
class EnemyManager;
class EffectManager;
class UIManager;

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

	GameManager(_Inout_ HWND, _Inout_ HINSTANCE);
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

	HWND m_hWnd;
	HDC m_hdc;
	HINSTANCE m_hInstance;
	FLOAT m_AccTime;
	MyTimer* m_pTimer;
	BackGroundScroller* m_pScroller;
	Player* m_pPlayer;
	EnemyManager* m_pEnemyManager;
	EffectManager* m_pEffectManager;
	UIManager* m_pUIManager;

	BYTE m_ByKey[keyboardNumber];
	BYTE m_OldKey[keyboardNumber];
};