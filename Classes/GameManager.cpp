#include "stdafx.h"
#include "GameManager.h"
#include "MyTimer.h"
#include "BackGroundScroller.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "UIManager.h"
#include "SoundManager.h"

GameManager::GameManager(_Inout_ HWND hWnd, _Inout_ HINSTANCE hInstance)
	: m_hWnd(hWnd),
	m_hInstance(hInstance),
	m_AccTime(0.f),
	m_pTimer(nullptr),
	m_pScroller(nullptr),
	m_pPlayer(nullptr)
{
	m_pTimer = new MyTimer();
	m_pScroller = new BackGroundScroller();
	m_pPlayer = new Player();
	// TODO :: EnemyManager 때문에 로딩시간이 기므로 쓰레드로 로딩 처리.
	// 나머지 시간은 메인 화면 띄우기.
	m_pEnemyManager = EnemyManager::GetInstance();
	m_pEffectManager = EffectManager::GetInstance();
	m_pUIManager = UIManager::GetInstance();
	SoundManager::GetInstance()->SethInstance(hInstance);
	
	init();
}

void GameManager::init()
{
	m_hdc = GetDC(m_hWnd);
	m_pTimer->Init();
	m_MemoryDC = CreateCompatibleDC(m_hdc);
	m_MemoryBitmap = CreateCompatibleBitmap(m_hdc, winWidth, winHeight);
	m_OldBitmap = (HBITMAP)SelectObject(m_MemoryDC, m_MemoryBitmap);

	return;
}

GameManager::~GameManager()
{
	delete m_pTimer;
	delete m_pScroller;
	DeleteObject(m_MemoryBitmap);
	DeleteDC(m_MemoryDC);
	ReleaseDC(m_hWnd, m_hdc);
}

void GameManager::Update()
{
	m_pTimer->ProcessTime();
	FLOAT dt = m_pTimer->GetElapsedTime();
	m_AccTime += dt;

	// 60프레임
	if (m_AccTime > 0.0167f)
	{
		CalProc(m_AccTime);
		DrawProc(m_AccTime);
		m_AccTime = 0.f;
	}
	return;
}

void GameManager::CalProc(const _In_ FLOAT dt)
{
	GetKeyState();
	if (m_pPlayer->GetIsPlayerAlived())
	{
		m_pPlayer->CalProc(m_ByKey, dt);
	}

	// EnemyManager에게 자신의 위치 정보 전달.
	EnemyManager::GetInstance()->SetPlayerInfo(*m_pPlayer);

	m_pEnemyManager->CalcProc(dt);
	m_pEffectManager->CalProc(dt);
	m_pUIManager->CalProc(dt);

	return;
}

void GameManager::DrawProc(const _In_ FLOAT dt)
{

	Rectangle(m_MemoryDC, 0, 0, winWidth, winHeight);

	m_pScroller->Scroll(m_MemoryDC, dt);
	if (m_pPlayer->GetIsPlayerAlived())
	{
		m_pPlayer->DrawProc(m_MemoryDC);
	}
	m_pEnemyManager->DrawProc(m_MemoryDC);
	m_pEffectManager->DrawProc(m_MemoryDC);
	m_pUIManager->DrawProc(m_MemoryDC);

	BitBlt(m_hdc, 0, 0, winWidth, winHeight, m_MemoryDC, 0, 0, SRCCOPY);

	SelectObject(m_hdc, m_OldBitmap);
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

