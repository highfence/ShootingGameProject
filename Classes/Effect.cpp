#include "stdafx.h"
#include "Effect.h"

Effect::Effect(const _In_ FLOAT x, const _In_ FLOAT y)
	: m_AccTime(0), m_CutAccTime(0), m_IsEffectDone(FALSE), m_PosX(x), m_PosY(y), m_FrameNum(1), m_IsDrawedOnce(FALSE)
{
	m_pSprite = new CImage;
	m_pShade = new CImage;
	init();
}

void Effect::init()
{
	return;
}

Effect::~Effect()
{
	delete m_pSprite;
	delete m_pShade;
}


BOOL Effect::GetIsEffectDone() const
{
	return m_IsEffectDone;
}

void Effect::AccTime(const _In_ FLOAT dt)
{
	m_CutAccTime += dt;
	m_AccTime += dt;
	return;
}

void Effect::ImgLoad(
	const _In_ std::wstring spriteStr,
	const _In_ std::wstring shadeStr,
	const _In_ INT frameNum)
{
	if (m_IsDrawedOnce == TRUE)
	{
		m_pSprite->Destroy();
		m_pShade->Destroy();
		m_IsDrawedOnce = FALSE;
	}

	std::wstring frameNumString = std::to_wstring(frameNum);
	std::wstring spriteFrame = spriteStr + frameNumString + SpriteExtension;
	m_pSprite->Load(spriteFrame.c_str());

	std::wstring shadeFrame = shadeStr + frameNumString + SpriteExtension;
	m_pShade->Load(shadeFrame.c_str());
	return;
}

void Effect::Draw(_Inout_ HDC drawDC)
{
#pragma warning(push)
#pragma warning(disable : 4244)

	m_pShade->BitBlt(drawDC, m_PosX - m_Width / 2, m_PosY - m_Height / 2, m_Width, m_Height, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_PosX - m_Width / 2, m_PosY - m_Height / 2, m_Width, m_Height, 0, 0, SRCPAINT);
	m_IsDrawedOnce = TRUE;

#pragma warning(pop)
	return;
}

void Effect::FrameCheck()
{
	if ((m_CutAccTime > m_TimePerFrame) && (m_FrameNum <= m_MaxFrameNum))
	{
		++m_FrameNum;
		ImgLoad(m_SpriteStr, m_ShadeStr, m_FrameNum);
		m_CutAccTime = 0.f;
	}
	else if (m_FrameNum == m_MaxFrameNum)
	{
		m_IsEffectDone = TRUE;
	}

	return;
}

void Effect::CalProc(const _In_ FLOAT dt)
{
	AccTime(dt);
	FrameCheck();
	return;
}

void Effect::DrawProc(_Inout_ HDC drawDC)
{
	Draw(drawDC);
	return;
}