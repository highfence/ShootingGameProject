#include "stdafx.h"
#include "Player.h"
#include "Missile.h"

const FLOAT playerInitWidth = winWidth / 2;
const FLOAT playerInitHeight = winHeight * 3 / 4;
const wchar_t* playerSprite = _T("../Resources/player_m2.png");
const wchar_t* shapeSprite = _T("../Resources/player_m_shape2.png");
const INT spriteWidth = 48;
const INT spriteHeight = 50;
const INT displayBoundaryPixel = 5;
const INT playerMissileNumber = 15;
const FLOAT missileLoadSpeed = 0.1f;


Player::Player()
	: m_PosX(0), m_PosY(0), m_AccTime(0)
{
	m_pSprite = new CImage;
	m_pShapeSprite = new CImage;
	m_pMissile = new Missile;
	init();
}

void Player::init()
{
	m_PosX = playerInitWidth;
	m_PosY = playerInitHeight;
	m_pSprite->Load(playerSprite);
	m_pShapeSprite->Load(shapeSprite);

	MissileLoad();
	return;
}

Player::~Player()
{
	DeleteMissile();
	delete m_pSprite;
}

void Player::Draw(_Inout_ HDC drawDC)
{
	// 비행기 출력
	m_pShapeSprite->BitBlt(drawDC, m_PosX - spriteWidth / 2, m_PosY - spriteHeight / 2,
		spriteWidth, spriteHeight, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_PosX - spriteWidth / 2, m_PosY - spriteHeight / 2,
		spriteWidth, spriteHeight, 0, 0, SRCPAINT);

	MissileDraw(drawDC);
	return;
}

void Player::Move(const _In_ BYTE* KeyState, const _In_ FLOAT dt)
{
	// TODO :: 기울어지는 애니메이션 이용하기.
	if (KeyState[VK_LEFT] & HOLDKEY)
	{
		if (m_PosX > displayBoundaryPixel + spriteWidth / 2)
		{
			m_PosX -= playerMoveSpeed * dt;
		}
	}
	if (KeyState[VK_RIGHT] & HOLDKEY)
	{
		if (m_PosX < winWidth - displayBoundaryPixel - spriteWidth / 2)
		{
			m_PosX += playerMoveSpeed * dt;
		}
	}
	if (KeyState[VK_UP] & HOLDKEY)
	{
		if (m_PosY > displayBoundaryPixel + spriteHeight / 2)
		{
			m_PosY -= playerMoveSpeed * dt;
		}
	}
	if (KeyState[VK_DOWN] & HOLDKEY)
	{
		if (m_PosY < winHeight - displayBoundaryPixel - spriteHeight / 2)
		{
			m_PosY += playerMoveSpeed * dt;
		}
	}
	if (KeyState[VK_A] & HOLDKEY)
	{
		LaunchMissile(dt);
	}
	if (KeyState[VK_D] & HOLDKEY)
	{
		DeleteMissile();
	}

	return;
}

void Player::MissileFly(const _In_ FLOAT dt)
{
	for (auto i : m_MissileVec)
	{
		i->Fly(dt);
	}
	return;
}

void Player::MissileLoad()
{
	for (int i = 0; i < playerMissileNumber; ++i)
	{
		Missile* loadingMissile = new Missile;
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
	m_AccTime += dt;
	if (m_AccTime > missileLoadSpeed)
	{
		for (auto i : m_MissileVec)
		{
			if (i->Launch(m_PosX, m_PosY))
			{
				m_AccTime = 0;
				break;
			}
		}
	}

	return;
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
	Move(keyByte, dt);
	MissileFly(dt);
	CheckMissileColide();
	return;
}

void Player::DrawProc(_Inout_ HDC drawDC)
{
	Draw(drawDC);
	return;
}

void Player::GetPosition(_Out_ INT* posX, _Out_ INT* posY)
{
	*posX = m_PosX;
	*posY = m_PosY;

	return;
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