#pragma once

/*
	Option을 간편하게 정의하기 위해 만들어낸 구조체.
	Option과 ID를 같이 저장한다.
*/

struct CreateOptionWithId
{
	CreateOption* opt;
	ENEMY::CREATE_OPTION id;
};

struct FireOptionWithId
{
	FireOption* opt;
	ENEMY::FIRE_OPTION id;
};

/*
	EnemyManager에서 옵션을 생성하고 만들기가 너무 귀찮고 힘들어서 만든 클래스.
	싱글턴 클래스로 옵션을 가지고 있다가, 호출하면 뱉어낸다.
	근데 이렇게 싱글턴을 많이 만들줄 알았다면 기본 클래스로 정의해두는 건데...
*/

class OptionHandler
{
public :
	static OptionHandler* GetInstance();
	void DeleteInstance();

	CreateOption* GetCreateOption();
	FireOption* GetFireOption();
	~OptionHandler();

private:
	// OptionHandler 생성자는 getInstance에서 밖에 호출되지 않는다.
	OptionHandler();

	// 싱글톤 인스턴스.
	static OptionHandler* m_pInstance;

	// 내부 함수들
	void Init();

	// 옵션 저장 풀.
	std::vector<CreateOptionWithId> m_CreateOptionVec;
	std::vector<FireOptionWithId> m_FireOptionVec;
};