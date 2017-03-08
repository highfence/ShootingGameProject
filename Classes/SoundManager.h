#pragma once

/*
	SoundManager
	사운드를 출력해주는 싱글톤 클래스.
	생성 후 SethInstance를 해주어야 사용이 가능하다.
*/

class SoundManager
{
public :
	static SoundManager* getInstance();
	void deleteInstance();
	const vRESULT SethInstance(_Inout_ HINSTANCE);
	const vRESULT PlaySoundWithSoundNum(const _In_ SOUND::SOUND_TYPE);

private :
	SoundManager();
	~SoundManager();

	// 싱글톤 인스턴스.
	static SoundManager* _instance;
	
	const vRESULT init();

	HINSTANCE m_hInstance;
	FLOAT m_AccTime;
	
};