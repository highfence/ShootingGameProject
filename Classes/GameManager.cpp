#include "stdafx.h"
#include "GameManager.h"
#include "MyTimer.h"
#include "BackGroundScroller.h"
#include "Player.h"
#include "EnemyManager.h"

GameManager::GameManager(_Inout_ HWND hWnd)
	: m_hWnd(hWnd)
{
	m_pTimer = new MyTimer;
	m_pScroller = new BackGroundScroller;
	m_pPlayer = new Player;
	m_pEnemyManager = new EnemyManager;
	init();
}

void GameManager::init()
{
	m_hdc = GetDC(m_hWnd);
	m_pTimer->Init();
	m_pEnemyManager->MakeEnemy(ENEMY::ENEMY_TYPE::ENEMY_ITEM, 450, 0, ENEMY::FLY_STRAIGHT, 0);
	return;
}

GameManager::~GameManager()
{
	delete m_pTimer;
	delete m_pScroller;
	ReleaseDC(m_hWnd, m_hdc);
}

void GameManager::Update()
{
	m_pTimer->ProcessTime();
	FLOAT dt = m_pTimer->GetElapsedTime();

	CalProc(dt);
	DrawProc(dt);
	return;
}

void GameManager::CalProc(const _In_ FLOAT dt)
{
	GetKeyState();
	m_pEnemyManager->CalFly(dt);
	m_pEnemyManager->ClearVec();
	m_pPlayer->Move(m_ByKey, dt);
	m_pPlayer->MissileFly(dt);
	return;
}

void GameManager::DrawProc(const _In_ FLOAT dt)
{
	HDC memoryDC = CreateCompatibleDC(m_hdc);
	HBITMAP memoryBitmap = CreateCompatibleBitmap(m_hdc, winWidth, winHeight);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memoryDC, memoryBitmap);

	Rectangle(memoryDC, 0, 0, winWidth, winHeight);

	m_pScroller->Scroll(memoryDC, dt);
	m_pPlayer->Draw(memoryDC, dt);
	m_pEnemyManager->Draw(memoryDC);

	BitBlt(m_hdc, 0, 0, winWidth, winHeight, memoryDC, 0, 0, SRCCOPY);

	SelectObject(m_hdc, oldBitmap);
	DeleteObject(memoryBitmap);
	DeleteDC(memoryDC);
	return;
}

void GameManager::GetKeyState()
{
	if (GetKeyboardState(m_ByKey))
	{
		for (int i = 0; i < keyboardNumber; ++i)
		{
			// ���� Ű�Է��� �ִ� ���.
			if (m_ByKey[i] & 0x80)
			{
				// �� �� Ű�Է��� �����ٸ� ���ۻ��·� ������ش� (PUSHKEY)
				if (!m_OldKey[i])
				{
					m_OldKey[i] = 1;
					m_ByKey[i] |= 0x40;
				}
				// �ƴ϶�� �׳� ������ �ִ� �� (HOLDKEY)
			}
			// Ű�Է��� ���� ���� ���.
			else
			{
				// �� �� Ű�Է��� �����ٸ� ��� ���·� ������ش�. (PULLKEY)
				if (m_OldKey[i])
				{
					m_OldKey[i] = 0;
					m_ByKey[i] = 0x20;
				}
				// �ƴ϶�� �׳� �ȴ����� �ִ� ����.
				else
				{
					m_ByKey[i] = 0x10;
				}
			}

		}
	}

	return;
}