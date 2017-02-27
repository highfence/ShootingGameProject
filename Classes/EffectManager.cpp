#include "stdafx.h"
#include "Effect.h"
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

}

// 계산 담당 함수 (GameManager->Update->CalProc에서 호출)
void EffectManager::CalProc(const _In_ FLOAT dt)
{
	AccTime(dt);
	return;
}

// 출력 담당 함수 (GameManager->Update->DrawProc에서 호출)
void EffectManager::DrawProc(_Inout_ HDC drawDC)
{

	return;
}

// 시간 누적 함수.
void EffectManager::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	return;
}

// 벡터 안의 이펙트들에게 시간을 분배하는 함수.
void EffectManager::ProvideTime(const _In_ FLOAT dt)
{
	for (auto i : m_EffectVec)
	{
		i->AccTime(dt);
	}
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

BOOL EffectManager::MakeExplodeLight(const _In_ FLOAT, const _In_ FLOAT)
{
	
	return TRUE;
}
