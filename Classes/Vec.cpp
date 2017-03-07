#include "stdafx.h"
#include "Vec.h"


Vec::Vec(const _In_ FLOAT vecX, const _In_ FLOAT vecY)
{
	_x = vecX;
	_y = vecY;
}

Vec::Vec()
{
	_x = 0.f;
	_y = 0.f;
}

Vec::~Vec()
{

}

Vec& Vec::operator=(const _In_ Vec &vecForCopy)
{
	_x = vecForCopy._x;
	_y = vecForCopy._y;
	return *this;
}

Vec& Vec::operator=(const _In_ INT intForCopy)
{
	_x = intForCopy;
	_y = intForCopy;
	return *this;
}

Vec& Vec::operator+(const _In_ Vec &vecForPlus)
{
	_x += vecForPlus._x;
	_y += vecForPlus._y;
	return *this;
}

Vec& Vec::operator+(const _In_ INT intForPlus)
{
	_x += intForPlus;
	_y += intForPlus;
	return *this;
}

Vec& Vec::operator-(const _In_ Vec &vecForMinus)
{
	_x -= vecForMinus._x;
	_y -= vecForMinus._y;
	return *this;
}

Vec& Vec::operator-(const _In_ INT intForMinus)
{
	_x -= intForMinus;
	_y -= intForMinus;
	return *this;
}

Vec& Vec::operator*(const _In_ Vec &vecForMulti)
{
	_x *= vecForMulti._x;
	_y *= vecForMulti._y;
	return *this;
}

Vec& Vec::operator*(const _In_ INT intForMulti)
{
	_x *= intForMulti;
	_y *= intForMulti;
	return *this;
}

Vec& Vec::operator/(const _In_ Vec &vecForDivide)
{
	// 벡터의 한 좌표라도 0일 경우 그냥 리턴.
	if (!vecForDivide._x && !vecForDivide._y)
	{
		_x /= vecForDivide._x;
		_y /= vecForDivide._y;
	}
	return *this;
}

Vec & Vec::operator/(const INT intForDivide)
{
	// 나누는 인자가 0일 경우 그냥 리턴.
	if (!intForDivide)
	{
		_x /= intForDivide;
		_y /= intForDivide;
	}
	return *this;
}

