#pragma once

using namespace EFFECT;

class Effect
{
public :
	Effect(const _In_ INT);
	~Effect();

private :
	// 인자 없이 생성 불가.
	Effect();

	void init();

	BOOL(Effect::*m_pEffectMakerHandler[EFFECT_TYPE_NUM])();

	BOOL MakeExplodeLight();
	INT m_EffectType;
	CImage* m_pSprite;
	CImage* m_pShade;
};