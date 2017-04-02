#include "stdafx.h"
#include "ExplodeLight.h"

const std::wstring explodeLightExtention = _T(".png");

ExplodeLight::ExplodeLight(const _In_ Vec createPos)
	: Effect(createPos)
{
	init();
}

ExplodeLight::ExplodeLight(
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
	: Effect(createPos, floatSpeed, floatVec)
{
	init();
}

void ExplodeLight::init()
{
	LoadInitialImg();
	InitialDataSubstitude();
	return;
}

ExplodeLight::~ExplodeLight()
{

}

void ExplodeLight::LoadInitialImg() 
{
	m_SpriteStr = explodeLightSpritePathStr;
	m_ShadeStr = explodeLightShadePathStr;
	m_FileExtensionStr = explodeLightExtention;
	ImgLoad(explodeLightSpritePathStr, explodeLightShadePathStr, explodeLightExtention,1);
	return;
}

void ExplodeLight::InitialDataSubstitude()
{
	m_Width = explodeLightWidth;
	m_Height = explodeLightHeight;
	m_TimePerFrame = explodeLightFrameTime;
	m_MaxFrameNum = explodeLightMaxFrameNum;
}
