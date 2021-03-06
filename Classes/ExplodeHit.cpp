#include "stdafx.h"
#include "ExplodeHit.h"

const INT explodeHitWidth = 12;
const INT explodeHitHeight = 22;
const FLOAT explodeHitFrameTime = 0.05;
const INT explodeHitMaxFrameNum = 6;
const std::wstring explodeHitSpritePath = _T("../Resources/FX/explosionHit_");
const std::wstring explodeHitShadePath = _T("../Resources/FX/explosionHitS_");
const std::wstring explodeHitExtension = _T(".png");

ExplodeHit::ExplodeHit(const _In_ Vec createPos)
	: Effect(createPos)
{
	init();
}

ExplodeHit::ExplodeHit(
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
	: Effect(createPos, floatSpeed, floatVec)
{
	init();;
}

void ExplodeHit::init()
{
	LoadInitialImg();
	InitialDataSubstitude();
	return;
}

ExplodeHit::~ExplodeHit()
{

}


void ExplodeHit::LoadInitialImg()
{
	m_SpriteStr = explodeHitSpritePath;
	m_ShadeStr = explodeHitShadePath;
	m_FileExtensionStr = explodeHitExtension;
	ImgLoad(explodeHitSpritePath, explodeHitShadePath, explodeHitExtension, 1);
	return;
}

void ExplodeHit::InitialDataSubstitude()
{
	m_Width = explodeHitWidth;
	m_Height = explodeHitHeight;
	m_TimePerFrame = explodeHitFrameTime;
	m_MaxFrameNum = explodeHitMaxFrameNum;
}
