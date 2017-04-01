#pragma once

// ���� ����
class Effect;

/*
	EffectManager
	����Ʈ���� �����ϴ� �̱��� Ŭ����.
	Effect�� �����Ǹ� �ð��� ���� ����ϴ� ������ ���ش�.
*/

class EffectManager
{
public :
	// �̱��� ȣ�� / ����
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

	// �̱��� �ν��Ͻ�.
	static EffectManager* m_pInstance;

	// �ڵ鷯�� �ڵ鷯 �Լ���.
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