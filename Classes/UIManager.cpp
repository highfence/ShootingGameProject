#include "stdafx.h"
#include "UIManager.h"

const std::wstring numberSpritePath = _T("../Resources/UI/numeral");
const std::wstring numberShadePath = _T("../Resources/UI/numeralS");
const std::wstring numberFileExtension = _T(".png");
const INT numberSpriteWidth = 19;
const INT numberSpriteHeight = 19;


UIManager* UIManager::m_pInstance = nullptr;

// UIManager 싱글톤 구현.
UIManager* UIManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new UIManager();
	}
	return m_pInstance;
}

// 싱글톤 삭제 함수.
void UIManager::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

/*
	생성자. init호출.
*/
UIManager::UIManager()
	: m_AccTime(0.f), m_Score(0), m_IsScoreCalcNeeded(TRUE)
{
	Init();
}

/*
	소멸자.
*/
UIManager::~UIManager()
{
	DeleteInstance();
}

/*
	초기화 함수.
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
	계산 총괄 함수. GameManager CalProc에서 호출.
*/
void UIManager::CalProc(const _In_ FLOAT dt)
{
	return;
}

/*
	출력 총괄 함수. GameManager DrawProc에서 호출.
*/
void UIManager::DrawProc(const _Inout_ HDC drawDC)
{
	DrawScore(drawDC);
	return;
}

/*
	점수 추가 함수. 
*/
void UIManager::PlusScore(const _In_ INT addScore)
{
	m_Score += addScore;
	CalcScore();
	return;
}

/*
	점수 출력 함수.
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
	점수 계산 함수.
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