#include "stdafx.h"
#include "Player.h"
#include "PlayerMissile.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "Option.h"

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
const INT playerOptionNumber = 3;

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
	InitialOptionSetting();
	MissileLoad();
	return;
}

Player::~Player()
{
	DeleteMissile();
	delete m_pSprite;
}

void Player::InitialImgLoad()
{
	ImgLoad(m_pSprite, playerFilePath, 3, playerFileExtension, FALSE);
	ImgLoad(m_pShadeSprite, playerShadePath, 3, playerFileExtension, FALSE);
	return;
}

void Player::InitialOptionSetting()
{
	// Option�� Ư����, ���� �ʴ� Option�� �ΰ� �ִ� ���� ���� ������, �� ���� �߰����ش�.
	m_OptionVec.reserve(playerOptionNumber + 1);
	Option* previousOption = nullptr;
	Option* curOption = nullptr;
	for (int i = 0; i <= playerOptionNumber; ++i)
	{
		curOption = new Option();
		m_OptionVec.emplace_back(curOption);

		if (previousOption != nullptr)
		{
			previousOption->SetNextOption(*curOption);
		}
		previousOption = curOption;
		curOption = nullptr;
	}

	return;
}


void Player::Draw(_Inout_ HDC drawDC)
{
	// ����� ���⿡ �°� 
	LoadImgWithDirection();
	
#pragma warning(push)
#pragma warning(disable : 4244)	

	// ����� ���
	m_pShadeSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCAND);
	m_pSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCPAINT);

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

void Player::OptionFly()
{
	m_OptionVec.front()->Move(m_Pos);

	return;
}

void Player::MissileLoad()
{
	m_MissileVec.reserve(playerMissileNumber);
	for (int i = 0; i < playerMissileNumber; ++i)
	{
		PlayerMissile* loadingMissile = new PlayerMissile;
		m_MissileVec.emplace_back(loadingMissile);
	}

	return;
}

void Player::MissileDraw(_Inout_ HDC drawDC)
{
	for (const auto& i : m_MissileVec)
	{
		i->Draw(drawDC);
	}

	return;
}

void Player::OptionDraw(_Inout_ HDC drawDC)
{
	m_OptionVec.front()->DrawProc(drawDC);

	return;
}

void Player::LaunchMissile(const _In_ FLOAT dt)
{
	if (m_AccTime > playerMissileLoadSpeed)
	{
		for (auto& i : m_MissileVec)
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

void Player::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	m_RecordAccTime += dt;
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
	AccTime(dt);
	Move(keyByte, dt);
	MissileFly(dt);
	OptionFly();
	CheckMissileColide();

	return;
}

void Player::DrawProc(_Inout_ HDC drawDC)
{
	/* Player �ڽ��� Draw */
	Draw(drawDC);

	/* �̻��ϵ� ��� */
	MissileDraw(drawDC);

	/* �ɼǵ� ��� */
	OptionDraw(drawDC);
	return;
}

/*
	�÷��̾��� �������� ��ȯ���ִ� �Լ�.
*/
const vRESULT Player::GetPosition(_Out_ Vec* vec) const 
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
	�÷��̾��� �浹 �ݰ��� ��ȯ���ִ� �Լ�.
*/
FLOAT Player::GetCollisionPixel() const
{
	return m_CollisionPixel;
}

/*
	�÷��̾ ����ִ��� ���θ� ��ȯ���ִ� �Լ�.
*/
BOOL Player::GetIsPlayerAlived() const
{
	return m_IsPlayerAlive;
}

/*
	�߻�� �̻����� ���⿡ �¾Ҵ��� Ȯ�����ִ� �Լ�.
*/
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
	���� ������ ��� ���ϰ� �ִ��� ����ؼ� �׿� �´� �̹����� �ε����ִ� �Լ�.
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
	�÷��̾�� �Ѿ��� �¾��� ��� ȣ���ϴ� �Լ�.
*/
void Player::PlayerDamaged(const _In_ Vec missileVec)
{
	if (m_IsPlayerAlive)
	{
		MakeDyingExplosion(missileVec);
	}
	m_IsPlayerAlive = FALSE;

	return;
}

/*
	�÷��̾ �������� �Ծ��� ��� ȣ���ϴ� �Լ�.
*/
void Player::PlayerPowerUp()
{
	if (m_PowerTier <= playerMaxPowerTier)
	{
		++m_PowerTier;
		ChangeMissilesAccordWithPower();
		ChangeOptionsAccordWithPower();
	}

	return;
}

/*
	��� ���� m_PowerTier�� �µ��� �̻����� ����� �������� �ٲپ��ִ� �Լ�. 
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
	��� ���� m_OptionTier�� �µ��� Option�� ������ �ٲپ��ִ� �Լ�.
*/
void Player::ChangeOptionsAccordWithPower()
{
	m_OptionVec.front()->Activate(m_Pos);
	return;
}

/*
	�Է¹��� Ű�� ���� m_Direction�� ������ִ� �Լ�.
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


#ifdef _DEBUG
/*
	Debug��忡�� ���� ��½�Ű�� �Լ�.
*/
INT Player::PrintDebugLabel(_Inout_ HDC drawDC)
{
	//SetTextAlign(drawDC, TA_CENTER);
	//std::wstring DebugLabel = std::to_wstring(m_Direction);
	//TextOut(drawDC, m_PosX, m_PosY, DebugLabel.c_str(), wcslen(DebugLabel.c_str()));
	return WELL_PERFORMED;
}
#endif

/*
	Make 8-ways Explosion when Player died.
*/
void Player::MakeDyingExplosion(const _In_ Vec missileVec)
{
	const float vecRange = 25.f;
	const float speedRange = 300.f;
	const int makeEffectNumber = 8;
	std::mt19937 rng((unsigned int)time(NULL));
	std::uniform_real_distribution<float> rangeDist(-0.20, 0.20);
	std::uniform_real_distribution<float> speedDist(-(speedRange / 2), speedRange);

	EffectManager* effectManager = EffectManager::GetInstance();
	for (int i = 0; i < makeEffectNumber; ++i)
	{
		float x = rangeDist(rng);
		float y = rangeDist(rng);
		float speed = speedDist(rng);
		Vec effectVec = Vec(missileVec.x + x, missileVec.y + y);

		effectManager->MakeEffect(EFFECT::EFFECT_TYPE::EXPLODE_LIGHT, m_Pos, playerMoveSpeed + speed, effectVec);
	}

	return;
}