#include "stdafx.h"
#include "Option.h"

const FLOAT optionSpriteWidth = 15.f;
const FLOAT optionSpriteHeight = 15.f;
const FLOAT optionWidthRangeThershold = 15.f;
const FLOAT optionHeightRangeThershold = 10.f;
const FLOAT optionThersholdCorrectionValue = 5.f;
const std::wstring optionSpritePath = _T("../Resources/Player/Opt");
const std::wstring optionShadePath = _T("../Resources/Player/OptS");
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
	if (m_pNextOption != nullptr)
	{
		/* 내 뒤의 Option이 먼저 그려짐 */
		m_pNextOption->DrawProc(drawDC);
	}
	
	if (m_IsOptionActivated == FALSE)
	{
		return;
	}

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
	Activate 되어 있지 않은 지점까지 내려가 마지막 한 Option을 Activate해주는 함수.
*/
void Option::Activate(const _In_ Vec previousPos)
{
	if (m_pNextOption == nullptr)
	{
		// Error or Last Option
		return;
	}

	// 다음 옵션이 Activate 되어 있다면,
	if (m_pNextOption->GetIsOptionActivated())
	{
		// 한 번 더 내려간다.
		m_pNextOption->Activate(m_Pos);
	}
	// Deactive 상태라면,	
	else
	{
		// NextOption 세팅
		m_pNextOption->SettingForActivate(m_Pos);
	}

	return;
}

/*
	Deactivate가 되는 상태는 플레이어가 죽는 상태 밖에 없으므로, 끝까지 내려가 모두를 Deactivate한다.
*/
void Option::Deactivate()
{
	// Activate 된 Option 모두 deactivate.
	if (m_pNextOption->GetIsOptionActivated())
	{
		m_pNextOption->Deactivate();
		return;
	}

	// 변수 초기화.
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

	if (xGap > optionWidthRangeThershold + optionThersholdCorrectionValue)
	{
		m_Pos.x = previousPos.x - optionWidthRangeThershold;
	}
	else if (xGap < -(optionWidthRangeThershold + optionThersholdCorrectionValue))
	{
		m_Pos.x = previousPos.x + optionWidthRangeThershold;
	}

	if (yGap > optionHeightRangeThershold + optionThersholdCorrectionValue)
	{
		m_Pos.y = previousPos.y - optionWidthRangeThershold;
	}
	else if (yGap < -(optionHeightRangeThershold + optionThersholdCorrectionValue))
	{
		m_Pos.y = previousPos.y + optionWidthRangeThershold;
	}

	if (m_pNextOption != nullptr)
	{
		m_pNextOption->Move(m_Pos);
	}

	return;
}