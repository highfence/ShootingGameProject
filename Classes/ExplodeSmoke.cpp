#include "stdafx.h"
#include "ExplodeSmoke.h"

const std::wstring explodeSmokeSpritePath = _T("../Resources/FX/ExplodeSmoke_0");
const std::wstring explodeSmokeShadePath = _T("../Resources/FX/ExplodeSmokeS_0");
const std::wstring explodeSmokeFileExtension = _T(".gif");
const INT explodeSmokeWidth = 82;
const INT explodeSmokeHeight = 72;
const FLOAT explodeSmokeFrameTime = 0.1f;
const INT explodeSmokeMaxFrameNum = 8;

ExplodeSmoke::ExplodeSmoke(const _In_ Vec createPos)
	: Effect(createPos)
{
	init();
}

ExplodeSmoke::ExplodeSmoke(
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
	: Effect(createPos, floatSpeed, floatVec)
{
	init();
}

void ExplodeSmoke::init()
{
	InitialDataSubstitude();
	LoadInitialImg();
	return;
}

ExplodeSmoke::~ExplodeSmoke()
{

}

void ExplodeSmoke::LoadInitialImg()
{
	m_SpriteStr = explodeSmokeSpritePath;
	m_ShadeStr = explodeSmokeShadePath;
	m_FileExtensionStr = explodeSmokeFileExtension;
	ImgLoad(explodeSmokeSpritePath, explodeSmokeShadePath, explodeSmokeFileExtension, 1);
	return;
}

void ExplodeSmoke::InitialDataSubstitude()
{
	m_Width = explodeSmokeWidth;
	m_Height = explodeSmokeHeight;
	m_TimePerFrame = explodeSmokeFrameTime;
	m_MaxFrameNum = explodeSmokeMaxFrameNum;
	return;
}