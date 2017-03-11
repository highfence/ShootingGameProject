#pragma once

/*
	Enemy의 Missile 생성시에 들어갈 정보를 담는 클래스.
*/

class FireOption
{
public :
	FireOption(
		const _In_ ENEMY::FIRE_TYPE fireType,
		const _In_ ENEMY::MISSILE_TYPE missileType,
		const _In_ ENEMY::MISSILE_SIZE missileSize,
		const _In_ FLOAT missileSpeed,
		const _In_ FLOAT accMissileSpeed,
		const _In_ FLOAT waitingTime,
		const _In_ Vec missileVec);
	FireOption(const _In_ std::nullptr_t);
	FireOption();
	~FireOption();

	FireOption& operator=(const _In_ FireOption);

	/*
		Getter, Setter
	*/
	BOOL GetIsOptionCanUse() const;
	ENEMY::FIRE_TYPE GetFireType() const;
	ENEMY::MISSILE_TYPE GetMissileType() const;
	ENEMY::MISSILE_SIZE GetMissileSize() const;
	FLOAT GetMissileSpeed() const;
	FLOAT GetAccMissileSpeed() const;
	FLOAT GetWaitingTime() const;
	Vec GetMissileVec() const;

	void SetFireType(const _In_ ENEMY::FIRE_TYPE);
	void SetMissileType(const _In_ ENEMY::MISSILE_TYPE);
	void SetMissileSize(const _In_ ENEMY::MISSILE_SIZE);
	void SetMissileSpeed(const _In_ FLOAT);
	void SetAccMissileSpeed(const _In_ FLOAT);
	void SetWaitingTime(const _In_ FLOAT);
	void SetMissileVec(const _In_ Vec);

private :

	/*
		IsOptionCanUse에 대한 여부를 외부에서 지정할 수 없도록 Setter를 만들지 않는다.	
	*/
	BOOL m_IsOptionCanUse;
	ENEMY::FIRE_TYPE m_FireType;
	ENEMY::MISSILE_TYPE m_MissileType;
	ENEMY::MISSILE_SIZE m_MissileSize;
	FLOAT m_MissileSpeed;
	FLOAT m_AccMissileSpeed;
	FLOAT m_WaitingTime;
	Vec m_MissileVec;
};