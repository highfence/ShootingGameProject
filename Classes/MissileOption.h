#pragma once

/*
	Enemy�� Missile �����ÿ� �� ������ ��� Ŭ����.
*/

class MissileOption
{
public :
	MissileOption(
		const _In_opt_ Vec missileVec,
		const _In_opt_ FLOAT missileSpeed,
		const _In_opt_ ENEMY::MISSILE_TYPE missileType,
		const _In_opt_ ENEMY::MISSILE_SIZE missileSize);
	MissileOption(const _In_ std::nullptr_t);
	MissileOption();
	~MissileOption();

	BOOL IsOptionCanUse() const;

	MissileOption& operator=(const _In_ MissileOption);
	Vec m_MissileVec;
	FLOAT m_MissileSpeed;
	ENEMY::MISSILE_TYPE m_MissileType;
	ENEMY::MISSILE_SIZE m_MissileSize;
	BOOL m_IsOptionCanUse;

};