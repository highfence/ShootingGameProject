#include "stdafx.h"
#include "ExplodeBig.h"

const std::wstring explodeBigSpritePath = _T("../Resources/FX/ExplodeBig_");
const std::wstring explodeBigShadePath = _T("../Resources/FX/ExplodeBigS_");
const std::wstring explodeBigFileExtension = _T(".png");
const INT explodeBigWidth = 96;
const INT explodeBigHeight = 96;
const INT explodeBigMaxFrame = 12;
const FLOAT explodeBigTimePerFrame = 0.1f;


ExplodeBig::ExplodeBig(const Vec createPos)
	: Effect(createPos)
{
	Init();
}

ExplodeBig::ExplodeBig(
	const Vec createPos,
	const FLOAT floatSpeed,
	const Vec floatVec)
	: Effect(createPos, floatSpeed, floatVec)
{
	Init();
}

void ExplodeBig::Init()
{
	InitialDataSubstitude();
	LoadInitialImg();
	return;
}

void ExplodeBig::InitialDataSubstitude()
{
	m_Width = explodeBigWidth;
	m_Height = explodeBigHeight;
	m_TimePerFrame = explodeBigTimePerFrame;
	m_MaxFrameNum = explodeBigMaxFrame;
}

void ExplodeBig::LoadInitialImg()
{
	m_SpriteStr = explodeBigSpritePath;
	m_ShadeStr = explodeBigShadePath;
	m_FileExtensionStr = explodeBigFileExtension;
	ImgLoad(explodeBigSpritePath, explodeBigShadePath, explodeBigFileExtension, 1);
	return;
}
