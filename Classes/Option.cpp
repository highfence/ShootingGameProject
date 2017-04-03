#include "stdafx.h"
#include "Option.h"
#include "OptionMissile.h"

const FLOAT optionSpriteWidth = 15.f;
const FLOAT optionSpriteHeight = 15.f;
const FLOAT optionWidthRangeThershold = 35.f;
const FLOAT optionHeightRangeThershold = 25.f;
const FLOAT optionThersholdCorrectionValue = 5.f;
const std::wstring optionSpritePath = _T("../Resources/Player/Opt");
const std::wstring optionShadePath = _T("../Resources/Player/OptS");
const std::wstring optionFileExtension = _T(".png");
const INT optionLoadMissileNumber = 30;

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
	m_RedMissileVec.reserve(optionLoadMissileNumber);
	m_BlueMissileVec.reserve(optionLoadMissileNumber);

	for (int i = 0; i < optionLoadMissileNumber; ++i)
	{
		OptionMissile* redMissile = new OptionMissile(PLAYER::OPTION_COLOR::RED);
		m_RedMissileVec.emplace_back(redMissile);

		OptionMissile* blueMissile = new OptionMissile(PLAYER::OPTION_COLOR::BLUE);
		m_BlueMissileVec.emplace_back(blueMissile);
	}

	return;
}

Option::~Option()
{
	m_RedMissileVec.clear();
	m_BlueMissileVec.clear();

	delete m_pSprite;
	m_pSprite = nullptr;
	delete m_pShadeSprite;
	m_pShadeSprite = nullptr;
}

void Option::CalcProc(const _In_ FLOAT deltaTime, const _In_ Vec previousPosition)
{
	if (m_pNextOption != nullptr)
	{
		m_pNextOption->CalcProc(deltaTime, m_Pos);
	}

	if (m_IsOptionActivated == FALSE)
	{
		return;
	}

	MissileFly(deltaTime);
	AccTime(deltaTime);
	MakeImageNextFrame();
	Move(previousPosition);

	return;
}

void Option::DrawProc(_Inout_ HDC drawDC)
{
#ifdef _DEBUG
#endif

	if (m_IsOptionActivated == FALSE)
	{
		return;
	}

	if (m_pNextOption != nullptr)
	{
		/* �� ���� Option�� ���� �׷��� */
		m_pNextOption->DrawProc(drawDC);
	}

#pragma warning(push)
#pragma warning(disable : 4244)	

	m_pShadeSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCPAINT);

#pragma warning(pop)

	/* �̻��� �׷��ֱ� */
	MissileDraw(drawDC);

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
	if (m_IsOptionActivated)
	{
		// �� �� �� ��������.
		m_pNextOption->Activate(m_Pos);
	}
	// Deactive ���¶��,	
	else
	{
		m_IsOptionActivated = TRUE;
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

void Option::Launch()
{
	if (!GetIsOptionActivated())
	{
		return;
	}

	if (m_pNextOption->GetIsOptionActivated())
	{
		m_pNextOption->Launch();
	}

	// LaunchPos ����.
	AdjustLaunchPos();
	
	// ���� �߻� ���� �´� �̻��� ã��.
	OptionMissile* missile;
	if (m_IsMissileRed)
	{
		missile = GetLaunchableMissile(PLAYER::OPTION_COLOR::RED);
		m_IsMissileRed = FALSE;
	}
	else
	{
		missile = GetLaunchableMissile(PLAYER::OPTION_COLOR::BLUE);
		m_IsMissileRed = TRUE;
	}

	// �߻� ������ �̻����� �ִٸ� �̻��� �߻�.
	if (missile != nullptr)
	{
		missile->Launch(m_Pos + m_LaunchPos);
	}

	return;
}

void Option::MissileFly(const FLOAT deltaTime)
{
	const INT OptionMissileSpeed = 2000;
	for (auto& i : m_RedMissileVec)
	{
		i->Fly(deltaTime, 0, -1, OptionMissileSpeed);
	}
	for (auto& i : m_BlueMissileVec)
	{
		i->Fly(deltaTime, 0, -1, OptionMissileSpeed);
	}

	return;
}

OptionMissile* Option::GetLaunchableMissile(const _In_ PLAYER::OPTION_COLOR color)
{
	if (color == PLAYER::OPTION_COLOR::RED)
	{
		for (auto& i : m_RedMissileVec)
		{
			if (!i->GetMissileLaunched())
			{
				return i;
			}
		}
	}
	else if (color == PLAYER::OPTION_COLOR::BLUE)
	{
		for (auto& i : m_BlueMissileVec)
		{
			if (!i->GetMissileLaunched())
			{
				return i;
			}
		}
	}

	return nullptr;
}

void Option::MissileDraw(HDC drawDC)
{
	for (auto& i : m_RedMissileVec)
	{
		i->Draw(drawDC);
	}
	for (auto& i : m_BlueMissileVec)
	{
		i->Draw(drawDC);
	}
	return;
}

void Option::MakeImageNextFrame()
{
	if (m_RecordRotateTime < m_TimePerFrame)
	{
		return;
	}
	m_RecordRotateTime = 0.f;

	++m_FrameNum;
	if (m_FrameNum == m_MaxFrameNum + 1)
	{
		m_FrameNum = 1;
	}
	
	ImgLoad(m_pSprite, optionSpritePath, m_FrameNum, optionFileExtension, TRUE);
	ImgLoad(m_pShadeSprite, optionShadePath, m_FrameNum, optionFileExtension, TRUE);

	return;
}

void Option::AccTime(const FLOAT deltaTime)
{
	m_AccTime += deltaTime;
	m_RecordFireTime += deltaTime;
	m_RecordRotateTime += deltaTime;

	return;
}

void Option::AdjustLaunchPos()
{
	if (m_LaunchPos.x == 0.f)
	{
		if (m_IsLaunchPosGoesToRight)
		{
			m_LaunchPos.x = 5.f;
			m_IsLaunchPosGoesToRight = FALSE;
		}
		else
		{
			m_LaunchPos.x = -5.f;
			m_IsLaunchPosGoesToRight = TRUE;
		}
	}
	else
	{
		m_LaunchPos.x = 0.f;
	}

	return;
}
