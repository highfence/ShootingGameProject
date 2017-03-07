#include "stdafx.h"
#include "BackGroundScroller.h"

const wchar_t* Background1 = _T("../Resources/BackGround1.png");
const INT scrollSpeed = 300;

BackGroundScroller::BackGroundScroller()
{
	init();
}

void BackGroundScroller::init()
{
	ImgLoad();
}

BackGroundScroller::~BackGroundScroller()
{
	ImgDelete();
}

void BackGroundScroller::ImgLoad()
{
	ImgStruct* img1 = new ImgStruct;
	img1->img = new CImage;
	img1->img->Load(Background1);
	img1->imgWidth = imgWidth;
	img1->imgHeight = imgHeight;
	img1->scrollY = 0;
	m_ImgVec.push_back(img1);

	return;
}

void BackGroundScroller::Scroll(_Inout_ HDC DrawDC, const _In_ FLOAT dt)
{
	// 흘러간 시간 처리.
	for (auto i : m_ImgVec)
	{
		i->scrollY += dt * scrollSpeed;

		// 이미지 위치가 화면 밖으로 나간 경우 한 화면 만큼 들어오도록 처리.
		if (i->scrollY >= imgHeight)
		{
			i->scrollY -= imgHeight;
		}
#pragma warning(push)
#pragma warning(disable : 4244)
		i->img->BitBlt(DrawDC, 0, i->scrollY, imgWidth, imgHeight, 0, 0, SRCCOPY);
		i->img->BitBlt(DrawDC, 0, i->scrollY - imgHeight, imgWidth, imgHeight, 0, 0, SRCCOPY);
#pragma warning(pop)
	}
	
	return;
}

void BackGroundScroller::ImgDelete()
{
	for (auto i : m_ImgVec)
	{
		delete i->img;
		delete i;
	}

	return;
}