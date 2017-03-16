#include "stdafx.h"
#include "SoundManager.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")



SoundManager* SoundManager::m_pInstance = nullptr;

// SoundManager �̱��� ����.
SoundManager* SoundManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new SoundManager();
	}
	return m_pInstance;
}

// �̱��� ���� �Լ�.
void SoundManager::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

/*
	������. initȣ��.
*/
SoundManager::SoundManager()
	: m_AccTime(0)
{
	Init();
}

/*
	�Ҹ���.
*/
SoundManager::~SoundManager()
{
	DeleteInstance();
}

/*
	�ʱ�ȭ �Լ�.
*/
void SoundManager::Init()
{
	return;
}

/*
	hInstance ���� �Լ�.
	GameManager���� �����ÿ� �� ȣ���ؾ��Ѵ�.
*/
const vRESULT SoundManager::SethInstance(_Inout_ HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	return WELL_PERFORMED;
}

/*
	Soundtype�� �̿��Ͽ� ���ϴ� ���带 �����Ű�� �Լ�.
*/
//const vRESULT SoundManager::PlaySoundWithSoundNum(
//	const _In_ SOUND::SOUND_TYPE soundTypeNum)
//{
//	PlaySound
//
//	return WELL_PERFORMED;
//}