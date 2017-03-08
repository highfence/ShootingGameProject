#include "stdafx.h"
#include "ExplodeLight.h"

ExplodeLight::ExplodeLight(const _In_ Vec createPos)
	: Effect(createPos)
{
	m_Width = explodeLightWidth;
	m_Height = explodeLightHeight;
	m_TimePerFrame = explodeLightFrameTime;
	m_MaxFrameNum = explodeLightMaxFrameNum;
	init();
}

ExplodeLight::ExplodeLight(
	const _In_ Vec createPos,
	const _In_ FLOAT floatSpeed,
	const _In_ Vec floatVec)
	: Effect(createPos, floatSpeed, floatVec)
{
	m_Width = explodeLightWidth;
	m_Height = explodeLightHeight;
	m_TimePerFrame = explodeLightFrameTime;
	m_MaxFrameNum = explodeLightMaxFrameNum;
	init();
}

void ExplodeLight::init()
{
	LoadInitialImg();
	return;
}

ExplodeLight::~ExplodeLight()
{

}

void ExplodeLight::LoadInitialImg() 
{
	m_SpriteStr = explodeLightSpritePathStr;
	m_ShadeStr = explodeLightShadePathStr;
	ImgLoad(explodeLightSpritePathStr, explodeLightShadePathStr, 1);
	return;
}