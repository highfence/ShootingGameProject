#include "stdafx.h"
#include "GameManager.h"
#include "MyTimer.h"
#include "BackGroundScroller.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "SoundManager.h"

GameManager::GameManager(_Inout_ HWND hWnd, _Inout_ HINSTANCE hInstance)
	: m_hWnd(hWnd), m_hInstance(hInstance)
{
	m_pTimer = new MyTimer;
	m_pScroller = new BackGroundScroller;
	m_pPlayer = new Player;
	m_pEnemyManager = EnemyManager::getInstance();
	m_pEffectManager = EffectManager::getInstance();
	SoundManager::getInstance()->SethInstance(hInstance);
	
	init();
}

void GameManager::init()
{
	m_hdc = GetDC(m_hWnd);
	m_pTimer->Init();
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
	m_pEnemyManager->CalProc(dt);
	m_pEffectManager->CalProc(dt);
	if (m_pPlayer->GetIsPlayerAlived())
	{
		m_pPlayer->CalProc(m_ByKey, dt);
	}

	return;
}

void GameManager::DrawProc(const _In_ FLOAT dt)
{
	HDC memoryDC = CreateCompatibleDC(m_hdc);
	HBITMAP memoryBitmap = CreateCompatibleBitmap(m_hdc, winWidth, winHeight);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memoryDC, memoryBitmap);

	Rectangle(memoryDC, 0, 0, winWidth, winHeight);

	m_pScroller->Scroll(memoryDC, dt);
	if (m_pPlayer->GetIsPlayerAlived())
	{
		m_pPlayer->DrawProc(memoryDC);
	}
	m_pEnemyManager->DrawProc(memoryDC);
	m_pEffectManager->DrawProc(memoryDC);

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
			// 현재 키입력이 있는 경우.
			if (m_ByKey[i] & 0x80)
			{
				// 그 전 키입력이 없었다면 시작상태로 만들어준다 (PUSHKEY)
				if (!m_OldKey[i])
				{
					m_OldKey[i] = 1;
					m_ByKey[i] |= 0x40;
				}
				// 아니라면 그냥 누르고 있는 중 (HOLDKEY)
			}
			// 키입력이 현재 없는 경우.
			else
			{
				// 그 전 키입력이 없었다면 띄는 상태로 만들어준다. (PULLKEY)
				if (m_OldKey[i])
				{
					m_OldKey[i] = 0;
					m_ByKey[i] = 0x20;
				}
				// 아니라면 그냥 안누르고 있는 상태.
				else
				{
					m_ByKey[i] = 0x10;
				}
			}

		}
	}

	return;
}

