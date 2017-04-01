#include "stdafx.h"
#include "Option.h"

const FLOAT optionSpriteWidth = 15.f;
const FLOAT optionSpriteHeight = 15.f;
const FLOAT optionWidthRangeThershold = 50.f;
const FLOAT optionHeightRangeThershold = 30.f;
const std::wstring optionSpritePath = _T("../Resources/Opt");
const std::wstring optionShadePath = _T("../Resources/OptS");
const std::wstring optionFileExtension = _T(".png");
const INT loadMissileNumber = 20;

Option::Option()
{
	init();
}

void Option::init()
{
	m_pSprite = new CImage;
	m_pShadeSprite = new CImage;

	m_Width = optionSpriteWidth;
	m_Height = optionSpriteHeight;
	InitialImgLoad();
	MissileLoad();

	return;
}

void Option::InitialImgLoad()
{
	ImgLoad(m_pSprite, optionSpritePath, m_FrameNum, optionFileExtension, FALSE);
	ImgLoad(m_pShadeSprite, optionShadePath, m_FrameNum, optionFileExtension, FALSE);

	return;
}

void Option::MissileLoad()
{

	return;
}

Option::~Option()
{

}

void Option::CalcProc(const _In_ FLOAT deltaTime, const _In_ Vec previousPosition)
{
	if (m_IsOptionActivated == FALSE)
	{
		return;
	}

	Move(previousPosition);

	m_pNextOption->CalcProc(deltaTime, m_Pos);
	return;
}

void Option::DrawProc(_Inout_ HDC drawDC)
{
	if (m_IsOptionActivated == FALSE)
	{
		return;
	}

	/* �� ���� Option�� ���� �׷��� */
	m_pNextOption->DrawProc(drawDC);

#pragma warning(push)
#pragma warning(disable : 4244)	

	m_pShadeSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCPAINT);

#pragma warning(pop)

	return;
}

/*
	Activate �Ǿ� ���� ���� �������� ������ ������ �� Option�� Activate���ִ� �Լ�.
*/
void Option::Activate(const _In_ Vec previousPos)
{
	if (m_pNextOption == nullptr)
	{
		// Error or Last Option
		return;
	}

	// ���� �ɼ��� Activate �Ǿ� �ִٸ�,
	if (m_pNextOption->GetIsOptionActivated())
	{
		// �� �� �� ��������.
		m_pNextOption->Activate(m_Pos);
	}
	// Deactive ���¶��,	
	else
	{
		// NextOption ����
		m_pNextOption->SettingForActivate(m_Pos);
	}

	return;
}

/*
	Deactivate�� �Ǵ� ���´� �÷��̾ �״� ���� �ۿ� �����Ƿ�, ������ ������ ��θ� Deactivate�Ѵ�.
*/
void Option::Deactivate()
{
	// Activate �� Option ��� deactivate.
	if (m_pNextOption->GetIsOptionActivated())
	{
		m_pNextOption->Deactivate();
		return;
	}

	// ���� �ʱ�ȭ.
	m_Pos = Vec(0.f, 0.f);
	m_SavePreviousPos = Vec(0.f, 0.f);
	m_AccTime = 0.f;
	m_RecordFireTime = 0.f;
	m_FrameNum = 1;
	
	m_IsOptionActivated = FALSE;
	return;
}

void Option::SetNextOption(_In_ Option& nextOption)
{
	m_pNextOption = &nextOption;
	return;
}

BOOL Option::GetIsOptionActivated()
{
	return m_IsOptionActivated;
}

void Option::SettingForActivate(const Vec previousPos)
{
	m_Pos = previousPos;
	m_SavePreviousPos = previousPos;
	m_IsOptionActivated = TRUE;
	return;
}

void Option::Move(const _In_ Vec previousPos)
{
	FLOAT xGap = previousPos.x - m_Pos.x;
	FLOAT yGap = previousPos.y - m_Pos.y;

	if (xGap > optionWidthRangeThershold)
	{

	}
	else if (xGap < -optionWidthRangeThershold)
	{

	}

	if (yGap > optionHeightRangeThershold)
	{

	}
	else if (xGap < -optionHeightRangeThershold)
	{

	}

	return;
}