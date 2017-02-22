#pragma once
#include <Windows.h>

/*
	Vec2
	Cocos2d-x���� �����ϰ� ����� Vec2 �ڷᱸ������ Win API���� ����ϱ� ���� ������ �ڷᱸ��.
	�ַ� ��ǥ ���� ��Ÿ���� ���� �����.
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