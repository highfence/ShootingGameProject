#include "stdafx.h"
#include "SoundManager.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")



SoundManager* SoundManager::_instance = nullptr;

// SoundManager �̱��� ����.
SoundManager* SoundManager::getInstance()
{
	if (!_instance)
	{
		_instance = new SoundManager();
	}
	return _instance;
}

// �̱��� ���� �Լ�.
void SoundManager::deleteInstance()
{
	delete _instance;
	_instance = nullptr;
	return;
}

/*
	������. initȣ��.
*/
SoundManager::SoundManager()
	: m_AccTime(0)
{
	vRESULT retval = init();
	DebugLogPrint(retval, MESSAGES::creationFailed, _T("In SoundMananger Creation"));
}

/*
	�Ҹ���.
*/
SoundManager::~SoundManager()
{
	deleteInstance();
}

/*
	�ʱ�ȭ �Լ�.
*/
const vRESULT SoundManager::init()
{

	return WELL_PERFORMED;
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