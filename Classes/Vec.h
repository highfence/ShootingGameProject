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
	Vec& operator = (const _In_ FLOAT floatForCopy);
	Vec& operator + (const _In_ Vec &vecForPlus);
	Vec& operator + (const _In_ FLOAT floatForPlus);
	Vec& operator - (const _In_ Vec &vecForMinus);
	Vec& operator - (const _In_ FLOAT floatForMinu);
	Vec& operator * (const _In_ Vec &vecForMulti);
	Vec& operator * (const _In_ FLOAT floatForMulti);
	Vec& operator / (const _In_ Vec &vecForDivide);
	Vec& operator / (const _In_ FLOAT floatForDivide);
	Vec GetMinusVec() const;
	Vec GetYSymmetryVec() const;
	Vec GetXSymmetryVec() const;

	FLOAT x;
	FLOAT y;
};