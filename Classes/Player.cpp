#include "stdafx.h"
#include "Player.h"
#include "PlayerMissile.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "SoundManager.h"

const FLOAT playerInitWidth = winWidth / 2;
const FLOAT playerInitHeight = winHeight * 3 / 4;

const std::wstring playerFilePath = _T("../Resources/player_");
const std::wstring playerShadePath = _T("../Resources/playerS_");
const std::wstring playerFileExtension = _T(".png");

const INT playerSpriteWidth = 64;
const INT playerSpriteHeight = 64;
const INT displayBoundaryPixel = 5;
const INT playerMissileNumber = 15;
const FLOAT playerMissileLoadSpeed = 0.05f;
const FLOAT playerColisionPixel = 15;
const INT playerMaxPowerTier = 4;


Player::Player()
	: 
	m_AccTime(0.f),
	m_Direction(0),
	m_PowerTier(1),
	m_IsPlayerAlive(TRUE),
	m_CollisionPixel(playerColisionPixel)
{
	m_Pos = Vec(playerInitWidth, playerInitHeight);
	m_pSprite = new CImage;
	m_pShadeSprite = new CImage;
	m_pMissile = new PlayerMissile;
	init();
}

void Player::init()
{
	m_Pos.x = playerInitWidth;
	m_Pos.y = playerInitHeight;
	m_Width = playerSpriteWidth;
	m_Height = playerSpriteHeight;

	InitialImgLoad();
	MissileLoad();
	return;
}

Player::~Player()
{
	DeleteMissile();
	delete m_pSprite;
}

INT Player::InitialImgLoad()
{
	ImgLoad(m_pSprite, playerFilePath, 3, playerFileExtension, FALSE);
	ImgLoad(m_pShadeSprite, playerShadePath, 3, playerFileExtension, FALSE);
	return WELL_PERFORMED;
}

void Player::Draw(_Inout_ HDC drawDC)
{
	// 비행기 기울기에 맞게 
	LoadImgWithDirection();
	
#pragma warning(push)
#pragma warning(disable : 4244)	

	// 비행기 출력
	m_pShadeSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCPAINT);

	MissileDraw(drawDC);

#pragma warning(pop)

#ifdef _DEBUG
	PrintDebugLabel(drawDC);
#endif
	return;
}

void Player::Move(const _In_ BYTE* KeyState, const _In_ FLOAT dt)
{
	if (KeyState[VK_LEFT] & HOLDKEY)
	{
		if (m_Pos.x > displayBoundaryPixel + m_Width / 2)
		{
			m_Pos.x -= playerMoveSpeed * dt;
		}
		CalDirection(VK_LEFT);
	}
	else if (KeyState[VK_RIGHT] & HOLDKEY)
	{
		if (m_Pos.x < winWidth - displayBoundaryPixel - m_Width / 2)
		{
			m_Pos.x += playerMoveSpeed * dt;
		}
		CalDirection(VK_RIGHT);
	}
	else
	{
		CalDirection(0);
	}
	if (KeyState[VK_UP] & HOLDKEY)
	{
		if (m_Pos.y > displayBoundaryPixel + m_Height / 2)
		{
			m_Pos.y -= playerMoveSpeed * dt;
		}
	}
	if (KeyState[VK_DOWN] & HOLDKEY)
	{
		if (m_Pos.y < winHeight - displayBoundaryPixel - m_Height / 2)
		{
			m_Pos.y += playerMoveSpeed * dt;
		}
	}
	if (KeyState[VK_A] & HOLDKEY)
	{
		LaunchMissile(dt);
	}

	return;
}

void Player::MissileFly(const _In_ FLOAT dt)
{
	for (auto i : m_MissileVec)
	{
		i->Fly(dt, 0, -1, PLAYER::playerMissileSpeed);
	}
	return;
}

void Player::MissileLoad()
{
	for (int i = 0; i < playerMissileNumber; ++i)
	{
		PlayerMissile* loadingMissile = new PlayerMissile;
		m_MissileVec.push_back(loadingMissile);
	}

	return;
}

void Player::MissileDraw(_Inout_ HDC drawDC)
{
	for (auto i : m_MissileVec)
	{
		i->Draw(drawDC);
	}

	return;
}

void Player::LaunchMissile(const _In_ FLOAT dt)
{
	if (m_AccTime > playerMissileLoadSpeed)
	{
		for (auto i : m_MissileVec)
		{
			if (i->Missile::Launch(m_Pos))
			{
				m_AccTime = 0;
				break;
			}
		}
	}

	return;
}

INT Player::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	m_RecordAccTime += dt;
	return WELL_PERFORMED;
}

void Player::DeleteMissile()
{
	while (!m_MissileVec.empty())
	{
		m_MissileVec.pop_back();
	}

	return;
}

void Player::CalProc(const _In_ BYTE* keyByte, const _In_ FLOAT dt)
{
	AccTime(dt);
	Move(keyByte, dt);
	MissileFly(dt);
	CheckMissileColide();

	// EnemyManager에게 자신의 위치 정보 전달.
	EnemyManager::getInstance()->SetPlayerInfo(this);

	return;
}

void Player::DrawProc(_Inout_ HDC drawDC)
{
	Draw(drawDC);
	return;
}

/*
	플레이어의 포지션을 반환해주는 함수.
*/
const vRESULT Player::GetPosition(_Out_ Vec* vec) 
{
	if (vec == nullptr)
	{
		return vRESULT::ERROR_INVALID_INPUT;
	}

	vec->x = m_Pos.x;
	vec->y = m_Pos.y;

	return WELL_PERFORMED;
}

/*
	플레이어의 충돌 반경을 반환해주는 함수.
*/
FLOAT Player::GetCollisionPixel() const
{
	return m_CollisionPixel;
}

/*
	플레이어가 살아있는지 여부를 반환해주는 함수.
*/
BOOL Player::GetIsPlayerAlived() const
{
	return m_IsPlayerAlive;
}

void Player::CheckMissileColide()
{
	for (auto i : m_MissileVec)
	{
		if (i->GetMissileLaunched())
		{
			i->CheckColide();
		}
	}

	return;
}

/*
	현재 방향이 어디를 향하고 있는지 계산해서 그에 맞는 이미지를 로드해주는 함수.
*/
void Player::LoadImgWithDirection()
{
	if (m_Direction <= 10 && m_Direction > 6)
	{
		ImgLoad(m_pSprite, playerFilePath, 5, playerFileExtension, TRUE);
		ImgLoad(m_pShadeSprite, playerShadePath, 5, playerFileExtension, TRUE);
	}
	else if (m_Direction <= 6 && m_Direction > 3)
	{
		ImgLoad(m_pSprite, playerFilePath, 4, playerFileExtension, TRUE);
		ImgLoad(m_pShadeSprite, playerShadePath, 4, playerFileExtension, TRUE);
	}
	else if (m_Direction <= 3 && m_Direction >= -3)
	{
		ImgLoad(m_pSprite, playerFilePath, 3, playerFileExtension, TRUE);
		ImgLoad(m_pShadeSprite, playerShadePath, 3, playerFileExtension, TRUE);
	}
	else if (m_Direction < -3 && m_Direction >= -6)
	{
		ImgLoad(m_pSprite, playerFilePath, 2, playerFileExtension, TRUE);
		ImgLoad(m_pShadeSprite, playerShadePath, 2, playerFileExtension, TRUE);
	}
	else
	{
		ImgLoad(m_pSprite, playerFilePath, 1, playerFileExtension, TRUE);
		ImgLoad(m_pShadeSprite, playerShadePath, 1, playerFileExtension, TRUE);
	}

	return;
}

/*
	플레이어에게 총알이 맞았을 경우 호출하는 함수.
*/
void Player::PlayerDamaged()
{
	if (m_IsPlayerAlive)
	{
		vRESULT retval = MakeDyingExplosion();
		DebugLogPrint(retval, MESSAGES::explodeFailed, _T("from Player Damaged"));
	}
	m_IsPlayerAlive = FALSE;

	return;
}

/*
	플레이어가 아이템을 먹었을 경우 호출하는 함수.
*/
void Player::PlayerPowerUp()
{
	if (m_PowerTier <= playerMaxPowerTier)
	{
		++m_PowerTier;
		ChangeMissilesAccordWithPower();
	}

	return;
}

/*
	멤버 변수 m_PowerTier에 맞도록 미사일의 외향과 데미지를 바꾸어주는 함수. 
*/
void Player::ChangeMissilesAccordWithPower()
{
	for (auto i : m_MissileVec)
	{
		i->ChangeMissileTier(m_PowerTier);
	}

	return;
}

/*
	입력받은 키에 따라 m_Direction을 계산해주는 함수.
*/
INT Player::CalDirection(const _In_ INT pushedKey)
{
	const FLOAT directionRefreshTime = 0.1f;
	if (m_RecordAccTime > directionRefreshTime)
	{
		switch (pushedKey)
		{
		case VK_LEFT :
			if (m_Direction > 0)
			{
				m_Direction = 0;
			}
			if (m_Direction > -10)
			{
				--m_Direction;
			}
			break;
		case VK_RIGHT :
			if (m_Direction < 0)
			{
				m_Direction = 0;
			}
			if (m_Direction < 10)
			{
				++m_Direction;
			}
			break;
		default :
			if (m_Direction > 0)
			{
				--m_Direction;
			}
			else
			{
				++m_Direction;
			}
		}
		m_RecordAccTime = 0;
	}

	return WELL_PERFORMED;
}


/*
	Debug모드에서 라벨을 출력시키는 함수.
*/
INT Player::PrintDebugLabel(_Inout_ HDC drawDC)
{
	//SetTextAlign(drawDC, TA_CENTER);
	//std::wstring DebugLabel = std::to_wstring(m_Direction);
	//TextOut(drawDC, m_PosX, m_PosY, DebugLabel.c_str(), wcslen(DebugLabel.c_str()));
	return WELL_PERFORMED;
}

/*
	Make 8-ways Explosion when Player died.
*/
const vRESULT Player::MakeDyingExplosion()
{
	EffectManager* effectManager = EffectManager::getInstance();
	effectManager->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos, playerMoveSpeed, Vec(0.f, 1.f));
	effectManager->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos, playerMoveSpeed, Vec(0.f, -1.f));
	effectManager->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos, playerMoveSpeed, Vec(0.5f, 0.5f));
	effectManager->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos, playerMoveSpeed, Vec(0.5f, -0.5f));
	effectManager->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos, playerMoveSpeed, Vec(-0.5f, 0.5f));
	effectManager->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos, playerMoveSpeed, Vec(-0.5f, -0.5f));
	effectManager->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos, playerMoveSpeed, Vec(1.f, 0.f));
	effectManager->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos, playerMoveSpeed, Vec(-1.f, 0.f));

	return WELL_PERFORMED;
}