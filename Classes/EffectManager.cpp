#include "stdafx.h"
#include "Effect.h"
#include "ExplodeLight.h"
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
	deleteInstance();
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