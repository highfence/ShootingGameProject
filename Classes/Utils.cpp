#include "stdafx.h"
#include "Utils.h"
#include <math.h>

void GetUnitVec(
	const _In_ FLOAT x,
	const _In_ FLOAT y,
	_Out_ FLOAT* unitX,
	_Out_ FLOAT* unitY)
{
	// 둘다 0일 경우.
	if (!x && !y)
	{
		*unitX = 0;
		*unitY = 0;
		return;
	}
	else if (x == 0)
	{
		*unitX = 0;
		if (y > 0)
		{
			*unitY = 1;
		}
		else if (y < 0)
		{
			*unitY = -1;
		}
		return;
	}
	else if (y == 0)
	{
		*unitY = 0;
		if (x > 0)
		{
			*unitX = 1;
		}
		else if (x < 0)
		{
			*unitX = -1;
		}
		return;
	}

	FLOAT length = fabs(sqrtf(x * x + y * y));
	*unitX = x / length;
	*unitY = y / length;

	return;
}

void ImgLoad(
	_Inout_ CImage* img,
	const _In_ std::wstring filePath,
	const _In_ INT frameNumber,
	const _In_ std::wstring fileExtension,
	const _In_ BOOL isDestroyNeeded
)
{
	if (isDestroyNeeded)
	{
		img->Destroy();
	}

	std::wstring frameNumberWstr = std::to_wstring(frameNumber);
	std::wstring completeFilePath = filePath + frameNumberWstr + fileExtension;
	img->Load(completeFilePath.c_str());

	return;
}


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

Vec& Vec::operator=(const Vec &vecForCopy)
{
	_x = vecForCopy._x;
	_y = vecForCopy._y;
	return *this;
}