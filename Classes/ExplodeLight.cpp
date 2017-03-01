#include "stdafx.h"
#include "ExplodeLight.h"

ExplodeLight::ExplodeLight(const _In_ FLOAT x, const _In_ FLOAT y)
	: Effect(x, y)
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
	m_pSprite->Load(L"../Resources/FX/explosion_2_07.png");
	m_pShade->Load(L"../Resources/FX/explosionS_2_07.png");
	//m_SpriteStr = explodeLightSpritePathStr;
	//m_ShadeStr = explodeLightShadePathStr;
	//ImgLoad(explodeLightSpritePathStr, explodeLightShadePathStr, 1);
	return;
}