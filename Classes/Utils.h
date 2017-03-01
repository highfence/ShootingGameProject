#pragma once
#include <Windows.h>

// 1,2번째 인자로 x, y변을 넣어주면 3,4번쨰 인자로 유닛벡터를 반환해주는 함수.
void GetUnitVec(const _In_ FLOAT, const _In_ FLOAT, _Out_ FLOAT*, _Out_ FLOAT*);