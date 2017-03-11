#include "stdafx.h"
#include "Enemy.h"
#include "EnemyMissile.h"

const Vec waitingPosition = Vec(-300.f, -300.f);
const Vec zeroVec = Vec(0.f, 0.f);

Enemy::Enemy()
	: m_Pos(waitingPosition),
	m_AccTime(0.f),
	m_RecordAccTime(0.f),
	m_FlightUnitVec(zeroVec),
	m_PlayerPos(zeroVec),
	m_IsEnemyDead(TRUE)
{
	init();
}

Enemy::Enemy(
	const _In_ Vec createPos,
	const _In_ INT flightType,
	const _In_opt_ Vec flightVec)
	: 
	m_Pos(createPos),
	m_AccTime(0.f),
	m_FlightUnitVec(zeroVec),
	m_RecordAccTime(0.f),
	m_RecordFlyTime(0.f),
	m_PlayerPos(zeroVec),
	m_FlightType(flightType),
	m_IsEnemyDead(FALSE),
	m_IsEnemyReadyToDelete(FALSE)
{
	m_FlightVec = flightVec;
	init();
}

void Enemy::init()
{
	m_pSprite = new CImage();
	m_pShadeSprite = new CImage();
	FunctionPointerRegist();
	return;
}

/*
	~Enemy
	m_MissileVec�� �ִ� �̻��ϵ� �����ֱ�.
*/
Enemy::~Enemy()
{
	ReleaseCImages();
	DeleteAllElementsMissileVector();
}

/*
	Regist All Function Pointer which Enemy will manage.
*/
vRESULT Enemy::FunctionPointerRegist()
{
	// Flight Function Pointer Regist
	m_pFlightHandler[FLIGHT_TYPE::FLY_STRAIGHT] = &Enemy::FlyStraight;
	m_pFlightHandler[FLIGHT_TYPE::FLY_ITEM] = &Enemy::FlyItem;
	m_pFlightHandler[FLIGHT_TYPE::FLY_ACCELERATE] = &Enemy::FlyAccelerate;
	m_pFlightHandler[FLIGHT_TYPE::FLY_GO_AND_SLOW] = &Enemy::FlyGoAndSlow;

	// Missile Fly Function Pointer Regist
	m_pMissileFlyHandler[MISSILE_TYPE::STRAIGHT_FIRE] = &Enemy::MissileFlyStraight;
	m_pMissileFlyHandler[MISSILE_TYPE::AIM_FIRE] = &Enemy::MissileFlyAimed;

	return WELL_PERFORMED;
}

/*
	Launch������ �̻����� �ִٸ� ã�Ƽ� ��ȯ���ִ� �Լ�.
	���ٸ� nullptr ��ȯ.
*/
EnemyMissile * Enemy::GetLaunchableMissile()
{
	for (auto i : m_MissileVec)
	{
		if (!i->m_IsMissileLaunched)
		{
			return i;
		}
	}

	return nullptr;
}

void Enemy::CalProc(const _In_ FLOAT dt)
{
	if (!CheckDead())
	{
		AccTime(dt);
		Fly(dt);
		Fire();
	}
	else
	{
		DeadProc();
	}

	MissileFly(dt);
	CheckEnemyReadyToDelete();
	return;
}

void Enemy::DrawProc(_Inout_ HDC drawDC)
{
	// Enemy�� �׾ �̻����� �׸�����.
	if (!m_IsEnemyDead)
	{
		Draw(drawDC);
	}
	DrawMissiles(drawDC);
	return;
}

void Enemy::Fly(const _In_ FLOAT dt)
{
	(this->*m_pFlightHandler[m_FlightType])(dt);
	return;
}

void Enemy::MissileFly(const _In_ FLOAT dt)
{
	for (auto i : m_MissileVec)
	{
		if (i->GetMissileLaunched())
		{
			auto MissileType = i->GetMissileType();
			if (MissileType != MISSILE_TYPE::NONE)
			{
				(this->*m_pMissileFlyHandler[MissileType])(i, dt);
			}
		}
	}
	return;
}

/*
	FlyStratight accord with m_FlightVec.
*/
BOOL Enemy::FlyStraight(const _In_ FLOAT dt)
{
	m_Pos.x += m_FlightVec.x * m_FlightSpeed * dt;
	m_Pos.y += m_FlightVec.y * m_FlightSpeed * dt;
	return TRUE;
}

/*
	Make random flightVector and Fly until "itemFlyTime(const FLOAT)" end.
	Using in Item :: public Enemy
*/
BOOL Enemy::FlyItem(const _In_ FLOAT dt)
{
	const FLOAT itemFlyTime = 1.0f;
	if ((m_FlightUnitVec.x == 0 && m_FlightUnitVec.y == 0) || (m_RecordFlyTime > itemFlyTime))
	{
		GetUnitVec((FLOAT)(rand() % 100), (FLOAT)(rand() % 100), &m_FlightUnitVec.x, &m_FlightUnitVec.y);
		FixUnitVecForRemainOnDisplay();
		m_RecordFlyTime = 0.f;
	}

	m_Pos.x += m_FlightUnitVec.x * dt * m_FlightSpeed;
	m_Pos.y += m_FlightUnitVec.y * dt * m_FlightSpeed;
	return TRUE;
}

/*
	�������� ���� ������ �� �� ������ �������� �ٽ� ȭ�鿡 ���� �� �ֵ��� ���ֺ��͸� �����ִ� �Լ�.
*/
void Enemy::FixUnitVecForRemainOnDisplay()
{
	INT boundaryRange = 150;
	if (m_Pos.x < boundaryRange)
	{
		m_FlightUnitVec.x = fabs(m_FlightUnitVec.x);
	}
	else if (m_Pos.x > winWidth - boundaryRange)
	{
		m_FlightUnitVec.x = -fabs(m_FlightUnitVec.x);
	}

	if (m_Pos.y < boundaryRange)
	{
		m_FlightUnitVec.y = fabs(m_FlightUnitVec.y);
	}
	else if (m_Pos.y > winWidth - boundaryRange)
	{
		m_FlightUnitVec.y = -fabs(m_FlightUnitVec.y);
	}
}

/*
	���� �������� ����
*/
BOOL Enemy::FlyAccelerate(const _In_ FLOAT dt)
{
	FLOAT currentSpeed = (m_Option.m_InitSpeed + m_Option.m_AccSpeedPerSec * m_AccTime);
	m_Pos.x += m_FlightVec.x * currentSpeed * dt;
	m_Pos.y += m_FlightVec.y * currentSpeed * dt;
	return TRUE;
}

/*
	��� ���� �Ÿ������� ������ �����ϴٰ� ���� �ð� �� �ڸ����� ������ ���� ����.
*/
BOOL Enemy::FlyGoAndSlow(const _In_ FLOAT dt)
{
	// ���� �ð��� m_TimeToSlow�� m_TimeToSlow + m_SlowedTime ������ ��� ���� ����.
	if ((m_AccTime < m_Option.m_TimeToSlow + m_Option.m_SlowedTime) 
		&& (m_AccTime > m_Option.m_TimeToSlow))
	{
		m_Pos.x += m_FlightVec.x * m_Option.m_SlowedSpeed * dt;
		m_Pos.y += m_FlightVec.y * m_Option.m_SlowedSpeed * dt;
	}
	else
	{
		m_Pos.x += m_FlightVec.x * m_Option.m_InitSpeed * dt;
		m_Pos.y += m_FlightVec.y * m_Option.m_InitSpeed * dt;
	}

	return TRUE;
}

/*
	�������� �̻����� ���ư��� �ϴ� ���.
*/
BOOL Enemy::MissileFlyStraight(EnemyMissile* missile, const FLOAT dt)
{
	missile->Fly(dt, 0, 1, m_MissileSpeed);
	missile->CheckColideWithPlayer();
	return TRUE;
}

/*
	����ź���� �̻����� ���ư��� �ϴ� ���.
	EnemyMissile���� ���ǵ� MissileOption�� �̿��� Launch�� ����ؾ߸� �̻����� �۵��Ѵ�.
*/
BOOL Enemy::MissileFlyAimed(EnemyMissile* missile, const FLOAT dt)
{
	MissileOption option = missile->GetOption();
	if (!option.IsOptionCanUse())
	{
		return FALSE;
	}

	missile->Fly(dt, option.m_MissileVec.x, option.m_MissileVec.y, option.m_MissileSpeed);
	missile->CheckColideWithPlayer();

	return TRUE;
}

/*
	Return Enemy Is on Display.
*/
BOOL Enemy::CheckEnemyIsOnDisplay()
{
	if ((m_Pos.x + m_SpriteRange.x / 2) <= -boundaryRange)
	{
		return FALSE;
	}
	else if ((m_Pos.x - m_SpriteRange.y / 2) >= winWidth + boundaryRange)
	{
		return FALSE;
	}
	else if ((m_Pos.y + m_SpriteRange.y / 2) <= -boundaryRange)
	{
		return FALSE;
	}
	else if ((m_Pos.y - m_SpriteRange.x / 2) >= winHeight + boundaryRange)
	{
		return FALSE;
	}

	return TRUE;
}

/*
	m_FlightVec�� �µ��� CImage�� ȸ�������ִ� �Լ�.
	Enemy ��� Ŭ�������� ȣ��.
*/
INT Enemy::RotateAccordWithVec()
{
	// TODO :: CImage ȸ�� �Լ�.

	return WELL_PERFORMED;
}

const vRESULT Enemy::GetDamage(const _In_ INT damage, const _In_ Vec playerMissile)
{
	m_Hp -= damage;

	if (m_Hp <= 0)
	{
		m_IsEnemyDead = TRUE;
	}
	
	return WELL_PERFORMED;
}

// Enemy�ȿ� �ð��� �������ִ� �Լ�.
void Enemy::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	m_RecordAccTime += dt;
	m_RecordFlyTime += dt;
	return;
}

// �ڽ��� �׾����� �ƴ��� �Ǵ��ϴ� �Լ�. �׾��ٸ� TRUE�� ��ȯ.
BOOL Enemy::CheckDead()
{
	if (m_Hp <= 0)
	{
		m_IsEnemyDead = TRUE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// �̻��ϵ��� �����ϴ� �Լ�. Enemy�� ��ӹ޴� Ŭ������ init���� ȣ��.
void Enemy::LoadMissiles(const _In_ ENEMY::MISSILE_SIZE missileSize)
{
	for (int i = 0; i < m_LoadedMissileNumber; ++i)
	{
		EnemyMissile* newMissile = new EnemyMissile(missileSize);
		m_MissileVec.push_back(newMissile);
	}

	return;
}

/*
	�̻��� ���͸� ��ȸ�ϸ� Draw�� ȣ�����ִ� �Լ�.
*/
void Enemy::DrawMissiles(_Inout_ HDC drawDC)
{
	for (auto i : m_MissileVec)
	{
		i->Draw(drawDC);
	}

	return;
}

/*
	��� ���� m_MissileVec�� �ִ� ��� ���ҵ��� ��ȸ�ϸ鼭 �Ҹ��ڸ� ȣ�����ִ� �Լ�.
*/
void Enemy::DeleteAllElementsMissileVector()
{
	std::vector<EnemyMissile*>::iterator iter = m_MissileVec.begin();
	while (iter != m_MissileVec.end())
	{
		delete (*iter);
		iter = m_MissileVec.erase(iter);
	}

	return;
}

/*
	�̻����� ������ ��� ���������� ��ȯ���ִ� �Լ�.
*/
BOOL Enemy::IsAllMissilesEndFly()
{
	for (auto i : m_MissileVec)
	{
		if (i->GetMissileLaunched())
		{
			return FALSE;
		}
	}

	return TRUE;
}

/*
	Enemy�� �������� ���� �������� Ȯ���Ѵ�.
	IsAllMissilesEndFly�� TRUE�̰�, EnemyDead�̰ų� ȭ��� ������ Delete �غ� �Ϸ�� �����̴�.
*/
void Enemy::CheckEnemyReadyToDelete()
{
	// �̻����� Fly�� ������ ���ߴٸ� �׳� return.
	if (!IsAllMissilesEndFly())
	{
		return;
	}
	// Enemy�� Dead�����̰ų� ȭ��� ���� ��� delete ready.
	if (m_IsEnemyDead || !CheckEnemyIsOnDisplay())
	{
		m_IsEnemyReadyToDelete = TRUE;
	}

	return;
}

/*
	�Ҵ�� CImage�� Delete���ش�. 
*/
void Enemy::ReleaseCImages()
{
	delete m_pSprite;
	m_pSprite = nullptr;
	delete m_pShadeSprite;
	m_pShadeSprite = nullptr;

	return;
}

