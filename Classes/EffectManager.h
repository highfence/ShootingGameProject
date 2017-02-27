#pragma once

// 전방 선언
class Effect;

/*
	EffectManager
	이펙트들을 관리하는 싱글톤 클래스.
	Effect가 생성되면 시간에 따라 출력하는 역할을 해준다.
*/

class EffectManager
{
public :
	// 싱글톤 호출 / 삭제
	static EffectManager* getInstance();
	void deleteInstance();

	void CalProc(const _In_ FLOAT);
	void DrawProc(_Inout_ HDC);

private :

	EffectManager();
	~EffectManager();

	// 싱글톤 인스턴스.
	static EffectManager* _instance;

	// 핸들러와 핸들러 함수들.
	BOOL(EffectManager::*m_pEffectMakerHandler[EFFECT_TYPE_NUM])(const _In_ FLOAT, const _In_ FLOAT);
	BOOL MakeExplodeLight(const _In_ FLOAT, const _In_ FLOAT);

	void init();
	void AccTime(const _In_ FLOAT);
	void ProvideTime(const _In_ FLOAT);
	void ClearVec();

	FLOAT m_AccTime;
	std::vector<Effect*> m_EffectVec;

};