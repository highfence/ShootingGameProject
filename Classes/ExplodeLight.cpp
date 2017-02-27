#include "stdafx.h"
#include "ExplodeLight.h"

ExplodeLight::ExplodeLight(const _In_ FLOAT x, const _In_ FLOAT y)
	: Effect(x, y)
{
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
	ImgLoad(explodeLightSpritePathStr, explodeLightShadePathStr, 0);
	return;
}