#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "OptionMissile.h"

const INT optionMissileDamage = 3;
const INT optionMissileWidth = 6;
const INT optionMissileSmallHeight = 16;
const INT optionMissileHeight = 23;
const FLOAT optionMissileLongerTime = 0.2f;
const std::wstring optionMissileRedSmall = _T("../Resources/Player/OptionMissileRedSmall.png");
const std::wstring optionMissileBlueSmall = _T("../Resources/Player/OptionMissileBlueSmall.png");
const std::wstring optionMissileRed = _T("../Resources/Player/OptionMissileRed.png");
const std::wstring optionMissileBlue = _T("../Resources/Player/OptionMissileBlue.png");
const std::wstring optionMissileShade = _T("../Resources/Player/OptionMissileS.png");
const std::wstring optionMissileSmallShade = _T("../Resources/Player/OptionMissileSmallS.png");


OptionMissile::OptionMissile(const _In_ PLAYER::OPTION_COLOR color)
	: Missile(), m_MissileColor(color)
{
	Init();
	NormalSizeImgLoad(FALSE);
}

void OptionMissile::Init()
{
	m_Damage = 3;
	return;
}

void OptionMissile::SmallSizeImgLoad(const _In_ BOOL isImgLoadedOnce)
{
	// Small Size �̻��Ϸ� width, height ����.
	m_Width = optionMissileWidth;
	m_Height = optionMissileSmallHeight;

	// �̹��� �ε尡 �Ǿ��־��ٸ� Destroy.
	if (isImgLoadedOnce)
	{
		m_pShapeSprite->Destroy();
		m_pSprite->Destroy();
	}
	
	// ���� ���� �̹��� �ε�.
	if (m_MissileColor == PLAYER::OPTION_COLOR::RED)
	{
		m_pSprite->Load(optionMissileRedSmall.c_str());
	}
	else if (m_MissileColor == PLAYER::OPTION_COLOR::BLUE)
	{
		m_pSprite->Load(optionMissileBlueSmall.c_str());
	}

	// ���̵� �̹��� �ε�.
	m_pShapeSprite->Load(optionMissileSmallShade.c_str());
	return;
}

void OptionMissile::NormalSizeImgLoad(const _In_ BOOL isImgLoadedOnce)
{
	// Normal Size �̻��Ϸ� width, height ����.
	m_Width = optionMissileWidth;
	m_Height = optionMissileHeight;

	// �̹��� �ε尡 �Ǿ��־��ٸ� Destroy.
	if (isImgLoadedOnce)
	{
		m_pShapeSprite->Destroy();
		m_pSprite->Destroy();
	}
	
	// ���� ���� �̹��� �ε�.
	if (m_MissileColor == PLAYER::OPTION_COLOR::RED)
	{
		m_pSprite->Load(optionMissileRed.c_str());
	}
	else if (m_MissileColor == PLAYER::OPTION_COLOR::BLUE)
	{
		m_pSprite->Load(optionMissileBlue.c_str());
	}

	// ���̵� �̹��� �ε�.
	m_pShapeSprite->Load(optionMissileShade.c_str());
	return;
}

void OptionMissile::CheckMissileFlyEnough()
{
	if (m_AccTime >= optionMissileLongerTime)
	{
		NormalSizeImgLoad(TRUE);
	}
	return;
}

void OptionMissile::AccTime(const FLOAT deltaTime)
{
	m_AccTime += deltaTime;
	return;
}

void OptionMissile::MissileDestroy()
{
	m_IsMissileLaunched = FALSE;
	m_AccTime = 0.f;
	SmallSizeImgLoad(TRUE);
	return;
}

OptionMissile::~OptionMissile()
{

}

void OptionMissile::Fly(
	const _In_ FLOAT dt,
	const _In_ FLOAT vecX,
	const _In_ FLOAT vecY,
	const _In_ FLOAT speed)
{
	if (!m_IsMissileLaunched)
	{
		return;
	}

	// �ð� ����.
	AccTime(dt);

	// ���� �ð� �̻��� �Ǹ� �̹��� ���������.
	// CheckMissileFlyEnough();

	FLOAT unitVecX;
	FLOAT unitVecY;

	GetUnitVec(vecX, vecY, &unitVecX, &unitVecY);

	m_Pos.x += unitVecX * speed * dt;
	m_Pos.y += unitVecY * speed * dt;

	if (!IsMissileOnDisplay())
	{
		MissileDestroy();
	}

	CheckColide();

	return;
}

BOOL OptionMissile::CheckColide()
{
	Enemy* i = EnemyManager::GetInstance()->FindEnemyColideWith(m_Pos, Vec(m_Width, m_Height));

	// �ڽŰ� �浹�� Enemy�� �ִٸ�,
	if (i != nullptr)
	{
		// �浹 ó�� �� �̻��� �Ҹ�.
		i->GetDamage(m_Damage, m_Pos);
		MissileDestroy();

		return TRUE;
	}
	
	return FALSE;
}