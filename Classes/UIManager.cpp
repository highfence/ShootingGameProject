#include "stdafx.h"
#include "UIManager.h"

const std::wstring numberSpritePath = _T("../Resources/UI/numeral");
const std::wstring numberShadePath = _T("../Resources/UI/numeralS");
const std::wstring numberFileExtension = _T(".png");
const INT numberSpriteWidth = 19;
const INT numberSpriteHeight = 19;


UIManager* UIManager::m_pInstance = nullptr;

// UIManager �̱��� ����.
UIManager* UIManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new UIManager();
	}
	return m_pInstance;
}

// �̱��� ���� �Լ�.
void UIManager::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

/*
	������. initȣ��.
*/
UIManager::UIManager()
	: m_AccTime(0.f), m_Score(0), m_IsScoreCalcNeeded(TRUE)
{
	Init();
}

/*
	�Ҹ���.
*/
UIManager::~UIManager()
{
	DeleteInstance();
}

/*
	�ʱ�ȭ �Լ�.
*/
void UIManager::Init()
{
	for (int i = 0; i < maxNumberPos; ++i)
	{
		m_ScoreSpriteArr[i] = new CImage;
		m_ScoreShadeArr[i] = new CImage;
		ImgLoad(m_ScoreSpriteArr[i], numberSpritePath, 0, numberFileExtension, FALSE);
		ImgLoad(m_ScoreShadeArr[i], numberShadePath, 0, numberFileExtension, FALSE);
	}

	return;
}

/*
	��� �Ѱ� �Լ�. GameManager CalProc���� ȣ��.
*/
void UIManager::CalProc(const _In_ FLOAT dt)
{
	return;
}

/*
	��� �Ѱ� �Լ�. GameManager DrawProc���� ȣ��.
*/
void UIManager::DrawProc(const _Inout_ HDC drawDC)
{
	DrawScore(drawDC);
	return;
}

/*
	���� �߰� �Լ�. 
*/
void UIManager::PlusScore(const _In_ INT addScore)
{
	m_Score += addScore;
	CalcScore();
	return;
}

/*
	���� ��� �Լ�.
*/
void UIManager::DrawScore(_Inout_ HDC drawDC)
{

#pragma warning(push)
#pragma warning(disable : 4244)
	const Vec scoreDrawPos = Vec(200.f, 50.f);

	for (int i = 0; i < maxNumberPos; ++i)
	{
		m_ScoreShadeArr[i]->BitBlt(drawDC, scoreDrawPos.x - (22 * i) - numberSpriteWidth / 2, scoreDrawPos.y - numberSpriteHeight / 2,
			numberSpriteWidth, numberSpriteHeight, 0, 0, SRCAND);
		m_ScoreSpriteArr[i]->BitBlt(drawDC, scoreDrawPos.x - (22 * i) - numberSpriteWidth / 2, scoreDrawPos.y - numberSpriteHeight / 2,
			numberSpriteWidth, numberSpriteHeight, 0, 0, SRCPAINT);
	}

#pragma warning(pop)

	return;
}

/*
	���� ��� �Լ�.
*/
void UIManager::CalcScore()
{
	
	INT remainScore = m_Score;
	for (INT i = maxNumberPos - 1; i > 0 ; --i)
	{
		INT divider = GetPoweredValue(10, i);
		INT quotient = remainScore / divider;

		ImgLoad(m_ScoreSpriteArr[i], numberSpritePath, quotient, numberFileExtension, TRUE);
		ImgLoad(m_ScoreShadeArr[i], numberShadePath, quotient, numberFileExtension, TRUE);

		remainScore -= (quotient * divider);
	}

	return;
}