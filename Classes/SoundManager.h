#pragma once

/*
	SoundManager
	���带 ������ִ� �̱��� Ŭ����.
	���� �� SethInstance�� ���־�� ����� �����ϴ�.
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

	// �̱��� �ν��Ͻ�.
	static SoundManager* _instance;
	
	const vRESULT init();

	HINSTANCE m_hInstance;
	FLOAT m_AccTime;
	
};