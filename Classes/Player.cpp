#include "stdafx.h"
#include "Player.h"

const FLOAT playerInitWidth = winWidth / 2;
const FLOAT playerInitHeight = winHeight * 3 / 4;
const wchar_t* playerSprite = _T("../Resources/Player1.png");
const INT spriteWidth = 64;
const INT spriteHeight = 64;


Player::Player()
	: m_PosX(0), m_PosY(0)
{
	m_pSprite = new CImage;
	init();
}

void Player::init()
{
	m_PosX = playerInitWidth;
	m_PosY = playerInitHeight;
	m_pSprite->Load(playerSprite);
	return;
}

Player::~Player()
{
	delete m_pSprite;
}

void Player::Draw(_Inout_ HDC DrawDC, const _In_ FLOAT dt)
{
	// 비행기 출력
	m_pSprite->BitBlt(DrawDC, m_PosX - spriteWidth / 2, m_PosY - spriteHeight / 2,
		spriteWidth, spriteHeight, 0, 0, SRCCOPY);

	return;
}

