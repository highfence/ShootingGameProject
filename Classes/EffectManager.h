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
	static EffectManager* GetInstance();
	void DeleteInstance();

	void CalProc(const _In_ FLOAT);
	void DrawProc(_Inout_ HDC);
	void MakeEffect(
		const _In_ INT,
		const _In_ Vec);

	void MakeEffect(
		const _In_ INT,
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);

private :

	EffectManager();
	~EffectManager();

	// 싱글톤 인스턴스.
	static EffectManager* m_pInstance;

	// 핸들러와 핸들러 함수들.
	BOOL(EffectManager::*m_pEffectMakerHandler[EFFECT::EFFECT_TYPE::EFFECT_TYPE_NUM])(const _In_ Vec);
	BOOL(EffectManager::*m_pEffectMakerHandlerWithFloat[EFFECT::EFFECT_TYPE::EFFECT_TYPE_NUM])(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);

	BOOL MakeExplodeLight(const _In_ Vec);
	BOOL MakeExplodeLightWithFloat(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);

	BOOL MakeExplodeHit(const _In_ Vec);
	BOOL MakeExplodeHitWithFloat(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);

	BOOL MakeExplodeSmoke(const _In_ Vec);
	BOOL MakeExplodeSmokeWithFloat(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);

	BOOL MakeExplodeArc(const _In_ Vec);
	BOOL MakeExplodeArcWithFloat(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);

	void Init();
	void AccTime(const _In_ FLOAT);
	void ClearVec();

	FLOAT m_AccTime;
	std::vector<Effect*> m_EffectVec;

};