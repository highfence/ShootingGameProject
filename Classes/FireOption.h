#pragma once

/*
	Enemy의 Missile 생성시에 들어갈 정보를 담는 클래스.
*/

class FireOption
{
public :
	FireOption();
	FireOption(
		const _In_ ENEMY::FIRE_TYPE fireType,
		const _In_ ENEMY::MISSILE_TYPE missileType,
		const _In_ ENEMY::MISSILE_SIZE missileSize,
		const _In_ FLOAT missileSpeed,
		const _In_ FLOAT accMissileSpeed,
		const _In_ FLOAT waitingTime,
		const _In_ Vec missileVec);
	~FireOption();

	FireOption& operator=(const _In_ FireOption);

	/*
		Getter, Setter
	*/
	BOOL getIsOptionCanUse() const;
	ENEMY::FIRE_TYPE getFireType() const;
	ENEMY::MISSILE_TYPE getMissileType() const;
	ENEMY::MISSILE_SIZE getMissileSize() const;
	FLOAT getMissileSpeed() const;
	FLOAT getAccMissileSpeed() const;
	FLOAT getWaitingTime() const;
	Vec getMissileVec() const;

	void setFireType(const _In_ ENEMY::FIRE_TYPE);
	void setMissileType(const _In_ ENEMY::MISSILE_TYPE);
	void setMissileSize(const _In_ ENEMY::MISSILE_SIZE);
	void setMissileSpeed(const _In_ FLOAT);
	void setAccMissileSpeed(const _In_ FLOAT);
	void setWaitingTime(const _In_ FLOAT);
	void setMissileVec(const _In_ Vec);

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