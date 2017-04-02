#include "stdafx.h"
#include "Effect.h"
#include "ExplodeLight.h"
#include "ExplodeHit.h"
#include "ExplodeSmoke.h"
#include "ExplodeArc.h"
#include "EffectManager.h"
using namespace EFFECT;

EffectManager* EffectManager::m_pInstance = nullptr;

// EffectManager �̱��� ����.
EffectManager* EffectManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new EffectManager();
	}
	return m_pInstance;
}

// �̱��� ���� �Լ�.
void EffectManager::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

// ������.
EffectManager::EffectManager()
	: m_AccTime(0)
{
	Init();
}

// �ʱ�ȭ �Լ�.
void EffectManager::Init()
{
	return;
}

// �Ҹ���.
EffectManager::~EffectManager()
{
	DeleteInstance();
}

// ��� ��� �Լ� (GameManager->Update->CalProc���� ȣ��)
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

// ��� ��� �Լ� (GameManager->Update->DrawProc���� ȣ��)
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

// �ð� ���� �Լ�.
void EffectManager::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	return;
}

// ���� ����Ʈ���� ���Ϳ��� �����ϴ� �Լ�.
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
