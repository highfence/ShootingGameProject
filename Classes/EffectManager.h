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
	static EffectManager* getInstance();
	void deleteInstance();

	void CalProc(const _In_ FLOAT);
	void DrawProc(_Inout_ HDC);

private :

	EffectManager();
	~EffectManager();

	// �̱��� �ν��Ͻ�.
	static EffectManager* _instance;

	// �ڵ鷯�� �ڵ鷯 �Լ���.
	BOOL(EffectManager::*m_pEffectMakerHandler[EFFECT_TYPE_NUM])(const _In_ FLOAT, const _In_ FLOAT);
	BOOL MakeExplodeLight(const _In_ FLOAT, const _In_ FLOAT);

	void init();
	void AccTime(const _In_ FLOAT);
	void ProvideTime(const _In_ FLOAT);
	void ClearVec();

	FLOAT m_AccTime;
	std::vector<Effect*> m_EffectVec;

};