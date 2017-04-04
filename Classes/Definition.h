#pragma once
// 윈도우 사이즈
const INT winWidth = 900;
const INT winHeight = 1200;
const INT boundaryRange = 100;

// 벡터 초기화 값.
const Vec zero = Vec(0.f, 0.f);

namespace BACKGROUND
{
	// 배경 이미지 사이즈. (윈도우 사이즈와 같음)
	const INT imgWidth = 900;
	const INT imgHeight = 1600;

	enum BACKGROUND_OBJ  
	{
		BLACK_HOLE,
		METEOR_1, METEOR_2, METEOR_3, METEOR_4, METEOR_5,
		MOON, PLANET_1, PLANET_2, STAR_1, STAR_2,	
		OBJ_NUM
	};

	const INT objWidthArray[OBJ_NUM] = {97, 42, 22, 31, 26, 17, 45, 64, 63, 40, 27};
	const INT objHeightArray[OBJ_NUM] = {75, 39, 20, 36, 27, 15, 42, 68, 63, 37, 21};
	const std::wstring objPathStr = _T("../Resources/Background/");
	const std::wstring objFileExtensionStr = _T(".png");
	const std::wstring objFileNameArray[OBJ_NUM] = { _T("Black hole"), _T("Meteor1"), _T("Meteor2"), _T("Meteor3"), _T("Meteor4"), _T("Meteor5"), _T("Moon"), _T("Planet1"), _T("Planet2"), _T("Star"), _T("Star2")};
}

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
		ENEMY_ITEM,
		ITEM,
		ENEMY_ZACO,
		ENEMY_HAND_SHOT,
		ENEMY_MINE,
		ENEMY_BOSS,
		ENEMY_TYPE_NUM
	};

	enum FLIGHT_TYPE 
	{
		FLY_STRAIGHT,
		FLY_ITEM,
		FLY_ACCELERATE,
		FLY_GO_AND_SLOW,
		FLY_MOVE_ONLY_SIDE,
		FLIGHT_TYPE_NUM
	};

	enum MISSILE_TYPE 
	{
		NONE,
		STRAIGHT_FIRE,
		ACCELERATE_FIRE,
		CIRCLE_TYPE,
		MISSILE_TYPE_NUM
	};

	enum FIRE_TYPE 
	{
		NORMAL_FIRE,
		AIMED_FIRE,
		N_WAY_FIRE,
		MULTI_FIRE,
		CIRCLE_FIRE,
		FIRE_TYPE_NUM
	};

	enum MISSILE_SIZE
	{
		SMALL, MEDIUM, LARGE, EXTRA, MISSILE_SIZE_NUM
	};
	
	enum CREATE_OPTION
	{
		ENEMY_ITEM_TRUE,
		ENEMY_ITEM_FALSE,
		ITEM_CREATE,
		ENEMY_HAND_SHOT_CREATE,
		ENEMY_MINE_DIAGONAL,
		ENEMY_MINE_STRAIGHT,
		ENEMY_MINE_STRAIGHT_WITH_ITEM,
		ENEMY_BOSS_CREATE,
		CREATE_OPTION_NUM
	};
	
	enum FIRE_OPTION
	{
		NO_FIRE,
		FIRE_FRONT,
		FIRE_AIMED,
		MINE_AIMED,
		N_WAY_FIRE_OPTION,
		N_WAY_FIRE_TO_PLAYER,
		MULTI_FIRE_OPTION,
		ROTATE_FIRE_OPTION,
		FIRE_OPTION_NUM
	};

	/* Enemy Missile */
	const std::wstring enemyMissileSmall = _T("../Resources/FX/proton_02.png");
	const std::wstring enemyMissileShadeSmall = _T("../Resources/FX/proton_02S.png");
	const INT enemyMissileSmallWidth = 9;
	const INT enemyMissileSmallHeight = 10;
	const std::wstring enemyMissileMedium = _T("../Resources/FX/proton_01.png");
	const std::wstring enemyMissileShadeMedium = _T("../Resources/FX/proton_01S.png");
	const INT enemyMissileMediumWidth = 13;
	const INT enemyMissileMediumHeight = 13;
	const std::wstring enemyMissileLarge = _T("../Resources/FX/proton_00.png");
	const std::wstring enemyMissileShadeLarge = _T("../Resources/FX/proton_00S.png");
	const INT enemyMissileLargeWidth = 20;
	const INT enemyMissileLargeHeight = 20;
	const std::wstring enemyMissileExtra = _T("../Resources/Boss/Missile_Extra.png");
	const std::wstring enemyMissileShadeExtra = _T("../Resources/Boss/Missile_ExtraS.png");
	const INT enemyMissileExtraWidth = 47;
	const INT enemyMissileExtraHeight = 47;

	// Enemy_Item
	const FLOAT enemyItemDamage = 3.f;
	const FLOAT enemyItemMissileSpeed = 700.f;
	const INT enemyItemLoadedMissileNumber = 5;

	// Item
	const std::wstring itemSpritePath = _T("../Resources/PowerUp.png");
	const std::wstring itemShadePath = _T("../Resources/PowerUpS.png");
	const FLOAT itemWidth = 24;
	const FLOAT itemHeight = 19;

}


namespace EFFECT
{

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
	const std::wstring playerMissile = _T("../Resources/FX/PlayerMissileTier");
	const std::wstring playerMissileShape = _T("../Resources/FX/PlayerMissileTierS");
	const std::wstring fileExtension = _T(".png");
	const FLOAT playerMissileSpeed = 2000.f;
	const INT playerMissileWidthArray[4] = { 6, 18, 38, 70 };
	const INT playerMissileHeightArray[4] = { 22, 25, 28, 28 };
	const INT playerMissileDamageArray[4] = { 3, 7, 15, 21 };

	enum OPTION_COLOR
	{
		RED, BLUE, OPTION_COLOR_NUM
	};
}

enum vRESULT
{
	WELL_PERFORMED = 0,
	ERROR_INVALID_INPUT = -1,
	ERROR_IMG_LOAD_FAILED = -2
};

namespace MESSAGES
{
	const std::wstring creationFailed = _T("Creation Falied! \n ERROR CODE : ");
	const std::wstring explodeFailed = _T("Explode Falied! \n ERROR CODE : ");
	const std::wstring error = _T("ERROR!");
}

//namespace SOUND
//{
//	enum SOUND_TYPE
//	{
//		POWER_UP = IDR_WAVE1,
//		PLAYER_SHOT_1 = IDR_WAVE2,
//		SOUND_TYPE_NUM
//	};
//}