#pragma once

// ���漱��
class MyTimer;
class BackGroundScroller;

class GameManager
{
public :

	GameManager(_In_ HWND);
	~GameManager();

	void Update();

private :

	// ���� ���� ���� �Ұ�.
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