#pragma once


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

	CreateOption* GetCreateOption(const _In_ ENEMY::CREATE_OPTION);
	FireOption* GetFireOption(const _In_ ENEMY::FIRE_OPTION);
	~OptionHandler();

private:
	// OptionHandler 생성자는 getInstance에서 밖에 호출되지 않는다.
	OptionHandler();

	// 싱글톤 인스턴스.
	static OptionHandler* m_pInstance;

	// 내부 함수들
	void Init();

	// 옵션 저장 풀.
	std::unordered_map<ENEMY::CREATE_OPTION, CreateOption> m_CreateOptionMap;
	std::unordered_map<ENEMY::FIRE_OPTION, FireOption> m_FireOptionMap;
};