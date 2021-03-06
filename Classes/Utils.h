﻿#pragma once
#include "Vec.h"

/*
	1,2번째 인자로 x, y변을 넣어주면 3,4번쨰 인자로 유닛벡터를 반환해주는 함수.
*/
void GetUnitVec(
	const _In_ FLOAT,
	const _In_ FLOAT,
	_Out_ FLOAT*,
	_Out_ FLOAT*
);

/*
	filePath + FrameNumber + FileExtension의 형태의 이미지를 로드해야할 경우 사용하는 함수.

	인자 :
		1. ImgLoad하고 싶은 CImage의 포인터.
		2. 이미지의 FilePath
		3. 이미지 FilePath 뒤에 더할 FrameNumber
		4. 이미지 파일의 확장자
		5. CImage가 한 번 사용된 적이 있는지. (Destroy가 필요한지)
*/
void ImgLoad(
	_Inout_ CImage*,
	const _In_ std::wstring,
	const _In_ INT,
	const _In_ std::wstring,
	const _In_ BOOL
);

/*
	탄젠트를 이용하여 각도를 구해주는 함수.
*/
FLOAT GetTanDegree(
	const _In_ FLOAT x,
	const _In_ FLOAT y
);

/*
	디버그시 로그를 남겨주는 함수.
*/
void DebugLogPrint(
	const _In_ vRESULT,
	const _In_ std::wstring,
	const _In_ LPCTSTR
);

/*
	돌리려는 각도(Degree)와 기준 벡터를 넣어주면 회전벡터를 반환해주는 함수.
*/
const vRESULT RotateVec(
	const _In_ FLOAT theta,
	const _In_ FLOAT refVecX,
	const _In_ FLOAT refVecY,
	_Out_ FLOAT& rotateVecX,
	_Out_ FLOAT& rotateVecY
);

/*
	INT형 값의 계승을 구하는 함수.
*/
INT GetPoweredValue(
	const _In_ INT originValue,
	const _In_ INT multiplier
);

/*
	두 물체가 2차원에서 서로 충돌했는지 판별해주는 함수.
*/
BOOL IsObjectColided(
	const _In_ Vec pos1,
	const _In_ Vec range1,
	const _In_ Vec pos2,
	const _In_ Vec range2
);
