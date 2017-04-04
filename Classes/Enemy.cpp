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
	Init();
}


void Enemy::Init()
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
void Enemy::FunctionPointerRegist()
{
	// Flight Function Pointer Regist
	m_pFlightHandler[FLIGHT_TYPE::FLY_STRAIGHT] = &Enemy::FlyStraight;
	m_pFlightHandler[FLIGHT_TYPE::FLY_ITEM] = &Enemy::FlyItem;
	m_pFlightHandler[FLIGHT_TYPE::FLY_ACCELERATE] = &Enemy::FlyAccelerate;
	m_pFlightHandler[FLIGHT_TYPE::FLY_GO_AND_SLOW] = &Enemy::FlyGoAndSlow;

	// Fire Function Pointer Regist
	m_pFireHandler[FIRE_TYPE::NORMAL_FIRE] = &Enemy::FireNormal;
	m_pFireHandler[FIRE_TYPE::AIMED_FIRE] = &Enemy::FireAimed;
	m_pFireHandler[FIRE_TYPE::N_WAY_FIRE] = &Enemy::FireNways;
	m_pFireHandler[FIRE_TYPE::MULTI_FIRE] = &Enemy::FireMulti;
	m_pFireHandler[FIRE_TYPE::CIRCLE_FIRE] = &Enemy::FireCircle;

	return;
}

void Enemy::DistributeFireOption()
{
	FireOption op = GetFireOption();
	for (auto& i : m_MissileVec)
	{
		i->SetFireOption(op);
	}

	return;
}

/*
	Launch가능한 미사일이 있다면 찾아서 반환해주는 함수.
	없다면 nullptr 반환.
*/
EnemyMissile * Enemy::GetLaunchableMissile()
{
	for (auto i : m_MissileVec)
	{
		if (!i->GetMissileLaunched())
		{
			return i;
		}
	}

	return nullptr;
}

/*
	LaunchPos를 결정해주는 함수. 기본적으로 LaunchPos = m_Pos이다.
*/
void Enemy::CalcLaunchPos()
{
	m_LaunchPos = m_Pos;
}

/*
	미사일이 지속적인 케어를 받아야하는 경우 진행되는 미사일 프로세스.
*/
void Enemy::MissileManageProc()
{
	if (GetFireOption().GetFireType() == ENEMY::FIRE_TYPE::CIRCLE_FIRE)
	{
		// 미사일들의 옵션의 중심 포지션을 자기 자신으로 바꾸어준다.
		for (auto& i : m_MissileVec)
		{
			auto opt = i->GetOption();
			auto data = opt.GetCircleShotData();
			data.SetCenterPos(m_Pos);

			opt.SetCircleShotData(data);
			i->SetFireOption(opt);
		}
	}

	return;
}

void Enemy::CalcProc(const _In_ FLOAT dt)
{
	// 비활성화 상태일 경우 바로 리턴.
	if (!m_IsEnemyActivated)
	{
		return;
	}

	// 죽지 않았다면 비행기 이동 & 미사일 발사. 
	if (!CheckDead())
	{
		AccTime(dt);
		Fly(dt);
		CalcLaunchPos();
		Fire();
	}
	// 죽은 상태라면 DeadProc진행.
	else
	{
		DeadProc();
	}

	// 죽건 죽지 않았건 미사일은 진행.
	MissileManageProc();
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

#ifdef _DEBUG

#endif
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
			i->CalcProc(dt);
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
	CreateOption opt = GetCreateOption();
	FLOAT currentSpeed = (opt.GetFlightSpeed() + opt.GetAccFlightSpeed() * m_AccTime);
	m_Pos.x += opt.GetFlightVec().x * currentSpeed * dt;
	m_Pos.y += opt.GetFlightVec().y * currentSpeed * dt;
	return TRUE;
}

/*
	어느 정도 거리까지는 빠르게 진행하다가 일정 시간 그 자리에서 느리게 가는 비행.
*/
BOOL Enemy::FlyGoAndSlow(const _In_ FLOAT dt)
{
	CreateOption opt = GetCreateOption();
	GoAndSlowData data = opt.GetGoAndSlowData();

	// 누적 시간이 SlowDownStartTime과 SlowDownStartTime + SlowDonwDurationTime사이일 경우 느린 비행.
	if ((m_AccTime < data.m_SlowDownStartTime + data.m_SlowDownDurationTime) 
		&& (m_AccTime > data.m_SlowDownStartTime))
	{
		m_Pos.x += data.m_SlowDownMoveVec.x * data.m_SlowDownMoveSpeed * dt;
		m_Pos.y += data.m_SlowDownMoveVec.y * data.m_SlowDownMoveSpeed * dt;
	}
	else
	{
		Vec flightVec = opt.GetFlightVec();
		FLOAT flightSpeed = opt.GetFlightSpeed();
		m_Pos.x += flightVec.x * flightSpeed * dt;
		m_Pos.y += flightVec.y * flightSpeed * dt;
	}

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
	m_RecordFireTime += dt;
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
	if (m_IsEnemyDead || !CheckEnemyIsOnDisplay())
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
	for (auto& i : m_MissileVec)
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
void Enemy::Activate(
	const Vec createPos,
	CreateOption& createOption,
	FireOption& fireOption)
{
	SetIsEnemyActivated(TRUE);
	SetIsEnemyDead(FALSE);
	SetCreateOption(createOption);
	SetFireOption(fireOption);

	// 소유 미사일들의 FireOption 변경.
	DistributeFireOption();
	m_Pos = createPos;
	m_Hp = createOption.GetEnemyHp();
}

/*
	활성화된 Enemy를 다시 비활성화해주는 함수.
*/
void Enemy::Deactivate()
{
	SetIsEnemyActivated(FALSE);
	m_IsEnemyExplode = FALSE;
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
	활성화시 등록된 FireOption에 따라 미사일을 발사해 주는 함수.	
*/
void Enemy::Fire()
{
	// FireOption의 타입에 따라 알맞은 함수 포인터 호출.
	(this->*m_pFireHandler[GetFireOption().GetFireType()])();
	return;
}

/*
	일정한 시간에 따라 미사일을 발사해주는 함수.
*/
BOOL Enemy::FireNormal()
{
	FireOption opt = GetFireOption();
	
	if (m_AccTime > opt.GetInitShootDelay()) 
	{
		// 첫번째 진입 시점.
		if ((m_RecordFireTime == m_AccTime)
			|| m_RecordFireTime > opt.GetIntervalShootDelay())
		{
			auto missile = GetLaunchableMissile();
			if (missile != nullptr)
			{
				missile->Launch(m_LaunchPos, opt);
			}
			m_RecordFireTime = 0.f;
		}
	}
	return TRUE;
}

/*
	플레이어의 위치로 미사일을 발사해주는 함수.
	매번 Fire가 호출 될 때마다 옵션의 미사일 벡터를 플레이어에게 바꿔주고 FireNormal을 호출한다.
*/
BOOL Enemy::FireAimed()
{
	// 벡터를 플레이어 쪽으로 바꿔줌.
	SetOptionMissileVecToPlayer();

	// 등록한 옵션을 실행할 FireNormal 호출.
	return FireNormal();
}

/*
	N-way방향으로 나가는 함수 구현. 
*/
BOOL Enemy::FireNways()
{
	FireOption opt = GetFireOption();
	NwayShotData data = opt.GetNwayShotData();

	// 이상한 옵션이 들어오거나 초기화 실패.
	if (!data.GetNwayShotDataValid())
	{
		return FALSE;
	}

	// 플레이어 쪽으로 발사하는 옵션이 있을 경우, 벡터를 플레이어 쪽으로 바꿔줌.
	if (data.m_IsMissileShotToPlayer)
	{
		SetOptionMissileVecToPlayer();
	}

	// 발사 시간 조정.
	// RecordFireTime이 초기 딜레이 이상, 초기 딜레이 + 인터벌 딜레이 이하일 경우 발사.
	if (m_RecordFireTime > opt.GetInitShootDelay() &&
		m_RecordFireTime <= (opt.GetInitShootDelay() + opt.GetIntervalShootDelay()))
	{
		// 미사일에 인터벌 딜레이가 필요할 경우 발사 불가. 
		if (data.m_IsMissileNeedDelay)
		{
			return FALSE;
		}

		// 이번 발사하는 미사일 개수가 짝수일 경우 처리.
		if (data.m_ShotNumber[data.m_RecordShotTimes] % 2 == 0)
		{
			LaunchEvenNumberWays();
		}
		// 발사하는 미사일 개수가 홀수일 경우 처리.
		else
		{
			LaunchOddNumberWays();
		}

		// 발사 후 딜레이 처리와 Shot정보를 다음으로 옮김.
		data.m_IsMissileNeedDelay = TRUE;
		++data.m_RecordShotTimes;
		
		// 재장전 처리.
		// RecordShotTimes == ShotTimes일 경우 재장전 시간이 필요하다.
		if (data.m_RecordShotTimes == data.m_ShotTimes)
		{
			data.m_RecordShotTimes = 0;
			m_RecordFireTime = 0.f;
		}
	}
	// 인터벌 딜레이 처리.
	else if (m_RecordFireTime > (opt.GetInitShootDelay() + opt.GetIntervalShootDelay()))
	{
		// 인터벌 딜레이가 끝났으므로 미사일 발사 가능. 
		data.m_IsMissileNeedDelay = FALSE;
		m_RecordFireTime = opt.GetInitShootDelay();
	}

	// 변경점 적용.
	opt.SetNwayShotData(data);
	SetFireOption(opt);
	return TRUE;
}

/*
	사방으로 미사일을 발사하는 Fire타입
	기본적인 구조는 NwayShot이랑 같고, rotate가 Angle대신 360 / 미사일 개수로 이뤄진다는 차이점이 있다.
*/
BOOL Enemy::FireMulti()
{
	FireOption opt = GetFireOption();
	NwayShotData data = opt.GetNwayShotData();

	if (!data.GetNwayShotDataValid())
	{
		return FALSE;
	}

	if (m_RecordFireTime > opt.GetInitShootDelay() &&
		m_RecordFireTime <= (opt.GetInitShootDelay() + opt.GetIntervalShootDelay()))
	{
		if (data.m_IsMissileNeedDelay)
		{
			return FALSE;
		}
		LaunchMultiWays();

		data.m_IsMissileNeedDelay = TRUE;
		++data.m_RecordShotTimes;

		if (data.m_RecordShotTimes == data.m_ShotTimes)
		{
			data.m_RecordShotTimes = 0;
			m_RecordFireTime = 0.f;
		}
	}
	else if (m_RecordFireTime > (opt.GetInitShootDelay() + opt.GetIntervalShootDelay()))
	{
		data.m_IsMissileNeedDelay = FALSE;
		m_RecordFireTime = opt.GetInitShootDelay();
	}

	// 변경점 적용.
	opt.SetNwayShotData(data);
	SetFireOption(opt);
	return TRUE;
}

/*
	한 점을 중심으로 회전하는 Circle형 미사일을 발사해주는 함수.
	초반 원형으로 퍼지는 벡터만을 쏴주면 나머지는 EnemyMissile에서 회전처리.
*/
BOOL Enemy::FireCircle()
{
	FireOption opt = GetFireOption();
	auto data = opt.GetCircleShotData();

	// 회전탄 발사 시간 조절 (회전탄은 Interval이 길어야 한다.)
	if (m_RecordFireTime > opt.GetInitShootDelay() &&
		m_RecordFireTime < (opt.GetInitShootDelay() + data.m_RotateTime))
	{
		if (data.m_IsMissileNeedDelay)
		{
			return FALSE;
		}
		
		// 사방으로 미사일을 뿌려주는 함수.
		LaunchForRotateWays();
		data.m_IsMissileNeedDelay = TRUE;
	}
	// 인터벌 딜레이 처리.
	else if (m_RecordFireTime > opt.GetInitShootDelay() + data.m_RotateTime + 1.f)
	{
		data.m_IsMissileNeedDelay = FALSE;
		m_RecordFireTime = opt.GetInitShootDelay();
	}

	// 변경점 적용.
	opt.SetCircleShotData(data);
	SetFireOption(opt);
	return TRUE;
}


/*
	가지고 있는 옵션의 벡터를 플레이어 쪽으로 향하게 하는 함수.
	만약 옵션에 RandomRange가 있을 경우, 미사일에 흔들림을 더해준다.
*/
BOOL Enemy::SetOptionMissileVecToPlayer()
{
	FireOption opt = GetFireOption();
	FLOAT range = opt.GetRandomRange();
	Vec vecToPlayer = m_PlayerPos - m_Pos;

	// RandomRange 옵션이 있을 경우
	if (range != 0)
	{
		// 난수 생성기를 통해 -range ~ range 범위의 값을 생성해준다.
		std::mt19937 rng;
		std::uniform_real_distribution<float> dist(-range, range);
		opt.SetMissileVec(Vec(vecToPlayer.x + dist(rng), vecToPlayer.y + dist(rng)));
	}
	else
	{
		// 아닐 경우 그냥 플레이어의 위치를 등록해준다.
		opt.SetMissileVec(Vec(vecToPlayer.x, vecToPlayer.y));
	}

	// 등록한 옵션으로 수정.
	SetFireOption(opt);

	return TRUE;
}

/*
	홀수 개의 미사일을 Launch시키는 함수.
	FireNways에서 호출.
*/
BOOL Enemy::LaunchOddNumberWays()
{
	FireOption opt = GetFireOption();
	NwayShotData data = opt.GetNwayShotData();

	// 미사일에 대입되어 실제로 발사시킬 옵션.
	FireOption inputOption = opt;

	// 좌우가 같은 모양으로 퍼지기 때문에 각도 처리를 해줘야 할 횟수 구하기.
	INT LaunchTimes = (data.m_ShotNumber[data.m_RecordShotTimes] + 1) / 2;

	// 부채꼴 모양으로 퍼질 미사일들의 기준이 될 정중앙 벡터 
	Vec standardVec = opt.GetMissileVec();
	Vec rotateVec = standardVec;
	FLOAT theta = data.m_ShotAngle[data.m_RecordShotTimes];

	for (INT i = 0; i < LaunchTimes; ++i)
	{
		// i * theta만큼 벌어진 벡터 구하고, 그 방향으로 미사일 발사.
		RotateVec(i * theta, standardVec.x, standardVec.y, rotateVec.x, rotateVec.y);

		EnemyMissile* missile = GetLaunchableMissile();
		if (missile != nullptr)
		{
			// 미사일 벡터만 달라진 옵션으로 발사.
			inputOption.SetMissileVec(rotateVec);
			missile->Launch(m_LaunchPos, inputOption);
		}
		// 정중앙 미사일이 아닌 경우, 반대 벡터로도 한 번 더 쏴주기.
		if (i != 0)
		{
			missile = GetLaunchableMissile();
			if (missile != nullptr)
			{
				inputOption.SetMissileVec(rotateVec.GetYSymmetryVec());
				missile->Launch(m_LaunchPos, inputOption);
			}
		}
	}

	return TRUE;
}

/*
	짝수 개의 미사일을 Launch시키는 함수.
	FireNways에서 호출.
*/
BOOL Enemy::LaunchEvenNumberWays()
{
	FireOption opt = GetFireOption();
	NwayShotData data = opt.GetNwayShotData();

	// 미사일에 대입되어 실제로 발사시킬 옵션.
	FireOption inputOption = opt;

	// 좌우가 같은 모양으로 퍼지기 때문에 각도 처리를 해줘야 할 횟수 구하기.
	INT LaunchTimes = (data.m_ShotNumber[data.m_RecordShotTimes]) / 2;

	// 부채꼴 모양으로 퍼질 미사일들의 기준이 될 정중앙 벡터 
	Vec standardVec = opt.GetMissileVec();
	Vec rotateVec = standardVec;
	FLOAT theta = data.m_ShotAngle[data.m_RecordShotTimes];

	for (INT i = 0; i < LaunchTimes; ++i)
	{
		// i * theta + theta / 2만큼 벌어진 벡터 구하고, 그 방향으로 미사일 발사.
		RotateVec(i * theta + theta / 2, standardVec.x, standardVec.y, rotateVec.x, rotateVec.y);

		// Y 대칭 방향으로 쏴주기.
		EnemyMissile* missile = GetLaunchableMissile();
		if (missile != nullptr)
		{
			inputOption.SetMissileVec(rotateVec);
			missile->Launch(m_LaunchPos, inputOption);
		}

		missile = GetLaunchableMissile();
		if (missile != nullptr)
		{
			inputOption.SetMissileVec(rotateVec.GetYSymmetryVec());
			missile->Launch(m_LaunchPos, inputOption);
		}
	}

	return TRUE;
}

/*
	원형으로 미사일을 Launch 시켜주는 함수.
*/
BOOL Enemy::LaunchMultiWays()
{
	FireOption opt = GetFireOption();
	NwayShotData data = opt.GetNwayShotData();
	FireOption inputOption = opt;

	Vec standardVec = opt.GetMissileVec();
	Vec rotateVec = standardVec;
	// 정해진 Angle대신 미사일 개수에 따라 각도가 달라짐.
	FLOAT theta = 360.f / data.m_ShotNumber[data.m_RecordShotTimes];
	INT LaunchTimes = (data.m_ShotNumber[data.m_RecordShotTimes]) / 2;

	for (INT i = 0; i < LaunchTimes; ++i)
	{
		RotateVec(i * theta, standardVec.x, standardVec.y, rotateVec.x, rotateVec.y);

		EnemyMissile* missile = GetLaunchableMissile();
		if (missile != nullptr)
		{
			inputOption.SetMissileVec(rotateVec);
			missile->Launch(m_LaunchPos, inputOption);
		}

		missile = GetLaunchableMissile();
		if (missile != nullptr)
		{
			inputOption.SetMissileVec(rotateVec.GetYSymmetryVec());
			missile->Launch(m_LaunchPos, inputOption);
		}
	}
	return TRUE;
}

/*
	회전탄을 위해 초기에 MultiWay로 뿌려주는 함수.
	원리는 LaunchMultiWays와 같지만, NwayShotData대신 CircleShotData로 발사할 수 있도록 대응.
*/
BOOL Enemy::LaunchForRotateWays()
{
	FireOption opt = GetFireOption();
	CircleShotData data = opt.GetCircleShotData();
	FireOption inputOption = opt;

	Vec standardVec = opt.GetMissileVec();
	Vec rotateVec = standardVec;
	// 정해진 Angle대신 미사일 개수에 따라 각도가 달라짐.
	FLOAT theta = 360.f / data.m_MissileNum;
	INT LaunchTimes;

	// 발사하는 미사일이 홀수이냐 짝수이냐를 판별하여 Launch횟수 결정.
	BOOL IsMissileNumberOdd;
	if ((data.m_MissileNum % 2) == 0)
	{
		IsMissileNumberOdd = FALSE;
		LaunchTimes = data.m_MissileNum / 2;
	}
	// 홀수일 경우.
	else
	{
		IsMissileNumberOdd = TRUE;
		LaunchTimes = (data.m_MissileNum + 1) / 2;
	}

	// 홀수 발사.
	if (IsMissileNumberOdd)
	{
		for (INT i = 0; i < LaunchTimes; ++i)
		{
			RotateVec(i * theta, standardVec.x, standardVec.y, rotateVec.x, rotateVec.y);

			EnemyMissile* missile = GetLaunchableMissile();
			if (missile != nullptr)
			{
				inputOption.SetMissileVec(rotateVec);
				auto inputData = inputOption.GetCircleShotData();
				inputData.SetTheta((theta * i) * M_PI / 180.f);
				inputOption.SetCircleShotData(inputData);
				missile->Launch(m_LaunchPos, inputOption);
			}

			if (i != 0)
			{
				missile = GetLaunchableMissile();
				if (missile != nullptr)
				{
					inputOption.SetMissileVec(rotateVec.GetYSymmetryVec());
					auto inputData = inputOption.GetCircleShotData();
					inputData.SetTheta((-theta * i) * M_PI / 180.f);
					inputOption.SetCircleShotData(inputData);
					missile->Launch(m_LaunchPos, inputOption);
				}
			}
		}
	}
	// 짝수 발사.
	else
	{
		for (INT i = 0; i < LaunchTimes; ++i)
		{
			RotateVec(i * theta + (theta / 2), standardVec.x, standardVec.y, rotateVec.x, rotateVec.y);

			EnemyMissile* missile = GetLaunchableMissile();
			if (missile != nullptr)
			{
				inputOption.SetMissileVec(rotateVec);
				auto inputData = inputOption.GetCircleShotData();
				inputData.SetTheta((theta * i) * M_PI / 180.f);
				inputOption.SetCircleShotData(inputData);
				missile->Launch(m_LaunchPos, inputOption);
			}

			missile = GetLaunchableMissile();
			if (missile != nullptr)
			{
				inputOption.SetMissileVec(rotateVec.GetYSymmetryVec());
				auto inputData = inputOption.GetCircleShotData();
				inputData.SetTheta((-theta * i) * M_PI / 180.f);
				inputOption.SetCircleShotData(inputData);
				missile->Launch(m_LaunchPos, inputOption);
			}
		}
	}

	return TRUE;
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

BOOL Enemy::GetIsEnemyDead() const
{
	return m_IsEnemyDead;
}

ENEMY_TYPE Enemy::GetEnemyType() const
{
	return m_EnemyType;
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

void Enemy::SetIsEnemyDead(const BOOL input)
{
	m_IsEnemyDead = input;
}

void Enemy::SetEnemyType(const ENEMY_TYPE enemyType)
{
	m_EnemyType = enemyType;
}
