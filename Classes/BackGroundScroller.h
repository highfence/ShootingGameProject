#pragma once

/*
	ImgStruct
	��׶��� ��ũ�ѷ����� ����ϱ� ���� ������ �̹��� ����ü.
	�̹����� ��� �ִ� CImage�� ���ҽ��� ũ�⸦ ��´�. (imgWidth, imgHeight)
	scrollY�� Y������ ��ŭ ��ũ�� �Ǿ������� ����Ѵ�.
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
	���ȭ���� �ε��Ͽ� ��ũ�����ִ� Ŭ����.
	������ Scroll�� ���Ͽ� DrawProc���� ����Ѵ�.

	TODO :: Optional�ϰ� �ٸ� ������� �ٲ� �� �ִ� ��� ����.
	TODO :: �����ϰ� ��濡 ������Ʈ �߰��ϴ� ��� ����.
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