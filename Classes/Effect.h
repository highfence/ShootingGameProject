#pragma once

// TODO :: ExplodeLight가 생성시에 스피드를 받아서 비행기가 움직였던 속도로 움직이게 하는 건 어떨까?

using namespace EFFECT;

class Effect
{
public :
	Effect(const _In_ Vec);
	Effect(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);

	virtual ~Effect();
	virtual void LoadInitialImg() = 0;

	void CalProc(const _In_ FLOAT);
	void DrawProc(_Inout_ HDC);

	BOOL GetIsEffectDone() const;
	void AccTime(const _In_ FLOAT);
	void ImgLoad(
		const _In_ std::wstring,
		const _In_ std::wstring,
		const _In_ INT);

	void Draw(_Inout_ HDC);
	vRESULT CalFloat(const _In_ FLOAT);
	void FrameCheck();


	Vec m_Pos;
	Vec m_FloatVec;
	FLOAT m_FloatSpeed;
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