#pragma once

/*
	ImgStruct
	백그라운드 스크롤러에서 사용하기 위해 정의한 이미지 구조체.
	이미지를 담고 있는 CImage와 리소스의 크기를 담는다. (imgWidth, imgHeight)
	scrollY는 Y축으로 얼만큼 스크롤 되었는지를 기록한다.
*/

typedef struct 
{
	CImage* img;
	FLOAT imgWidth;
	FLOAT imgHeight;
	FLOAT scrollY;
} ImgStruct;

/*
	BackGroundScroller
	배경화면을 로드하여 스크롤해주는 클래스.
	생성후 Scroll을 통하여 DrawProc에서 사용한다.

	TODO :: Optional하게 다른 배경으로 바꿀 수 있는 기능 구현.
	TODO :: 랜덤하게 배경에 오브젝트 추가하는 기능 구현.
*/

class BackGroundScroller
{
public :
	BackGroundScroller();
	~BackGroundScroller();

	void Scroll(_Inout_ HDC, const _In_ FLOAT);

private :

	void init();
	void ImgLoad();
	void ImgDelete();

	std::vector<ImgStruct*> m_ImgVec;
};