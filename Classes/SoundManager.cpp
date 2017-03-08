#include "stdafx.h"
#include "SoundManager.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")



SoundManager* SoundManager::_instance = nullptr;

// SoundManager 싱글톤 구현.
SoundManager* SoundManager::getInstance()
{
	if (!_instance)
	{
		_instance = new SoundManager();
	}
	return _instance;
}

// 싱글톤 삭제 함수.
void SoundManager::deleteInstance()
{
	delete _instance;
	_instance = nullptr;
	return;
}

/*
	생성자. init호출.
*/
SoundManager::SoundManager()
	: m_AccTime(0)
{
	vRESULT retval = init();
	DebugLogPrint(retval, MESSAGES::creationFailed, _T("In SoundMananger Creation"));
}

/*
	소멸자.
*/
SoundManager::~SoundManager()
{
	deleteInstance();
}

/*
	초기화 함수.
*/
const vRESULT SoundManager::init()
{

	return WELL_PERFORMED;
}

/*
	hInstance 세팅 함수.
	GameManager에서 생성시에 꼭 호출해야한다.
*/
const vRESULT SoundManager::SethInstance(_Inout_ HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	return WELL_PERFORMED;
}

/*
	Soundtype을 이용하여 원하는 사운드를 재생시키는 함수.
*/
const vRESULT SoundManager::PlaySoundWithSoundNum(
	const _In_ SOUND::SOUND_TYPE soundTypeNum)
{
	PlaySound(
		MAKEINTRESOURCE(soundTypeNum),
		m_hInstance,
		SND_RESOURCE | SND_ASYNC);

	return WELL_PERFORMED;
}