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
	FLOAT scrollX;
	FLOAT scrollY;
	BOOL isImgActivated;
} ImgStruct;

/*
	BackGroundScroller
	���ȭ���� �ε��Ͽ� ��ũ�����ִ� Ŭ����.
	������ Scroll�� ���Ͽ� DrawProc���� ����Ѵ�.

	TODO :: Optional�ϰ� �ٸ� ������� �ٲ� �� �ִ� ��� ����.
*/

class BackGroundScroller
{
public :
	BackGroundScroller();
	~BackGroundScroller();

	void Scroll(_Inout_ HDC, const _In_ FLOAT);

private :

	void Init();
	void ImgLoad();
	void ObjLoad();
	void ImgDelete();
	void ObjDelete();
	void ScrollBackGround(_Inout_ HDC, const _In_ FLOAT);
	void ScrollObj(_Inout_ HDC, const _In_ FLOAT);
	void AccTime(const _In_ FLOAT);
	void MakeRandomBackgroundObject();

	std::vector<ImgStruct*> m_ImgVec;
	std::vector<ImgStruct*> m_ObjectVec;

	FLOAT m_AccTime = 0.f;
	FLOAT m_RecordTime = 0.f;
	std::mt19937 m_RandomGenerator;
};