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

	// Missile Fly Function Pointer Regist
	//m_pMissileFlyHandler[MISSILE_TYPE::STRAIGHT_FIRE] = &Enemy::MissileFlyStraight;
	//m_pMissileFlyHandler[MISSILE_TYPE::AIM_FIRE] = &Enemy::MissileFlyAimed;

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

void Enemy::CalcProc(const _In_ FLOAT dt)
{

	// ��Ȱ��ȭ ������ ��� �ٷ� ����.
	if (!m_IsEnemyActivated)
	{
		return;
	}

	// ���� �ʾҴٸ� ����� �̵� & �̻��� �߻�. 
	if (!CheckDead())
	{
		AccTime(dt);
		Fly(dt);
		Fire();
	}
	// ���� ���¶�� DeadProc����.
	else
	{
		DeadProc();
	}

	// �װ� ���� �ʾҰ� �̻����� ����.
	MissileFly(dt);

	// �ൿ�� �����ٸ� ��Ȱ��ȭ.
	if (CheckActEnd())
	{
		Deactivate();
	}

	return;
}

void Enemy::DrawProc(_Inout_ HDC drawDC)
{
	// ��Ȱ��ȭ ���¶�� �ٷ� return
	if (!GetIsEnemyActivated())
	{
		return;
	}

	// Enemy�� �׾ �̻����� �׸�����.
	if (!m_IsEnemyDead)
	{
		Draw(drawDC);
	}
	DrawMissiles(drawDC);

#ifdef _DEBUG
	//std::wstring debugLabel = _T("Player X : ") + std::to_wstring(m_PlayerPos.x) + _T(", Y : ") + std::to_wstring(m_PlayerPos.y);
	//TextOut(drawDC, m_Pos.x, m_Pos.y, debugLabel.c_str(), wcslen(debugLabel.c_str()));
#endif
	return;
}

/*
	FlightHandler�� ����Ǿ� �ִ� �Լ��� Ȱ��ȭ�����ִ� �Լ�.
*/
void Enemy::Fly(const _In_ FLOAT dt)
{
	(this->*m_pFlightHandler[m_CreateOption.GetFlightType()])(dt);
	return;
}

/*
	�����ϰ� �ִ� �̻��ϵ��� �̵���Ű�� �Լ�.
*/
void Enemy::MissileFly(const _In_ FLOAT dt)
{
	for (auto i : m_MissileVec)
	{
		if (i->GetMissileLaunched())
		{
			// TODO :: �̻����� �ڱⰡ �׳� �̵���Ű����.
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
	CreateOption op = GetCreateOption();
	FLOAT currentSpeed = (op.GetFlightSpeed() + op.GetAccFlightSpeed() * m_AccTime);
	m_Pos.x += op.GetFlightVec().x * currentSpeed * dt;
	m_Pos.y += op.GetFlightVec().y * currentSpeed * dt;
	return TRUE;
}

/*
	��� ���� �Ÿ������� ������ �����ϴٰ� ���� �ð� �� �ڸ����� ������ ���� ����.
*/
BOOL Enemy::FlyGoAndSlow(const _In_ FLOAT dt)
{
	CreateOption op = GetCreateOption();
	GoAndSlowData data = op.GetGoAndSlowData();

	// ���� �ð��� SlowDownStartTime�� SlowDownStartTime + SlowDonwDurationTime������ ��� ���� ����.
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

///*
//	�������� �̻����� ���ư��� �ϴ� ���.
//*/
//BOOL Enemy::MissileFlyStraight(EnemyMissile* missile, const FLOAT dt)
//{
//	FireOption op;
//	if ((op = GetFireOption()).GetIsOptionCanUse())
//	{
//		missile->Fly(dt, 0, 1, op.GetMissileSpeed());
//		missile->CheckColideWithPlayer();
//	}
//	return TRUE;
//}
//
///*
//	����ź���� �̻����� ���ư��� �ϴ� ���.
//	EnemyMissile���� ���ǵ� MissileOption�� �̿��� Launch�� ����ؾ߸� �̻����� �۵��Ѵ�.
//*/
//BOOL Enemy::MissileFlyAimed(EnemyMissile* missile, const FLOAT dt)
//{
//	FireOption option = missile->GetOption();
//	if (!option.GetIsOptionCanUse())
//	{
//		return FALSE;
//	}
//
//	missile->Fly(dt, option.GetMissileVec().x, option.GetMissileVec().y, option.GetMissileSpeed());
//	missile->CheckColideWithPlayer();
//
//	return TRUE;
//}

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
	Enemy���� �������� �ִ� �Լ�.
	Enemy�� ���� �� ����Ʈ�� �־���ϴ� ���� ��ӹ��� Ŭ�������� ������ ���־�� ��.
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
	Enemy�ȿ� �ð��� �������ִ� �Լ�.
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
	�ڽ��� �׾����� �ƴ��� �Ǵ��ϴ� �Լ�. �׾��ٸ� TRUE�� ��ȯ.
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
	Act�� �������� Ȯ���ϴ� �Լ�.
	1. ��� �̻����� ������ ������ �ϰ�
	2. �װų� ȭ�� �ٱ��� �־�� �Ѵ�.
*/
BOOL Enemy::CheckActEnd()
{
	// �̻����� ������ ������ �ʾҴٸ� FALSE ����.
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
	�̻��ϵ��� �����ϴ� �Լ�. Enemy�� ��ӹ޴� Ŭ������ init���� ȣ��.
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
	�̻��� ���͸� ��ȸ�ϸ� Draw�� ȣ�����ִ� �Լ�.
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
	��Ȱ��ȭ�� Enemy�� Ȱ��ȭ �����ش�.
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

	// ���� �̻��ϵ��� FireOption ����.
	DistributeFireOption();
	m_Pos = createPos;
	m_Hp = createOption.GetEnemyHp();
}

/*
	Ȱ��ȭ�� Enemy�� �ٽ� ��Ȱ��ȭ���ִ� �Լ�.
*/
void Enemy::Deactivate()
{
	SetIsEnemyActivated(FALSE);
	SetCreateOption(nullptr);
	SetFireOption(nullptr);
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

/*
	Ȱ��ȭ�� ��ϵ� FireOption�� ���� �̻����� �߻��� �ִ� �Լ�.	
*/
void Enemy::Fire()
{
	// FireOption�� Ÿ�Կ� ���� �˸��� �Լ� ������ ȣ��.
	(this->*m_pFireHandler[GetFireOption().GetFireType()])();
	return;
}

/*
	������ �ð��� ���� �̻����� �߻����ִ� �Լ�.
*/
BOOL Enemy::FireNormal()
{
	FireOption op = GetFireOption();
	
	if (m_AccTime > op.GetInitShootDelay() && m_RecordFireTime > op.GetIntervalShootDelay())
	{
		auto missile = GetLaunchableMissile();
		if (missile != nullptr)
		{
			missile->Launch(m_Pos, op);
		}
		m_RecordFireTime = 0.f;
	}
	return TRUE;
}

/*
	�÷��̾��� ��ġ�� �̻����� �߻����ִ� �Լ�.
	�Ź� Fire�� ȣ�� �� ������ �ɼ��� �̻��� ���͸� �÷��̾�� �ٲ��ְ� FireNormal�� ȣ���Ѵ�.
*/
BOOL Enemy::FireAimed()
{
	// ���͸� �÷��̾� ������ �ٲ���.
	SetOptionMissileVecToPlayer();

	// ����� �ɼ��� ������ FireNormal ȣ��.
	return FireNormal();
}

/*
	N-way�������� ������ �Լ� ����. 
*/
BOOL Enemy::FireNways()
{
	FireOption op = GetFireOption();
	NwayShotData data = op.GetNwayShotData();

	// �̻��� �ɼ��� �����ų� �ʱ�ȭ ����.
	if (!data.GetNwayShotDataValid())
	{
		return FALSE;
	}

	// �÷��̾� ������ �߻��ϴ� �ɼ��� ���� ���, ���͸� �÷��̾� ������ �ٲ���.
	if (data.IsMissileShotToPlayer)
	{
		SetOptionMissileVecToPlayer();
	}

	// �߻� �ð� ����.
	// RecordFireTime�� �ʱ� ������ �̻�, �ʱ� ������ + ���͹� ������ ������ ��� �߻�.
	if (m_RecordFireTime > op.GetInitShootDelay() &&
		m_RecordFireTime <= (op.GetInitShootDelay() + op.GetIntervalShootDelay()))
	{
		// �̻��Ͽ� ���͹� �����̰� �ʿ��� ��� �߻� �Ұ�. 
		if (data.IsMissileNeedDelay)
		{
			return FALSE;
		}

		// �̹� �߻��ϴ� �̻��� ������ ¦���� ��� ó��.
		if (data.ShotNumber[data.RecordShotTimes] % 2 == 0)
		{
			LaunchOddNumberWaysMissiles();
			// ������ ó��.
			data.IsMissileNeedDelay = TRUE;
		}
		// �߻��ϴ� �̻��� ������ Ȧ���� ��� ó��.
		else
		{
			LaunchEvenNumberWaysMissiles();
			// ������ ó��.
			data.IsMissileNeedDelay = TRUE;
		}
		
		// ������ ó��.
		// RecordShotTimes == ShotTimes�� ��� ������ �ð��� �ʿ��ϴ�.
		if (data.RecordShotTimes == data.ShotTimes)
		{
			data.RecordShotTimes = 0;
			m_RecordFireTime = 0.f;
		}
	}
	// ���͹� ������ ó��.
	else if (m_RecordFireTime > (op.GetInitShootDelay() + op.GetIntervalShootDelay()))
	{
		// ���͹� �����̰� �������Ƿ� �̻��� �߻� ����. 
		data.IsMissileNeedDelay = FALSE;
	}

	return TRUE;
}


/*
	������ �ִ� �ɼ��� ���͸� �÷��̾� ������ ���ϰ� �ϴ� �Լ�.
	���� �ɼǿ� RandomRange�� ���� ���, �̻��Ͽ� ��鸲�� �����ش�.
*/
BOOL Enemy::SetOptionMissileVecToPlayer()
{
	FireOption op = GetFireOption();
	FLOAT range = op.GetRandomRange();

	// RandomRange �ɼ��� ���� ���
	if (range != 0)
	{
		// ���� �����⸦ ���� -range ~ range ������ ���� �������ش�.
		std::mt19937 rng;
		std::uniform_real_distribution<float> dist(-range, range);
		op.SetMissileVec(Vec(m_PlayerPos.x + dist(rng), m_PlayerPos.y + dist(rng)));
	}
	else
	{
		// �ƴ� ��� �׳� �÷��̾��� ��ġ�� ������ش�.
		op.SetMissileVec(Vec(m_PlayerPos.x, m_PlayerPos.y));
	}

	// ����� �ɼ����� ����.
	SetFireOption(op);

	return TRUE;
}

/*
	Ȧ�� ���� �̻����� Launch��Ű�� �Լ�.
	FireNways���� ȣ��.
*/
BOOL Enemy::LaunchOddNumberWaysMissiles()
{


	return TRUE;
}

/*
	¦�� ���� �̻����� Launch��Ű�� �Լ�.
	FireNways���� ȣ��.
*/
BOOL Enemy::LaunchEvenNumberWaysMissiles()
{

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
