#pragma once

// TODO :: ExplodeLight�� �����ÿ� ���ǵ带 �޾Ƽ� ����Ⱑ �������� �ӵ��� �����̰� �ϴ� �� ���?

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
	// ���� ���� ���� �Ұ�.
	Effect();

	void init();
	BOOL m_IsEffectDone;
	BOOL m_IsDrawedOnce;
};