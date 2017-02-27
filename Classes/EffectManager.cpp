#include "stdafx.h"
#include "Effect.h"
#include "EffectManager.h"

EffectManager* EffectManager::_instance = nullptr;

// EffectManager �̱��� ����.
EffectManager* EffectManager::getInstance()
{
	if (!_instance)
	{
		_instance = new EffectManager();
	}
	return _instance;
}

// �̱��� ���� �Լ�.
void EffectManager::deleteInstance()
{
	delete _instance;
	_instance = nullptr;
	return;
}

// ������.
EffectManager::EffectManager()
	: m_AccTime(0)
{
	init();
}

// �ʱ�ȭ �Լ�.
void EffectManager::init()
{
	m_pEffectMakerHandler[EXPLODE_LIGHT] = &EffectManager::MakeExplodeLight;
	return;
}

// �Ҹ���.
EffectManager::~EffectManager()
{

}

// ��� ��� �Լ� (GameManager->Update->CalProc���� ȣ��)
void EffectManager::CalProc(const _In_ FLOAT dt)
{
	AccTime(dt);
	return;
}

// ��� ��� �Լ� (GameManager->Update->DrawProc���� ȣ��)
void EffectManager::DrawProc(_Inout_ HDC drawDC)
{

	return;
}

// �ð� ���� �Լ�.
void EffectManager::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	return;
}

// ���� ���� ����Ʈ�鿡�� �ð��� �й��ϴ� �Լ�.
void EffectManager::ProvideTime(const _In_ FLOAT dt)
{
	for (auto i : m_EffectVec)
	{
		i->AccTime(dt);
	}
	return;
}

// ���� ����Ʈ���� ���Ϳ��� �����ϴ� �Լ�.
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
