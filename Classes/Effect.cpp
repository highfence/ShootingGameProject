#include "stdafx.h"
#include "Effect.h"

// TODO :: ���⼭ ���� ����
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