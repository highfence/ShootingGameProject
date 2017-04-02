#include "stdafx.h"
#include "Effect.h"
#include "ExplodeLight.h"
#include "ExplodeHit.h"
#include "ExplodeSmoke.h"
#include "ExplodeArc.h"
#include "EffectManager.h"
using namespace EFFECT;

EffectManager* EffectManager::m_pInstance = nullptr;

// EffectManager 싱글톤 구현.
EffectManager* EffectManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new EffectManager();
	}
	return m_pInstance;
}

// 싱글톤 삭제 함수.
void EffectManager::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

// 생성자.
EffectManager::EffectManager()
	: m_AccTime(0)
{
	Init();
}

// 초기화 함수.
void EffectManager::Init()
{
	return;
}

// 소멸자.
EffectManager::~EffectManager()
{
	DeleteInstance();
}

// 계산 담당 함수 (GameManager->Update->CalProc에서 호출)
void EffectManager::CalProc(const _In_ FLOAT dt)
{
	AccTime(dt);
	for (auto i : m_EffectVec)
	{
		i->CalProc(dt);
	}
	ClearVec();

	return;
}

// 출력 담당 함수 (GameManager->Update->DrawProc에서 호출)
void EffectManager::DrawProc(_Inout_ HDC drawDC)
{
#ifdef _DEBUG
	SetTextAlign(drawDC, TA_LEFT);
	std::wstring DebugLabel = _T("Effect Vector Size : ") + std::to_wstring(m_EffectVec.size());
	TextOut(drawDC, 10, 30, DebugLabel.c_str(), wcslen(DebugLabel.c_str()));
#endif

	for (auto i : m_EffectVec)
	{
		i->DrawProc(drawDC);
	}
	return;
}

// 시간 누적 함수.
void EffectManager::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	return;
}

// 끝난 이펙트들을 벡터에서 정리하는 함수.
void EffectManager::ClearVec()
{
	std::vector<Effect*>::iterator iter = m_EffectVec.begin();
	while (iter != m_EffectVec.end())
	{
		if (((*iter)->GetIsEffectDone()))
		{
			iter = m_EffectVec.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	return;
}
