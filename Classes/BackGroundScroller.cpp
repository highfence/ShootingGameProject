#include "stdafx.h"
#include "BackGroundScroller.h"

const wchar_t* Background1 = _T("../Resources/BackGround1.png");
const INT scrollSpeed = 100;

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

}

void BackGroundScroller::ImgLoad()
{
	// TODO :: CImage ���� ���� �غ���
	ImgStruct* img1 = new ImgStruct;
	img1->img->Load(Background1);
	img1->imgWidth = imgWidth;
	img1->imgHeight = imgHeight;
	img1->scrollY = 0;
	m_ImgVec.push_back(img1);

	return;
}

void BackGroundScroller::Scroll(_Inout_ HDC DrawDC, const _In_ FLOAT dt)
{
	// �귯�� �ð� ó��.
	for (auto i : m_ImgVec)
	{
		i->scrollY += dt * scrollSpeed;

		// �̹��� ��ġ�� ȭ�� ������ ���� ��� �� ȭ�� ��ŭ �������� ó��.
		if (i->scrollY >= imgHeight)
		{
			i->scrollY -= imgHeight;
		}

		i->img->BitBlt(DrawDC, 0, i->scrollY, imgWidth, imgHeight, 0, 0, SRCCOPY);
		i->img->BitBlt(DrawDC, 0, i->scrollY - imgHeight, imgWidth, imgHeight, 0, 0, SRCCOPY);
	}
	
	return;
}