#include "stdafx.h"
#include "ExplodeArc.h"

const std::wstring explodeArcSpritePath = _T("../Resources/FX/explosion_1_0");
const std::wstring explodeArcShadePath = _T("../Resources/FX/explosion_1S_0");
const std::wstring explodeArcExtension = _T(".png");
const INT explodeArcWidth = 52;
const INT explodeArcHeight = 51;
const FLOAT explodeArcFrameTime = 0.1f;
const INT explodeArcMaxFrameNum = 11;

ExplodeArc::ExplodeArc(const _In_ Vec createPos)
	: Effect(createPos)
{
	init();
}

ExplodeArc::ExplodeArc(
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
	: Effect(createPos, floatSpeed, floatVec)
{
	init();
}

void ExplodeArc::init()
{
	InitialDataSubstitude();
	LoadInitialImg();
	return;
}

ExplodeArc::~ExplodeArc()
{

}

void ExplodeArc::LoadInitialImg()
{
	m_SpriteStr = explodeArcSpritePath;
	m_ShadeStr = explodeArcShadePath;
	m_FileExtensionStr = explodeArcExtension;
	ImgLoad(explodeArcSpritePath, explodeArcShadePath, explodeArcExtension, 1);
	return;
}

void ExplodeArc::InitialDataSubstitude()
{
	m_Width = explodeArcWidth;
	m_Height = explodeArcHeight;
	m_TimePerFrame = explodeArcFrameTime;
	m_MaxFrameNum = explodeArcMaxFrameNum;
	return;
}

