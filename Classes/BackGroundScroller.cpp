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

	// �귯�� �ð� ó��.
	AccTime(dt);

	// ���ȭ�� ��ũ��.
	ScrollBackGround(drawDC, dt);
	// ������Ʈ ��ũ��.
	//ScrollObj(drawDC, dt);
	
	return;
}

void BackGroundScroller::ScrollBackGround(_Inout_ HDC drawDC, const _In_ FLOAT dt)
{
	for (auto& i : m_ImgVec)
	{
		i->scrollY += dt * scrollSpeed;

		// �̹��� ��ġ�� ȭ�� ������ ���� ��� �� ȭ�� ��ŭ �������� ó��.
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
	�ð� ���� �Լ�.
*/
void BackGroundScroller::AccTime(const FLOAT dt)
{
	m_AccTime += dt;
	m_RecordTime += dt;
	return;
}

/*
	��濡 ������ ��� ������Ʈ�� ��Ͻ�Ű�� �Լ�.
*/
void BackGroundScroller::MakeRandomBackgroundObject()
{
	// ���͹� Ÿ�Ӹ��� ���� �õ�.
	if (m_RecordTime >= objGenerateIntervalTime)
	{
		// ���� ����.
		std::uniform_real_distribution<float> distForMake(0.f, 1.f);
		float chanceToMakeObj = distForMake(m_RandomGenerator);

		// ���� ����Ȯ���ȿ� ����ٸ� ���� ����.
		if (chanceToMakeObj < objGenerateChance)
		{
			// � ������Ʈ�� ������ ����. ������ 0 ���� OBJ_NUM - 1����.
			std::uniform_int_distribution<int> distForChoose(0, OBJ_NUM - 1);
			int objGenerateNum = distForChoose(m_RandomGenerator);
			m_ObjectVec.at(objGenerateNum)->isImgActivated = TRUE;

			// ��ġ ����.
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