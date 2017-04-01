#include "stdafx.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EnemyMissile.h"

using namespace ENEMY;

EnemyMissile::EnemyMissile(ENEMY::MISSILE_SIZE missileSize)
{
	if (missileSize == ENEMY::MISSILE_SIZE::SMALL)
	{
		m_pSprite->Load(enemyMissileSmall.c_str());
		m_pShapeSprite->Load(enemyMissileShadeSmall.c_str());
		m_Width = enemyMissileSmallWidth;
		m_Height = enemyMissileSmallHeight;
	}
	else if (missileSize == ENEMY::MISSILE_SIZE::MEDIUM)
	{
		m_pSprite->Load(enemyMissileMedium.c_str());
		m_pShapeSprite->Load(enemyMissileShadeMedium.c_str());
		m_Width = enemyMissileMediumWidth;
		m_Height = enemyMissileMediumHeight;
	}
	else if (missileSize == ENEMY::MISSILE_SIZE::LARGE)
	{
		m_pSprite->Load(enemyMissileLarge.c_str());
		m_pShapeSprite->Load(enemyMissileShadeLarge.c_str());
		m_Width = enemyMissileLargeWidth;
		m_Height = enemyMissileLargeHeight;
	}
	init();
	return;
}

void EnemyMissile::init()
{
	RegisterFunctionPointer();
	return;
}

/*
	함수 포인터를 등록시켜주는 함수.
*/
void EnemyMissile::RegisterFunctionPointer()
{
	m_pMissileFlyHandler[MISSILE_TYPE::STRAIGHT_FIRE] = &EnemyMissile::MissileFlyNormal;
	m_pMissileFlyHandler[MISSILE_TYPE::ACCELERATE_FIRE] = &EnemyMissile::MissileAccelerate;
	m_pMissileFlyHandler[MISSILE_TYPE::CIRCLE_TYPE] = &EnemyMissile::MissileCircle;
	return;
}

/*
	FireOption에 등록되어있는대로 일정하게 날아가는 미사일.
*/
BOOL EnemyMissile::MissileFlyNormal(const FLOAT deltaTime)
{
	FireOption op = GetOption();
	Vec missileVec = op.GetMissileVec();
	Fly(deltaTime, missileVec.x, missileVec.y, op.GetMissileSpeed());

	return TRUE;
}

/*
	일정하게 가/감속 하는 스타일의 미사일.
*/
BOOL EnemyMissile::MissileAccelerate(const FLOAT deltaTime)
{
	FireOption opt = GetOption();
	Vec missileVec = opt.GetMissileVec();
	FLOAT initSpeed = opt.GetMissileSpeed();
	FLOAT accSpeed = opt.GetAccMissileSpeed();
	FLOAT currentSpeed = initSpeed + accSpeed * m_AccTime;
	Fly(deltaTime, missileVec.x, missileVec.y, currentSpeed);
	
	return TRUE;
}

/*
	회전탄의 움직임을 구현하는 미사일.
*/
BOOL EnemyMissile::MissileCircle(const FLOAT dt)
{
	FireOption opt = GetOption();
	CircleShotData data = opt.GetCircleShotData();
	
	// 진행 벡터와 speed를 이용하여 이동거리 계산.
	FLOAT flyDistance = m_AccTime * opt.GetMissileSpeed();
	
	// 이동거리가 아직 충분하지 않다면 (Radius 미만이라면) Fly진행.
	if (flyDistance < data.Radius)
	{
		MissileFlyNormal(dt);
	}
	// 충분하다면 회전 운동 진행. RecordRotateTime에 시간 누적.
	else if (data.RecordRotateTime < data.RotateTime)
	{
		MoveLoopingBullet(dt, opt, data);
		data.RecordRotateTime += dt;
	}
	// RecordRotateTime이 넘어가면 중심에서 현재 위치로의 벡터로 진행.
	else
	{
		Vec oppositeVec;
		oppositeVec.x = m_Pos.x - data.CenterPos.x;
		oppositeVec.y = m_Pos.y - data.CenterPos.y;
		opt.SetMissileVec(oppositeVec);
		SetFireOption(opt);
		MissileFlyNormal(dt);
	}

	// 변경사항 저장.
	opt.SetCircleShotData(data);
	SetFireOption(opt);
	return TRUE;
}

/*
	원형으로 미사일을 루프시켜주는 함수.
*/
void EnemyMissile::MoveLoopingBullet(const FLOAT dt, FireOption& opt, CircleShotData& data)
{
	// 도는 각도 계산.
	FLOAT currentRotateAngle = (data.InitRotateAnglePerSec + data.AccRotateAnglePerSec * data.RecordRotateTime) * dt;

	// 도는 각도가 Max값을 넘어가면 Max값으로 고정.
	if (currentRotateAngle > data.MaxRotateAngelPerSec)
	{
		currentRotateAngle = data.MaxRotateAngelPerSec;
	}

	// 라디안 변환.
	FLOAT currentRotateRadian = currentRotateAngle * M_PI / 180;

	// 각도 이동.
	data.Theta += currentRotateRadian;
	data.Theta = fmod(data.Theta, 2 * M_PI);

	// 이동시킨 각도에 따라 좌표 변환.
	Vec MoveOnVec;
	m_Pos.x = data.CenterPos.x + data.Radius * cos(data.Theta);
	m_Pos.y = data.CenterPos.y + data.Radius * sin(data.Theta);

	// 변경사항 저장.
	opt.SetCircleShotData(data);
	return;
}

BOOL EnemyMissile::CheckColideWithPlayer()
{
	Player& playerInfo = EnemyManager::GetInstance()->getPlayerInfo();
	FLOAT playerCorrectionPixel = playerInfo.GetCollisionPixel();
	Vec playerPos;
	playerInfo.GetPosition(&playerPos);

	auto x0 = m_Pos.x - m_Width / 2;
	auto y0 = m_Pos.y - m_Height / 2;
	auto x1 = m_Pos.x + m_Width / 2;
	auto y1 = m_Pos.y + m_Height / 2;
	auto mx0 = playerPos.x - playerCorrectionPixel;
	auto my0 = playerPos.y - playerCorrectionPixel;
	auto mx1 = playerPos.x + playerCorrectionPixel;
	auto my1 = playerPos.y + playerCorrectionPixel;

	if (!(x1 <= mx0 || mx1 <= x0 || y1 <= my0 || my1 <= y0))
	{
		playerInfo.PlayerDamaged(m_Option.GetMissileVec());
		MakeMissileInitialState();
		return TRUE;
	}
	return FALSE;
}

EnemyMissile::~EnemyMissile()
{

}

void EnemyMissile::CalcProc(const FLOAT deltaTime)
{
	// 미사일이 아직 발사되지 않은 경우 바로 리턴.
	if (!m_IsMissileLaunched)
	{
		return;
	}

	// 시간 누적
	m_AccTime += deltaTime;

	// 충돌 검사.
	CheckColideWithPlayer();

	// 옵션 호출 및 이상할 경우 바로 리턴.
	FireOption op = GetOption();
	if (!op.GetIsOptionCanUse())
	{
		return;
	}

	(this->*m_pMissileFlyHandler[op.GetMissileType()])(deltaTime);
	return;
}

void EnemyMissile::Fly(
	const _In_ FLOAT dt,
	const _In_ FLOAT vecX,
	const _In_ FLOAT vecY,
	const _In_ FLOAT speed)
{
	if (!m_IsMissileLaunched)
	{
		return;
	}

	FLOAT unitVecX;
	FLOAT unitVecY;

	GetUnitVec(vecX, vecY, &unitVecX, &unitVecY);

	m_Pos.x += unitVecX * speed * dt;
	m_Pos.y += unitVecY * speed * dt;

	if (!IsMissileOnDisplay())
	{
		m_IsMissileLaunched = FALSE;
	}

	return;
}

// EnemyMissile에게 Player의 위치 정보를 알려주는 함수. (충돌 판정을 위해)
void EnemyMissile::SetPlayerPos(
	const _In_ FLOAT playerPosX,
	const _In_ FLOAT playerPosY)
{
	m_PlayerPosX = playerPosX;
	m_PlayerPosY = playerPosY;

	return;
}

void EnemyMissile::Draw(const HDC drawDC)
{
	if (!m_IsMissileLaunched)
	{
		return;
	}

#pragma warning(push)
#pragma warning(disable : 4244)


#ifdef _DEBUG
	//// 좌표 출력.
	//std::wstring debugLabel = std::to_wstring((int)m_Pos.x) + _T(", ") + std::to_wstring((int)m_Pos.y);
	//TextOut(drawDC, m_Pos.x, m_Pos.y, debugLabel.c_str(), wcslen(debugLabel.c_str()));

	//// 센터 포지션 출력.
	//auto data = GetOption().GetCircleShotData();
	//Vec centerPos = data.CenterPos;
	//auto theta = data.Theta;
	//debugLabel = std::to_wstring(centerPos.x) + _T(", ") + std::to_wstring(centerPos.y);
	//TextOut(drawDC, centerPos.x, centerPos.y, debugLabel.c_str(), wcslen(debugLabel.c_str()));
	//debugLabel = std::to_wstring(theta);
	//TextOut(drawDC, centerPos.x, centerPos.y + 15, debugLabel.c_str(), wcslen(debugLabel.c_str()));

	//// 선 출력.
	//MoveToEx(drawDC, centerPos.x, centerPos.y, NULL);
	//LineTo(drawDC, m_Pos.x, m_Pos.y);
#endif

	m_pShapeSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCAND);

	m_pSprite->BitBlt(drawDC, m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2,
		m_Width, m_Height, 0, 0, SRCPAINT);

#pragma warning(pop)
	return;
}

/*
	Initialize with MissileOption (Launch Func Overloading)
	Using in EnemyMissile
*/
BOOL EnemyMissile::Launch(
	const _In_ Vec createVec,
	const _In_ FireOption& option)
{
	if (m_IsMissileLaunched)
	{
		return FALSE;
	}

	m_IsMissileLaunched = TRUE;
	m_Pos = createVec;
	m_Option = option;
	m_MissileType = option.GetMissileType();

	return TRUE;
}

BOOL EnemyMissile::IsMissileOnDisplay()
{
	if (m_Pos.y < -m_Height)
	{
		MakeMissileInitialState();
		return FALSE;
	}
	else if (m_Pos.x < -m_Width)
	{
		MakeMissileInitialState();
		return FALSE;
	}
	else if (m_Pos.x > winWidth + m_Width)
	{
		MakeMissileInitialState();
		return FALSE;
	}
	else if (m_Pos.y > winHeight + m_Height)
	{
		MakeMissileInitialState();
		return FALSE;
	}

	return TRUE;
}


/*
	미사일의 상태를 초기화시켜주는 함수.
	미사일이 화면 밖으로 나갔거나 플레이어와 충돌했을 경우 호출해준다.
*/
const FLOAT savePlacePos = -300.f;
void EnemyMissile::MakeMissileInitialState()
{
	m_Pos = Vec(savePlacePos, savePlacePos);
	//m_Option = nullptr;
}

FireOption EnemyMissile::GetOption() const
{
	return m_Option;
}

void EnemyMissile::SetFireOption(const FireOption & op)
{
	m_Option = op;
}
