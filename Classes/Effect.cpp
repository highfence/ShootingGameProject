#include "stdafx.h"
#include "Effect.h"

Effect::Effect(const _In_ FLOAT x, const _In_ FLOAT y)
	: m_AccTime(0), m_IsEffectDone(FALSE), m_PosX(x), m_PosY(y)
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
	m_AccTime += dt;
	return;
}

void Effect::ImgLoad(const _In_ std::wstring spriteStr, const _In_ std::wstring shadeStr, const _In_ INT frameNum)
{
	std::wstring spriteFrame = spriteStr + _T("%d", frameNum) + SpriteExtension;
	m_pSprite->Load(spriteFrame.c_str());
	std::wstring shadeFrame = shadeStr + _T("%d", frameNum) + SpriteExtension;
	m_pShade->Load(shadeFrame.c_str());
	return;
}