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


Player::Player()
	: m_PosX(0), m_PosY(0)
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
	return;
}

Player::~Player()
{
	delete m_pSprite;
}


void Player::Draw(_Inout_ HDC drawDC, const _In_ FLOAT dt)
{
	// 비행기 출력
	m_pShapeSprite->BitBlt(drawDC, m_PosX - spriteWidth / 2, m_PosY - spriteHeight / 2,
		spriteWidth, spriteHeight, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_PosX - spriteWidth / 2, m_PosY - spriteHeight / 2,
		spriteWidth, spriteHeight, 0, 0, SRCPAINT);

	m_pMissile->Draw(drawDC);

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
		m_pMissile->Launch(m_PosX, m_PosY);
	}

	return;
}

void Player::MissileFly(const _In_ FLOAT dt)
{
	m_pMissile->Fly(dt);
	return;
}