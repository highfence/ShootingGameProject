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
	// TODO :: EnemyManager ������ �ε��ð��� ��Ƿ� ������� �ε� ó��.
	// ������ �ð��� ���� ȭ�� ����.
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
	m_AccTime += dt;

	// 60������
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

	// EnemyManager���� �ڽ��� ��ġ ���� ����.
	EnemyManager::GetInstance()->SetPlayerInfo(*m_pPlayer);

	m_pEnemyManager->CalcProc(dt);
	m_pEffectManager->CalProc(dt);
	m_pUIManager->CalProc(dt);

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
	m_pUIManager->DrawProc(memoryDC);

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

