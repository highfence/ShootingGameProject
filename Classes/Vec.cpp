#include "stdafx.h"
#include "Vec.h"


Vec::Vec(
	const _In_ FLOAT vecX,
	const _In_ FLOAT vecY)
{
	x = vecX;
	y = vecY;
}


Vec::Vec()
{
	x = 0.f;
	y = 0.f;
}

Vec::~Vec()
{

}

Vec& Vec::operator=(const _In_ Vec &vecForCopy)
{
	x = vecForCopy.x;
	y = vecForCopy.y;
	return *this;
}

Vec& Vec::operator=(const _In_ INT intForCopy)
{
	x = intForCopy;
	y = intForCopy;
	return *this;
}

Vec& Vec::operator+(const _In_ Vec &vecForPlus)
{
	x += vecForPlus.x;
	y += vecForPlus.y;
	return *this;
}

Vec& Vec::operator+(const _In_ INT intForPlus)
{
	x += intForPlus;
	y += intForPlus;
	return *this;
}

Vec& Vec::operator-(const _In_ Vec &vecForMinus)
{
	x -= vecForMinus.x;
	y -= vecForMinus.y;
	return *this;
}

Vec& Vec::operator-(const _In_ INT intForMinus)
{
	x -= intForMinus;
	y -= intForMinus;
	return *this;
}

Vec& Vec::operator*(const _In_ Vec &vecForMulti)
{
	x *= vecForMulti.x;
	y *= vecForMulti.y;
	return *this;
}

Vec& Vec::operator*(const _In_ INT intForMulti)
{
	x *= intForMulti;
	y *= intForMulti;
	return *this;
}

Vec& Vec::operator/(const _In_ Vec &vecForDivide)
{
	// 나누는 벡터의 한 좌표라도 0일 경우 그냥 리턴.
	if (!vecForDivide.x && !vecForDivide.y)
	{
		x /= vecForDivide.x;
		y /= vecForDivide.y;
	}
	return *this;
}

Vec & Vec::operator/(const INT intForDivide)
{
	// 나누는 인자가 0일 경우 그냥 리턴.
	if (!intForDivide)
	{
		x /= intForDivide;
		y /= intForDivide;
	}
	return *this;
}

Vec Vec::GetMinusVec() const
{
	return Vec(-x, -y);
}

Vec Vec::GetYSymmetryVec() const
{
	return Vec(x, -y);
}

Vec Vec::GetXSymmetryVec() const
{
	return Vec(-x, y);
}
