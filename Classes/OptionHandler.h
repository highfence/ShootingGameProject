#pragma once

/*
	Option�� �����ϰ� �����ϱ� ���� ���� ����ü.
	Option�� ID�� ���� �����Ѵ�.
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
	EnemyManager���� �ɼ��� �����ϰ� ����Ⱑ �ʹ� ������ ���� ���� Ŭ����.
	�̱��� Ŭ������ �ɼ��� ������ �ִٰ�, ȣ���ϸ� ����.
	�ٵ� �̷��� �̱����� ���� ������ �˾Ҵٸ� �⺻ Ŭ������ �����صδ� �ǵ�...
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
	// OptionHandler �����ڴ� getInstance���� �ۿ� ȣ����� �ʴ´�.
	OptionHandler();

	// �̱��� �ν��Ͻ�.
	static OptionHandler* m_pInstance;

	// ���� �Լ���
	void Init();

	// �ɼ� ���� Ǯ.
	std::vector<CreateOptionWithId> m_CreateOptionVec;
	std::vector<FireOptionWithId> m_FireOptionVec;
};