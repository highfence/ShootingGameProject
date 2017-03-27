#include "stdafx.h"
#include "BackGroundScroller.h"

using namespace BACKGROUND;
const wchar_t* Background1 = _T("../Resources/BackGround1.png");
const INT scrollSpeed = 300;
const FLOAT objGenerateIntervalTime = 0.5f;
const FLOAT objGenerateChance = 0.2f;

BackGroundScroller::BackGroundScroller()
{
	Init();
}

void BackGroundScroller::Init()
{
	ImgLoad();
	ObjLoad();
}

BackGroundScroller::~BackGroundScroller()
{
	ImgDelete();
	ObjDelete();
}

void BackGroundScroller::ImgLoad()
{
	ImgStruct* img1 = new ImgStruct;
	img1->img = new CImage;
	img1->img->Load(Background1);
	img1->imgWidth = imgWidth;
	img1->imgHeight = imgHeight;
	img1->scrollX = 0;
	img1->scrollY = 0;
	img1->isImgActivated = TRUE;
	m_ImgVec.push_back(img1);

	return;
}

void BackGroundScroller::ObjLoad()
{
	for (int i = 0; i < OBJ_NUM; ++i)
	{
		ImgStruct* newImg = new ImgStruct;
		newImg->img = new CImage;
		std::wstring imgStr = objPathStr + objFileNameArray[i] + objFileExtensionStr;
		newImg->img->Load(imgStr.c_str());
		newImg->imgWidth = objWidthArray[i];
		newImg->imgHeight = objHeightArray[i];
		newImg->scrollX = 0;
		newImg->scrollY = 0;
		newImg->isImgActivated = FALSE;

		m_ObjectVec.push_back(newImg);
	}
}

void BackGroundScroller::Scroll(_Inout_ HDC drawDC, const _In_ FLOAT dt)
{
	MakeRandomBackgroundObject();

	// 흘러간 시간 처리.
	AccTime(dt);

	// 배경화면 스크롤.
	ScrollBackGround(drawDC, dt);
	// 오브젝트 스크롤.
	//ScrollObj(drawDC, dt);
	
	return;
}

void BackGroundScroller::ScrollBackGround(_Inout_ HDC drawDC, const _In_ FLOAT dt)
{
	for (auto& i : m_ImgVec)
	{
		i->scrollY += dt * scrollSpeed;

		// 이미지 위치가 화면 밖으로 나간 경우 한 화면 만큼 들어오도록 처리.
		if (i->scrollY >= imgHeight)
		{
			i->scrollY -= imgHeight;
		}
#pragma warning(push)
#pragma warning(disable : 4244)
		i->img->BitBlt(drawDC, 0, i->scrollY, imgWidth, imgHeight, 0, 0, SRCCOPY);
		i->img->BitBlt(drawDC, 0, i->scrollY - imgHeight, imgWidth, imgHeight, 0, 0, SRCCOPY);
#pragma warning(pop)
	}
}

void BackGroundScroller::ScrollObj(_Inout_ HDC drawDC, const _In_ FLOAT dt)
{
	for (auto& i : m_ObjectVec)
	{
		if (i->isImgActivated == TRUE)
		{
			i->scrollY += dt * scrollSpeed;

			if (i->scrollY >= imgHeight + i->imgWidth)
			{
				i->isImgActivated = FALSE;
			}
			else
			{
#pragma warning(push)
#pragma warning(disable : 4244)
				i->img->BitBlt(drawDC, i->scrollX, i->scrollY, i->imgWidth, i->imgHeight, 0, 0, BLACKNESS);
				i->img->BitBlt(drawDC, i->scrollX, i->scrollY, i->imgWidth, i->imgHeight, 0, 0, SRCAND);
#pragma warning(pop)
			}
		}
	}
}

/*
	시간 누적 함수.
*/
void BackGroundScroller::AccTime(const FLOAT dt)
{
	m_AccTime += dt;
	m_RecordTime += dt;
	return;
}

/*
	배경에 임의의 배경 오브젝트를 등록시키는 함수.
*/
void BackGroundScroller::MakeRandomBackgroundObject()
{
	// 인터벌 타임마다 생성 시도.
	if (m_RecordTime >= objGenerateIntervalTime)
	{
		// 난수 생성.
		std::uniform_real_distribution<float> distForMake(0.f, 1.f);
		float chanceToMakeObj = distForMake(m_RandomGenerator);

		// 만약 생성확률안에 들었다면 생성 시작.
		if (chanceToMakeObj < objGenerateChance)
		{
			// 어떤 오브젝트를 만들지 결정. 범위는 0 부터 OBJ_NUM - 1까지.
			std::uniform_int_distribution<int> distForChoose(0, OBJ_NUM - 1);
			int objGenerateNum = distForChoose(m_RandomGenerator);
			m_ObjectVec.at(objGenerateNum)->isImgActivated = TRUE;

			// 위치 결정.
			std::uniform_real_distribution<float> distForPosition(0.f, imgWidth);
			m_ObjectVec.at(objGenerateNum)->scrollX = distForPosition(m_RandomGenerator);
		}

		m_RecordTime = 0.f;
	}
}

void BackGroundScroller::ImgDelete()
{
	for (auto& i : m_ImgVec)
	{
		delete i->img;
		delete i;
	}
	return;
}

void BackGroundScroller::ObjDelete()
{
	for (auto& i : m_ObjectVec)
	{
		delete i->img;
		delete i;
	}
	return;
}