#pragma once

// ������ ������
const INT winWidth = 900;
const INT winHeight = 1600;

// ��� �̹��� ������. (������ ������� ����)
const INT imgWidth = 900;
const INT imgHeight = 1600;

// Ű �Է� ����
const INT keyboardNumber = 256;

// �÷��̾� ����
const FLOAT playerMoveSpeed = 300;


namespace ENEMY
{
	enum ENEMY_TYPE
	{
		ENEMY_ITEM, ENEMY_TYPE_NUM
	};

	enum FLIGHT_TYPE
	{
		FLY_STRAIGHT, FLIGHT_TYPE_NUM
	};
}

namespace EFFECT
{
	enum EFFECT_TYPE
	{
		EXPLODE_LIGHT, EFFECT_TYPE_NUM
	};
}