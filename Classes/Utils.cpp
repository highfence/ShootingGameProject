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

FLOAT GetTanDegree(
	const _In_ FLOAT x,
	const _In_ FLOAT y
)
{
	FLOAT radian = atan2f(y, x);
	FLOAT degree = radian * 180.f / (FLOAT)M_PI;
	return degree;
}

void DebugLogPrint(
	const _In_ vRESULT retval,
	const _In_ std::wstring message,
	const _In_ LPCTSTR callClass
)
{
#ifdef _DEBUG
	if (retval != WELL_PERFORMED)
	{
		std::wstring guideWord = message + std::to_wstring(retval) + _T("\n") + callClass + _T("\n");
		OutputDebugString(guideWord.c_str());
	}
#endif
	return;
}

const vRESULT RotateVec(
	const _In_ FLOAT theta,
	const _In_ FLOAT refVecX,
	const _In_ FLOAT refVecY,
	_Out_ FLOAT& rotateVecX,
	_Out_ FLOAT& rotateVecY)
{
	FLOAT radian = M_PI / 180 * theta;
	FLOAT cosVal = cos(radian);
	FLOAT sinVal = sin(radian);

	rotateVecX = refVecX * cosVal - refVecY * sinVal;
	rotateVecY = refVecX * sinVal + refVecY * cosVal;

	return WELL_PERFORMED;
}

INT GetPoweredValue(const _In_ INT originValue, const _In_ INT multiplier)
{
	INT retval = 1;
	for (INT i = 0; i < multiplier; ++i)
	{
		retval *= originValue;
	}

	return retval;
}

BOOL IsObjectColided(
	const _In_ Vec pos1,
	const _In_ Vec range1,
	const _In_ Vec pos2,
	const _In_ Vec range2
)
{
	Vec obj1RightTop, obj1LeftBottom;
	obj1RightTop.x = pos1.x - range1.x / 2;
	obj1RightTop.y = pos1.y - range1.y / 2;
	obj1LeftBottom.x = pos1.x + range1.x / 2;
	obj1LeftBottom.y = pos1.y + range1.y / 2;

	Vec obj2RightTop, obj2LeftBottom;
	obj2RightTop.x = pos2.x - range2.x / 2;
	obj2RightTop.y = pos2.y - range2.y / 2;
	obj2LeftBottom.x = pos2.x + range2.x / 2;
	obj2LeftBottom.y = pos2.y + range2.y / 2;

	if (!(obj2LeftBottom.x < obj1RightTop.x
		|| obj1LeftBottom.x < obj2RightTop.x 
		|| obj2LeftBottom.y < obj1RightTop.y
		|| obj1LeftBottom.y < obj2RightTop.y))
	{
		return TRUE;
	}

	return FALSE;
}