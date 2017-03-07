#pragma once


/*
	2차원 벡터 값을 표현하기 위해 사용하는 클래스.
	FLOAT 인자 _x, _y를 가지고 있다.
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