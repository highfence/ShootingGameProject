#pragma once

// 윈도우 사이즈
const INT winWidth = 900;
const INT winHeight = 1600;

// 배경 이미지 사이즈. (윈도우 사이즈와 같음)
const INT imgWidth = 900;
const INT imgHeight = 1600;

// 키 입력 관련
const INT keyboardNumber = 256;

// 플레이어 관련
const FLOAT playerMoveSpeed = 300;


namespace ENEMY
{
	enum FLIGHT_TYPE
	{
		FLY_STRAIGHT, FLIGHT_TYPE_NUM
	};
}