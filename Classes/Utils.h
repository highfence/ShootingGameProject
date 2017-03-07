#pragma once


/*
	1,2번째 인자로 x, y변을 넣어주면 3,4번쨰 인자로 유닛벡터를 반환해주는 함수.
*/
void GetUnitVec(
	const _In_ FLOAT,
	const _In_ FLOAT,
	_Out_ FLOAT*,
	_Out_ FLOAT*);

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
	const _In_ BOOL);

/*
	탄젠트를 이용하여 각도를 구해주는 함수.
*/
FLOAT GetTanDegree(
	const _In_ FLOAT x,
	const _In_ FLOAT y);

