#include "stdafx.h"
#include "SoundManager.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")



SoundManager* SoundManager::m_pInstance = nullptr;

// SoundManager 싱글톤 구현.
SoundManager* SoundManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new SoundManager();
	}
	return m_pInstance;
}

// 싱글톤 삭제 함수.
void SoundManager::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

/*
	생성자. init호출.
*/
SoundManager::SoundManager()
	: m_AccTime(0)
{
	Init();
}

/*
	소멸자.
*/
SoundManager::~SoundManager()
{
	DeleteInstance();
}

/*
	초기화 함수.
*/
void SoundManager::Init()
{
	return;
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
//const vRESULT SoundManager::PlaySoundWithSoundNum(
//	const _In_ SOUND::SOUND_TYPE soundTypeNum)
//{
//	PlaySound
//
//	return WELL_PERFORMED;
//}