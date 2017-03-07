#include "stdafx.h"
#include "Vec.h"


Vec::Vec(const _In_ FLOAT vecX, const _In_ FLOAT vecY)
{
	m_X = vecX;
	m_Y = vecY;
}

Vec::Vec()
{
	m_X = 0.f;
	m_Y = 0.f;
}

Vec::~Vec()
{

}

Vec& Vec::operator=(const _In_ Vec &vecForCopy)
{
	m_X = vecForCopy.m_X;
	m_Y = vecForCopy.m_Y;
	return *this;
}

Vec& Vec::operator=(const _In_ INT intForCopy)
{
	m_X = intForCopy;
	m_Y = intForCopy;
	return *this;
}

Vec& Vec::operator+(const _In_ Vec &vecForPlus)
{
	m_X += vecForPlus.m_X;
	m_Y += vecForPlus.m_Y;
	return *this;
}

Vec& Vec::operator+(const _In_ INT intForPlus)
{
	m_X += intForPlus;
	m_Y += intForPlus;
	return *this;
}

Vec& Vec::operator-(const _In_ Vec &vecForMinus)
{
	m_X -= vecForMinus.m_X;
	m_Y -= vecForMinus.m_Y;
	return *this;
}

Vec& Vec::operator-(const _In_ INT intForMinus)
{
	m_X -= intForMinus;
	m_Y -= intForMinus;
	return *this;
}

Vec& Vec::operator*(const _In_ Vec &vecForMulti)
{
	m_X *= vecForMulti.m_X;
	m_Y *= vecForMulti.m_Y;
	return *this;
}

Vec& Vec::operator*(const _In_ INT intForMulti)
{
	m_X *= intForMulti;
	m_Y *= intForMulti;
	return *this;
}

Vec& Vec::operator/(const _In_ Vec &vecForDivide)
{
	// 나누는 벡터의 한 좌표라도 0일 경우 그냥 리턴.
	if (!vecForDivide.m_X && !vecForDivide.m_Y)
	{
		m_X /= vecForDivide.m_X;
		m_Y /= vecForDivide.m_Y;
	}
	return *this;
}

Vec & Vec::operator/(const INT intForDivide)
{
	// 나누는 인자가 0일 경우 그냥 리턴.
	if (!intForDivide)
	{
		m_X /= intForDivide;
		m_Y /= intForDivide;
	}
	return *this;
}

