#pragma once

// TODO :: ExplodeLight가 생성시에 스피드를 받아서 비행기가 움직였던 속도로 움직이게 하는 건 어떨까?

using namespace EFFECT;

class Effect
{
public :
	Effect() = delete;
	Effect(const _In_ Vec);
	Effect(
		const _In_ Vec,
		const _In_ FLOAT,
		const _In_ Vec);

	virtual ~Effect();
	virtual void LoadInitialImg() = 0;
	virtual void InitialDataSubstitude() = 0;

	void CalProc(const _In_ FLOAT);
	void DrawProc(_Inout_ HDC);

	BOOL GetIsEffectDone() const;
	void AccTime(const _In_ FLOAT);

	void ImgLoad(
		const _In_ std::wstring,
		const _In_ std::wstring,
		const _In_ std::wstring,
		const _In_ INT);

	void Draw(_Inout_ HDC);
	vRESULT CalFloat(const _In_ FLOAT);
	void FrameCheck();


	Vec m_Pos = zero;
	Vec m_FloatVec = zero;
	FLOAT m_FloatSpeed = 0.f;
	FLOAT m_Width = 0.f;
	FLOAT m_Height = 0.f;
	FLOAT m_TimePerFrame = 0.f;
	INT m_FrameNum = 1;
	INT m_MaxFrameNum = 0;
	CImage* m_pSprite = nullptr;
	CImage* m_pShade = nullptr;
	FLOAT m_AccTime = 0.f;
	FLOAT m_CutAccTime = 0.f;
	std::wstring m_SpriteStr;
	std::wstring m_ShadeStr;
	std::wstring m_FileExtensionStr;

private :

	void Init();
	BOOL m_IsEffectDone = FALSE;
	BOOL m_IsDrawedOnce = FALSE;
};