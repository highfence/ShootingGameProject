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

// 미사일 관련
const FLOAT colideCorrectionPixel = 15;

namespace ENEMY
{
	enum ENEMY_TYPE
	{
		ENEMY_ITEM, ITEM, ENEMY_TYPE_NUM
	};

	enum FLIGHT_TYPE
	{
		FLY_STRAIGHT, FLY_ITEM, FLIGHT_TYPE_NUM
	};

	enum MISSILE_TYPE
	{
		NONE, STRAIGHT_FIRE, MISSILE_TYPE_NUM
	};

	enum MISSILE_SIZE
	{
		SMALL, MEDIUM, MISSILE_SIZE_NUM
	};

	const std::wstring enemyMissileSmall = _T("../Resources/FX/proton_02.png");
	const std::wstring enemyMissileShadeSmall = _T("../Resources/FX/proton_02S.png");
	const INT enemyMissileSmallWidth = 9;
	const INT enemyMissileSmallHeigth = 10;
	const std::wstring enemyMissileMedium = _T("../Resources/FX/proton_01.png");
	const std::wstring enemyMissileShadeMedium = _T("../Resources/FX/proton_01S.png");
	const INT enemyMissileMediumWidth = 13;
	const INT enemyMissileMediumHeight = 13;

	// Enemy_Item
	const FLOAT enemyItemDamage = 3.f;
	const FLOAT enemyItemMissileSpeed = 700.f;
	const FLOAT enemyItemLoadedMissileNumber = 5.f;

	// Item
	const std::wstring itemSpritePath = _T("../Resources/PowerUp.png");
	const std::wstring itemShadePath = _T("../Resources/PowerUpS.png");
	const FLOAT itemWidth = 24;
	const FLOAT itemHeight = 19;
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
	const FLOAT explodeLightFrameTime = 0.05f;

	const std::wstring SpriteExtension = _T(".png");
}

namespace PLAYER
{
	const std::wstring playerMissile = _T("../Resources/MissileRed.png");
	const std::wstring playerShape = _T("../Resources/MissileRedShape.png");
	const FLOAT playerMissileSpeed = 2000.f;
	const FLOAT playerMissileWidth = 6.f;
	const FLOAT playerMissileHeight = 22.f;
	const INT playerMissileDamageOneTier = 50;
}