#include "stdafx.h"
#include "Effect.h"
#include "ExplodeLight.h"
#include "ExplodeHit.h"
#include "ExplodeSmoke.h"
#include "ExplodeArc.h"
#include "EffectManager.h"

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
	m_pEffectMakerHandler[EXPLODE_LIGHT] = &EffectManager::MakeExplodeLight;
	m_pEffectMakerHandler[EXPLODE_HIT] = &EffectManager::MakeExplodeHit;
	m_pEffectMakerHandler[EXPLODE_SMOKE] = &EffectManager::MakeExplodeSmoke;
	m_pEffectMakerHandler[EXPLODE_ARC] = &EffectManager::MakeExplodeArc;

	m_pEffectMakerHandlerWithFloat[EXPLODE_LIGHT] = &EffectManager::MakeExplodeLightWithFloat;
	m_pEffectMakerHandlerWithFloat[EXPLODE_HIT] = &EffectManager::MakeExplodeHitWithFloat;
	m_pEffectMakerHandlerWithFloat[EXPLODE_SMOKE] = &EffectManager::MakeExplodeSmokeWithFloat;
	m_pEffectMakerHandlerWithFloat[EXPLODE_ARC] = &EffectManager::MakeExplodeArcWithFloat;

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

BOOL EffectManager::MakeExplodeLight(
	const _In_ Vec createPos)
{
	auto newEffect = new ExplodeLight(createPos);
	m_EffectVec.push_back(newEffect);
	return TRUE;
}

BOOL EffectManager::MakeExplodeLightWithFloat(
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
{
	auto newEffect = new ExplodeLight(createPos, floatSpeed, floatVec);
	m_EffectVec.push_back(newEffect);
	return TRUE;
}

BOOL EffectManager::MakeExplodeHit(
	const _In_ Vec createPos)
{
	auto newEffect = new ExplodeHit(createPos);
	m_EffectVec.push_back(newEffect);
	return TRUE;
}

BOOL EffectManager::MakeExplodeHitWithFloat(
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
{
	auto newEffect = new ExplodeHit(createPos, floatSpeed, floatVec);
	m_EffectVec.push_back(newEffect);
	return TRUE;
}

BOOL EffectManager::MakeExplodeSmoke(
	const _In_ Vec createPos)
{
	auto newEffect = new ExplodeSmoke(createPos);
	m_EffectVec.push_back(newEffect);
	return TRUE;
}

BOOL EffectManager::MakeExplodeSmokeWithFloat(
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
{
	auto newEffect = new ExplodeSmoke(createPos, floatSpeed, floatVec);
	m_EffectVec.push_back(newEffect);
	return TRUE;
}

BOOL EffectManager::MakeExplodeArc(
	const _In_ Vec createPos)
{
	auto newEffect = new ExplodeArc(createPos);
	m_EffectVec.push_back(newEffect);
	return TRUE;
}

BOOL EffectManager::MakeExplodeArcWithFloat(
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
{
	auto newEffect = new ExplodeArc(createPos, floatSpeed, floatVec);
	m_EffectVec.push_back(newEffect);
	return TRUE;
}
void EffectManager::MakeEffect(
	const _In_ INT effectType,
	const _In_ Vec createPos)
{
	(this->*m_pEffectMakerHandler[effectType])(createPos);
	return;
}

void EffectManager::MakeEffect(
	const _In_ INT effectType,
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
{
	(this->*m_pEffectMakerHandlerWithFloat[effectType])(
		createPos,
		floatSpeed,
		floatVec);
	return;
}