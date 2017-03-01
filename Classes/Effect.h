#pragma once

using namespace EFFECT;

class Effect
{
public :
	Effect(const _In_ FLOAT, const _In_ FLOAT);
	virtual ~Effect();

	void CalProc(const _In_ FLOAT);
	void DrawProc(_Inout_ HDC);

	BOOL GetIsEffectDone() const;
	void AccTime(const _In_ FLOAT);
	void ImgLoad(const _In_ std::wstring, const _In_ std::wstring, const _In_ INT);
	void Draw(_Inout_ HDC);
	void FrameCheck();

	virtual void LoadInitialImg() = 0;

	FLOAT m_PosX;
	FLOAT m_PosY;
	FLOAT m_Width;
	FLOAT m_Height;
	FLOAT m_TimePerFrame;
	INT m_FrameNum;
	INT m_MaxFrameNum;
	CImage* m_pSprite;
	CImage* m_pShade;
	FLOAT m_AccTime;
	FLOAT m_CutAccTime;
	std::wstring m_SpriteStr;
	std::wstring m_ShadeStr;

private :
	// 인자 없이 생성 불가.
	Effect();

	void init();
	BOOL m_IsEffectDone;
	BOOL m_IsDrawedOnce;
};