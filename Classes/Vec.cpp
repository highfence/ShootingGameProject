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

Vec& Vec::operator=(const _In_ FLOAT floatForCopy)
{
	x = floatForCopy;
	y = floatForCopy;
	return *this;
}

Vec& Vec::operator+(const _In_ Vec &vecForPlus)
{
	x += vecForPlus.x;
	y += vecForPlus.y;
	return *this;
}

Vec& Vec::operator+(const _In_ FLOAT floatForPlus)
{
	x += floatForPlus;
	y += floatForPlus;
	return *this;
}

Vec& Vec::operator-(const _In_ Vec &vecForMinus)
{
	x -= vecForMinus.x;
	y -= vecForMinus.y;
	return *this;
}

Vec& Vec::operator-(const _In_ FLOAT floatForMinus)
{
	x -= floatForMinus;
	y -= floatForMinus;
	return *this;
}

Vec& Vec::operator*(const _In_ Vec &vecForMulti)
{
	x *= vecForMulti.x;
	y *= vecForMulti.y;
	return *this;
}

Vec& Vec::operator*(const _In_ FLOAT floatForMulti)
{
	x *= floatForMulti;
	y *= floatForMulti;
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

Vec & Vec::operator/(const FLOAT floatForDivide)
{
	// 나누는 인자가 0일 경우 그냥 리턴.
	if (!floatForDivide)
	{
		x /= floatForDivide;
		y /= floatForDivide;
	}
	return *this;
}

BOOL Vec::operator==(const Vec compareVec)
{
	if (x != compareVec.x)
	{
		return FALSE;
	}
	else if (y != compareVec.y)
	{
		return FALSE;
	}
	return TRUE;
}

Vec Vec::GetMinusVec() const
{
	return Vec(-x, -y);
}

Vec Vec::GetYSymmetryVec() const
{
	return Vec(-x, y);
}

Vec Vec::GetXSymmetryVec() const
{
	return Vec(x, -y);
}
