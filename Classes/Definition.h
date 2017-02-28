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

	const INT explodeLightMaxFrameNum = 9;
	const std::wstring explodeLightSpritePathStr = _T("../Resources/FX/explosion_2_0");
	const std::wstring explodeLightShadePathStr = _T("../Resources/FX/explosionS_2_0");
	const INT explodeLightWidth = 52;
	const INT explodeLightHeight = 51;
	const FLOAT explodeLightFrameTime = 0.1f;

	const std::wstring SpriteExtension = _T(".png");
}