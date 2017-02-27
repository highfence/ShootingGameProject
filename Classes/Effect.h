#pragma once

using namespace EFFECT;

class Effect
{
public :
	Effect(const _In_ FLOAT, const _In_ FLOAT);
	virtual ~Effect();

	BOOL GetIsEffectDone() const;
	void AccTime(const _In_ FLOAT);
	void ImgLoad(const _In_ std::wstring, const _In_ std::wstring, const _In_ INT);

	virtual void LoadInitialImg() = 0;

	FLOAT m_PosX;
	FLOAT m_PosY;
	CImage* m_pSprite;
	CImage* m_pShade;
	FLOAT m_AccTime;

private :
	// 인자 없이 생성 불가.
	Effect();

	void init();
	BOOL m_IsEffectDone;
};