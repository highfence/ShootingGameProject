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

// �̻��� ����
const FLOAT colideCorrectionPixel = 15;

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

	const std::wstring enemyMissileSmall = _T("../Resources/FX/proton_02.png");
	const std::wstring enemyMissileShadeSmall = _T("../Resources/FX/proton_02S.png");
	const std::wstring enemyMissileMedium = _T("../Resources/FX/proton_01.png");
	const std::wstring enemyMissileShadeMedium = _T("../Resources/FX/proton_01S.png");
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

namespace PLAYER
{
	const std::wstring playerMissile = _T("../Resources/MissileRed.png");
	const std::wstring playerShape = _T("../Resources/MissileRedShape.png");
	const FLOAT playerMissileSpeed = 2000;
	const FLOAT playerMissileWidth = 6;
	const FLOAT playerMissileHeight = 22;
	const INT playerMissileDamageOneTier = 50;
}