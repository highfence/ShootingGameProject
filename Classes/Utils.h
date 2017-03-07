#pragma once

/*
	2���� ���� ���� ǥ���ϱ� ���� ����ϴ� Ŭ����.
	FLOAT ���� _x, _y�� ������ �ִ�.
*/
class Vec
{
public :
	Vec(const _In_ FLOAT, const _In_ FLOAT);
	Vec();
	~Vec();
	Vec& operator = (const Vec &vecForCopy);

	FLOAT _x;
	FLOAT _y;
};

/*
	GetUnitVec
	1,2��° ���ڷ� x, y���� �־��ָ� 3,4���� ���ڷ� ���ֺ��͸� ��ȯ���ִ� �Լ�.
*/
void GetUnitVec(
	const _In_ FLOAT,
	const _In_ FLOAT,
	_Out_ FLOAT*,
	_Out_ FLOAT*);

/*
	ImgLoad
	filePath + FrameNumber + FileExtension�� ������ �̹����� �ε��ؾ��� ��� ����ϴ� �Լ�.

	���� :
		1. ImgLoad�ϰ� ���� CImage�� ������.
		2. �̹����� FilePath
		3. �̹��� FilePath �ڿ� ���� FrameNumber
		4. �̹��� ������ Ȯ����
		5. CImage�� �� �� ���� ���� �ִ���. (Destroy�� �ʿ�����)
*/
void ImgLoad(
	_Inout_ CImage*,
	const _In_ std::wstring,
	const _In_ INT,
	const _In_ std::wstring,
	const _In_ BOOL);

