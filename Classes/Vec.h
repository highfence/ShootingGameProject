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
	Vec& operator = (const _In_ Vec &vecForCopy);
	Vec& operator = (const _In_ INT intForCopy);
	Vec& operator + (const _In_ Vec &vecForPlus);
	Vec& operator + (const _In_ INT intForPlus);
	Vec& operator - (const _In_ Vec &vecForMinus);
	Vec& operator - (const _In_ INT intForMinu);
	Vec& operator * (const _In_ Vec &vecForMulti);
	Vec& operator * (const _In_ INT intForMulti);
	Vec& operator / (const _In_ Vec &vecForDivide);
	Vec& operator / (const _In_ INT intForDivide);

	FLOAT _x;
	FLOAT _y;
};