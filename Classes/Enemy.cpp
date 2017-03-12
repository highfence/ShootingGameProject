#include "stdafx.h"
#include "Enemy.h"
#include "EnemyMissile.h"

const Vec waitingPosition = Vec(-300.f, -300.f);
const Vec zeroVec = Vec(0.f, 0.f);

Enemy::Enemy()
	:
	m_IsEnemyActivated(FALSE),
	m_Pos(waitingPosition),
	m_AccTime(0.f),
	m_RecordAccTime(0.f),
	m_FlightUnitVec(zeroVec),
	m_PlayerPos(zeroVec),
	m_IsEnemyDead(TRUE)
{
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
	m_MissileVec에 있는 미사일들 지워주기.
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
	Launch가능한 미사일이 있다면 찾아서 반환해주는 함수.
	없다면 nullptr 반환.
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

void Enemy::CalcProc(const _In_ FLOAT dt)
{
	// 비활성화 상태일 경우 바로 리턴.
	if (m_IsEnemyActivated)
	{
		return;
	}

	// 죽지 않았다면 비행기 이동 & 미사일 발사. 
	if (!CheckDead())
	{
		AccTime(dt);
		Fly(dt);
		Fire();
	}
	// 죽은 상태라면 DeadProc진행.
	else
	{
		DeadProc();
	}

	// 죽건 죽지 않았건 미사일은 진행.
	MissileFly(dt);

	// 행동이 끝났다면 비활성화.
	if (CheckActEnd())
	{
		Deactivate();
	}

	return;
}

void Enemy::DrawProc(_Inout_ HDC drawDC)
{
	// 비활성화 상태라면 바로 return
	if (!GetIsEnemyActivated())
	{
		return;
	}

	// Enemy가 죽어도 미사일은 그리도록.
	if (!m_IsEnemyDead)
	{
		Draw(drawDC);
	}
	DrawMissiles(drawDC);
	return;
}

/*
	FlightHandler에 연결되어 있는 함수를 활성화시켜주는 함수.
*/
void Enemy::Fly(const _In_ FLOAT dt)
{
	(this->*m_pFlightHandler[m_CreateOption.GetFlightType()])(dt);
	return;
}

/*
	소유하고 있는 미사일들을 이동시키는 함수.
*/
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
	Vec flightVec = m_CreateOption.GetFlightVec();
	FLOAT flightSpeed = m_CreateOption.GetFlightSpeed();
	m_Pos.x += flightVec.x * flightSpeed * dt;
	m_Pos.y += flightVec.y * flightSpeed * dt;
	return TRUE;
}

/*
	Make random flightVector and Fly until "itemFlyTime(const FLOAT)" end.
	Using in Item :: public Enemy
*/
BOOL Enemy::FlyItem(const _In_ FLOAT dt)
{
	const FLOAT itemFlyTime = 1.0f;
	if ((m_FlightUnitVec.x == 0 && m_FlightUnitVec.y == 0)
		|| (m_RecordFlyTime > itemFlyTime))
	{
		GetUnitVec((FLOAT)(rand() % 100), (FLOAT)(rand() % 100), &m_FlightUnitVec.x, &m_FlightUnitVec.y);
		FixUnitVecForRemainOnDisplay();
		m_RecordFlyTime = 0.f;
	}

	FLOAT flightSpeed = m_CreateOption.GetFlightSpeed();
	m_Pos.x += m_FlightUnitVec.x * dt * flightSpeed;
	m_Pos.y += m_FlightUnitVec.y * dt * flightSpeed;
	return TRUE;
}

/*
	아이템이 랜덤 비행을 할 때 밖으로 나가더라도 다시 화면에 들어올 수 있도록 유닛벡터를 고쳐주는 함수.
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
	점점 빨라지는 비행
*/
BOOL Enemy::FlyAccelerate(const _In_ FLOAT dt)
{
	CreateOption op = GetCreateOption();
	FLOAT currentSpeed = (op.GetFlightSpeed() + op.GetAccFlightSpeed() * m_AccTime);
	m_Pos.x += op.GetFlightVec().x * currentSpeed * dt;
	m_Pos.y += op.GetFlightVec().y * currentSpeed * dt;
	return TRUE;
}

/*
	어느 정도 거리까지는 빠르게 진행하다가 일정 시간 그 자리에서 느리게 가는 비행.
*/
BOOL Enemy::FlyGoAndSlow(const _In_ FLOAT dt)
{
	CreateOption op = GetCreateOption();
	GoAndSlowData data = op.GetGoAndSlowData();

	// 누적 시간이 SlowDownStartTime과 SlowDownStartTime + SlowDonwDurationTime사이일 경우 느린 비행.
	if ((m_AccTime < data.SlowDownStartTime + data.SlowDownDurationTime) 
		&& (m_AccTime > data.SlowDownStartTime))
	{
		m_Pos.x += data.SlowDownMoveVec.x * data.SlowDownMoveSpeed * dt;
		m_Pos.y += data.SlowDownMoveVec.y * data.SlowDownMoveSpeed * dt;
	}
	else
	{
		Vec flightVec = op.GetFlightVec();
		FLOAT flightSpeed = op.GetFlightSpeed();
		m_Pos.x += flightVec.x * flightSpeed * dt;
		m_Pos.y += flightVec.y * flightSpeed * dt;
	}

	return TRUE;
}

/*
	직선으로 미사일을 날아가게 하는 방식.
*/
BOOL Enemy::MissileFlyStraight(EnemyMissile* missile, const FLOAT dt)
{
	FireOption op;
	if ((op = GetFireOption()).GetIsOptionCanUse())
	{
		missile->Fly(dt, 0, 1, op.GetMissileSpeed());
		missile->CheckColideWithPlayer();
	}
	return TRUE;
}

/*
	조준탄으로 미사일을 날아가게 하는 방식.
	EnemyMissile에서 정의된 MissileOption을 이용한 Launch를 사용해야만 미사일이 작동한다.
*/
BOOL Enemy::MissileFlyAimed(EnemyMissile* missile, const FLOAT dt)
{
	FireOption option = missile->GetOption();
	if (!option.GetIsOptionCanUse())
	{
		return FALSE;
	}

	missile->Fly(dt, option.GetMissileVec().x, option.GetMissileVec().y, option.GetMissileSpeed());
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
	Enemy에게 데미지를 주는 함수.
	Enemy가 맞을 때 이펙트가 있어야하는 경우는 상속받은 클래스에서 재정의 해주어야 함.
*/
void Enemy::GetDamage(const _In_ INT damage, const _In_ Vec playerMissile)
{
	m_Hp -= damage;
	if (m_Hp <= 0)
	{
		m_IsEnemyDead = TRUE;
	}
}

/*
	Enemy안에 시간을 누적해주는 함수.
*/
void Enemy::AccTime(const _In_ FLOAT dt)
{
	m_AccTime += dt;
	m_RecordAccTime += dt;
	m_RecordFlyTime += dt;
	return;
}

/*
	자신이 죽었는지 아닌지 판단하는 함수. 죽었다면 TRUE를 반환.
*/
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

/*
	Act가 끝났는지 확인하는 함수.
	1. 모든 미사일의 비행이 끝나야 하고
	2. 죽거나 화면 바깥에 있어야 한다.
*/
BOOL Enemy::CheckActEnd()
{
	// 미사일이 비행이 끝나지 않았다면 FALSE 리턴.
	if (!IsAllMissilesEndFly())
	{
		return FALSE;
	}
	if (m_IsEnemyDead || CheckEnemyIsOnDisplay())
	{
		return TRUE;
	}
	return FALSE;
}

/*
	미사일들을 적재하는 함수. Enemy를 상속받는 클래스의 init에서 호출.
*/
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
	미사일 벡터를 순회하며 Draw를 호출해주는 함수.
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
	멤버 변수 m_MissileVec에 있는 모든 원소들을 순회하면서 소멸자를 호출해주는 함수.
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
	비활성화된 Enemy를 활성화 시켜준다.
*/
void Enemy::Activate(CreateOption& createOption, FireOption& fireOption)
{
	SetIsEnemyActivated(TRUE);
	SetCreateOption(createOption);
	SetFireOption(fireOption);
	if (GetCreateOption().GetIsOptionCanUse())
	{
		m_Pos = GetCreateOption().GetCreatePos();
	}
}

/*
	활성화된 Enemy를 다시 비활성화해주는 함수.
*/
void Enemy::Deactivate()
{
	SetIsEnemyActivated(FALSE);
	SetCreateOption(nullptr);
	SetFireOption(nullptr);
}

/*
	미사일의 비행이 모두 끝났는지를 반환해주는 함수.
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
	할당된 CImage를 Delete해준다. 
*/
void Enemy::ReleaseCImages()
{
	delete m_pSprite;
	m_pSprite = nullptr;
	delete m_pShadeSprite;
	m_pShadeSprite = nullptr;

	return;
}

/*
	Getter, Setter Zone
*/
BOOL Enemy::GetIsEnemyActivated() const
{
	return m_IsEnemyActivated;
}

CreateOption Enemy::GetCreateOption() const
{
	return m_CreateOption;
}

FireOption Enemy::GetFireOption() const
{
	return m_FireOption;
}

Vec Enemy::GetPosition() const
{
	return m_Pos;
}

Vec Enemy::GetColideRange() const
{
	return m_ColideRange;
}

void Enemy::SetIsEnemyActivated(const BOOL input)
{
	m_IsEnemyActivated = input;
}

void Enemy::SetCreateOption(const CreateOption option)
{
	m_CreateOption = option;
}

void Enemy::SetFireOption(const FireOption option)
{
	m_FireOption = option;
}

void Enemy::SetPosition(const Vec position)
{
	m_Pos = position;
}

void Enemy::SetColideRange(const Vec range)
{
	m_ColideRange = range;
}

void Enemy::SetPlayerPos(const Vec playerPos)
{
	m_PlayerPos = playerPos;
}
