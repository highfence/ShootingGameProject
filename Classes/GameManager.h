#pragma once

// 전방선언
class MyTimer;
class BackGroundScroller;

class GameManager
{
public :

	GameManager(_In_ HWND);
	~GameManager();

	void Update();

private :

	// 인자 없이 생성 불가.
	GameManager();

	// Private Function
	void init();
	void CalProc(const _In_ FLOAT);
	void DrawProc(const _In_ FLOAT);

	HWND m_hWnd;
	HDC m_hdc;
	MyTimer* m_pTimer;
	BackGroundScroller* m_pScroller;

};