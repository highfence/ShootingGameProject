#pragma once
#include <atlimage.h>

typedef struct ImgStruct
{
	CImage* img;
	INT imgWidth;
	INT imgHeight;
	INT scrollY;
};

class BackGroundScroller
{
public :
	BackGroundScroller();
	~BackGroundScroller();

	void Scroll(_Inout_ HDC, const _In_ FLOAT);

private :

	void init();
	void ImgLoad();

	std::vector<ImgStruct*> m_ImgVec;
};