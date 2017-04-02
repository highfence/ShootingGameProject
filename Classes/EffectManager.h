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

	template <typename T>
	BOOL MakeEffect(const _In_ Vec);
	template <typename T>
	BOOL MakeEffectWithFloat(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);



private :

	EffectManager();
	~EffectManager();

	// �̱��� �ν��Ͻ�.
	static EffectManager* m_pInstance;

		void Init();
	void AccTime(const _In_ FLOAT);
	void ClearVec();

	FLOAT m_AccTime;
	std::vector<Effect*> m_EffectVec;

};

template<typename T>
inline BOOL EffectManager::MakeEffect(const Vec createPos)
{
	auto newEffect = new T(createPos);
	m_EffectVec.emplace_back((Effect*)newEffect);
	return TRUE;
}

template<typename T>
inline BOOL EffectManager::MakeEffectWithFloat(
	const Vec createPos,
	const FLOAT floatSpeed,
	const Vec floatVec)
{
	auto newEffect = new T(createPos, floatSpeed, floatVec);
	m_EffectVec.emplace_back((Effect*)newEffect);
	return TRUE;
}
