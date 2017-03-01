#pragma once

// 전방선언
class MyTimer;
class BackGroundScroller;
class Player;
class EnemyManager;
class EffectManager;

/*
	GameManager
	게임의 모든 것을 실제적으로 관리하는 클래스.
	생성할 때 윈도우 핸들을 인자로 받는다.
	
	그 이후 메시지 루프에서 Update를 계속 호출.
	Update 내부에서 계산을 담당하는 CalProc과 렌더를 담당하는 DrawProc을 계속해서 호출한다.

	TODO :: 60fps로 DrawProc 호출.
*/

class GameManager
{
public :

	GameManager(_Inout_ HWND);
	~GameManager();

	void Update();

private :

	// 인자 없이 생성 불가.
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