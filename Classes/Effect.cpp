#include "stdafx.h"
#include "Effect.h"

// TODO :: 여기서 부터 시작
// const wchar_t* 

Effect::Effect(const _In_ INT effectType)
	: m_EffectType(effectType)
{
	init();
}

void Effect::init()
{
	m_pEffectMakerHandler[EXPLODE_LIGHT] = &Effect::MakeExplodeLight;
	return;
}

Effect::~Effect()
{

}

BOOL Effect::MakeExplodeLight()
{
	
	return TRUE;
}