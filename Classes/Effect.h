#pragma once

using namespace EFFECT;

class Effect
{
public :
	Effect(const _In_ INT);
	~Effect();

private :
	// ���� ���� ���� �Ұ�.
	Effect();

	void init();

	BOOL(Effect::*m_pEffectMakerHandler[EFFECT_TYPE_NUM])();

	BOOL MakeExplodeLight();
	INT m_EffectType;
	CImage* m_pSprite;
	CImage* m_pShade;
};