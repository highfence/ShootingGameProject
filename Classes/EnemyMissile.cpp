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
	�Լ� �����͸� ��Ͻ����ִ� �Լ�.
*/
void EnemyMissile::RegisterFunctionPointer()
{
	m_pMissileFlyHandler[MISSILE_TYPE::STRAIGHT_FIRE] = &EnemyMissile::MissileFlyNormal;
	m_pMissileFlyHandler[MISSILE_TYPE::ACCELERATE_FIRE] = &EnemyMissile::MissileAccelerate;
	m_pMissileFlyHandler[MISSILE_TYPE::CIRCLE_TYPE] = &EnemyMissile::MissileCircle;
	return;
}

/*
	FireOption�� ��ϵǾ��ִ´�� �����ϰ� ���ư��� �̻���.
*/
BOOL EnemyMissile::MissileFlyNormal(const FLOAT deltaTime)
{
	FireOption op = GetOption();
	Vec missileVec = op.GetMissileVec();
	Fly(deltaTime, missileVec.x, missileVec.y, op.GetMissileSpeed());

	return TRUE;
}

/*
	�����ϰ� ��/���� �ϴ� ��Ÿ���� �̻���.
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
	ȸ��ź�� �������� �����ϴ� �̻���.
*/
BOOL EnemyMissile::MissileCircle(const FLOAT dt)
{
	FireOption opt = GetOption();
	CircleShotData data = opt.GetCircleShotData();
	
	// ���� ���Ϳ� speed�� �̿��Ͽ� �̵��Ÿ� ���.
	FLOAT flyDistance = m_AccTime * opt.GetMissileSpeed();
	
	// �̵��Ÿ��� ���� ������� �ʴٸ� (Radius �̸��̶��) Fly����.
	if (flyDistance < data.Radius)
	{
		MissileFlyNormal(dt);
	}
	// ����ϴٸ� ȸ�� � ����. RecordRotateTime�� �ð� ����.
	else if (data.RecordRotateTime < data.RotateTime)
	{
		MoveLoopingBullet(dt, opt, data);
		data.RecordRotateTime += dt;
	}
	// RecordRotateTime�� �Ѿ�� �߽ɿ��� ���� ��ġ���� ���ͷ� ����.
	else
	{
		Vec oppositeVec;
		oppositeVec.x = m_Pos.x - data.CenterPos.x;
		oppositeVec.y = m_Pos.y - data.CenterPos.y;
		opt.SetMissileVec(oppositeVec);
		SetFireOption(opt);
		MissileFlyNormal(dt);
	}

	// ������� ����.
	opt.SetCircleShotData(data);
	SetFireOption(opt);
	return TRUE;
}

/*
	�������� �̻����� ���������ִ� �Լ�.
*/
void EnemyMissile::MoveLoopingBullet(const FLOAT dt, FireOption& opt, CircleShotData& data)
{
	// ���� ���� ���.
	FLOAT currentRotateAngle = (data.InitRotateAnglePerSec + data.AccRotateAnglePerSec * data.RecordRotateTime) * dt;

	// ���� ������ Max���� �Ѿ�� Max������ ����.
	if (currentRotateAngle > data.MaxRotateAngelPerSec)
	{
		currentRotateAngle = data.MaxRotateAngelPerSec;
	}

	// ���� ��ȯ.
	FLOAT currentRotateRadian = currentRotateAngle * M_PI / 180;

	// ���� �̵�.
	data.Theta += currentRotateRadian;
	data.Theta = fmod(data.Theta, 2 * M_PI);

	// �̵���Ų ������ ���� ��ǥ ��ȯ.
	Vec MoveOnVec;
	m_Pos.x = data.CenterPos.x + data.Radius * cos(data.Theta);
	m_Pos.y = data.CenterPos.y + data.Radius * sin(data.Theta);

	// ������� ����.
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
	// �̻����� ���� �߻���� ���� ��� �ٷ� ����.
	if (!m_IsMissileLaunched)
	{
		return;
	}

	// �ð� ����
	m_AccTime += deltaTime;

	// �浹 �˻�.
	CheckColideWithPlayer();

	// �ɼ� ȣ�� �� �̻��� ��� �ٷ� ����.
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

// EnemyMissile���� Player�� ��ġ ������ �˷��ִ� �Լ�. (�浹 ������ ����)
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
	//// ��ǥ ���.
	//std::wstring debugLabel = std::to_wstring((int)m_Pos.x) + _T(", ") + std::to_wstring((int)m_Pos.y);
	//TextOut(drawDC, m_Pos.x, m_Pos.y, debugLabel.c_str(), wcslen(debugLabel.c_str()));

	//// ���� ������ ���.
	//auto data = GetOption().GetCircleShotData();
	//Vec centerPos = data.CenterPos;
	//auto theta = data.Theta;
	//debugLabel = std::to_wstring(centerPos.x) + _T(", ") + std::to_wstring(centerPos.y);
	//TextOut(drawDC, centerPos.x, centerPos.y, debugLabel.c_str(), wcslen(debugLabel.c_str()));
	//debugLabel = std::to_wstring(theta);
	//TextOut(drawDC, centerPos.x, centerPos.y + 15, debugLabel.c_str(), wcslen(debugLabel.c_str()));

	//// �� ���.
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
	�̻����� ���¸� �ʱ�ȭ�����ִ� �Լ�.
	�̻����� ȭ�� ������ �����ų� �÷��̾�� �浹���� ��� ȣ�����ش�.
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
