#include "stdafx.h"
#include "Effect.h"

Effect::Effect(const _In_ Vec createPos)
	: m_Pos(createPos),
	m_AccTime(0),
	m_CutAccTime(0),
	m_IsEffectDone(FALSE),
	m_FrameNum(1),
	m_IsDrawedOnce(FALSE),
	// TODO :: 널포인터 생성
	m_pSprite(nullptr),
	m_pShade(nullptr)
{
	m_FloatSpeed = 0.f;
	m_pSprite = new CImage();
	m_pShade = new CImage();
	init();
}

Effect::Effect(
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
	: m_FloatVec(floatVec),
	m_FloatSpeed(floatSpeed),
	m_Pos(createPos),
	m_AccTime(0),
	m_CutAccTime(0),
	m_IsEffectDone(FALSE),
	m_FrameNum(1),
	m_IsDrawedOnce(FALSE),
	m_pSprite(nullptr),
	m_pShade(nullptr)
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
	// TODO :: 널포인터까지 (Release 함수)
	delete m_pSprite;
	m_pSprite = nullptr;
	delete m_pShade;
	m_pShade = nullptr;
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
	const _In_ std::wstring fileExtension,
	const _In_ INT frameNum)
{
	if (m_IsDrawedOnce == TRUE)
	{
		m_pSprite->Destroy();
		m_pShade->Destroy();
		m_IsDrawedOnce = FALSE;
	}

	std::wstring frameNumString = std::to_wstring(frameNum);
	std::wstring spriteFrame = spriteStr + frameNumString + fileExtension;
	m_pSprite->Load(spriteFrame.c_str());

	std::wstring shadeFrame = shadeStr + frameNumString + fileExtension;
	m_pShade->Load(shadeFrame.c_str());
	return;
}

void Effect::Draw(_Inout_ HDC drawDC)
{
#pragma warning(push)
#pragma warning(disable : 4244)

	m_pShade->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCPAINT);
	m_IsDrawedOnce = TRUE;

#pragma warning(pop)
	return;
}

void Effect::FrameCheck()
{
	if ((m_CutAccTime > m_TimePerFrame) && (m_FrameNum <= m_MaxFrameNum))
	{
		++m_FrameNum;
		ImgLoad(m_SpriteStr, m_ShadeStr, m_FileExtensionStr, m_FrameNum);
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
	CalFloat(dt);
	FrameCheck();
	return;
}

void Effect::DrawProc(_Inout_ HDC drawDC)
{
	Draw(drawDC);
	return;
}

vRESULT Effect::CalFloat(const _In_ FLOAT dt)
{
	if (m_FloatSpeed != 0.f)
	{
		m_Pos.x += m_FloatVec.x * m_FloatSpeed * dt;
		m_Pos.y += m_FloatVec.y * m_FloatSpeed * dt;
	}

	return WELL_PERFORMED;
}