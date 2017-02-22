#pragma once
#include <Windows.h>

/*
	Vec2
	Cocos2d-x에서 유용하게 썼었던 Vec2 자료구조형을 Win API에서 사용하기 위해 정의한 자료구조.
	주로 좌표 값을 나타내는 데에 사용함.
*/

typedef struct Vec2
{
	FLOAT x;
	FLOAT y;
};

void SetVec2(_Inout_ Vec2* vec2, const _In_ FLOAT x, const _In_ FLOAT y)
{
	vec2->x = x;
	vec2->y = y;
	return;
}