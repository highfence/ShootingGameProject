#include "stdafx.h"
#include "Effect.h"
#include "ExplodeLight.h"
#include "EffectManager.h"

EffectManager* EffectManager::_instance = nullptr;

// EffectManager 싱글톤 구현.
EffectManager* EffectManager::getInstance()
{
	if (!_instance)
	{
		_instance = new EffectManager();
	}
	return _instance;
}

// 싱글톤 삭제 함수.
void EffectManager::deleteInstance()
{
	delete _instance;
	_instance = nullptr;
	return;
}

// 생성자.
EffectManager::EffectManager()
	: m_AccTime(0)
{
	init();
}

// 초기화 함수.
void EffectManager::init()
{
	m_pEffectMakerHandler[EXPLODE_LIGHT] = &EffectManager::MakeExplodeLight;
	return;
}

// 소멸자.
EffectManager::~EffectManager()
{
	deleteInstance();
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
		if (!(*iter)->GetIsEffectDone())
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

BOOL EffectManager::MakeExplodeLight(const _In_ FLOAT x, const _In_ FLOAT y)
{
	auto newEffect = new ExplodeLight(x, y);
	m_EffectVec.push_back(newEffect);
	return TRUE;
}

void EffectManager::MakeEffect(const _In_ INT effectType, const _In_ FLOAT creationX, const _In_ FLOAT creationY)
{
	(this->*m_pEffectMakerHandler[effectType])(creationX, creationY);
	return;
}