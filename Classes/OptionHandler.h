#pragma once


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

	CreateOption* GetCreateOption(const _In_ ENEMY::CREATE_OPTION);
	FireOption* GetFireOption(const _In_ ENEMY::FIRE_OPTION);
	~OptionHandler();

private:
	// OptionHandler �����ڴ� getInstance���� �ۿ� ȣ����� �ʴ´�.
	OptionHandler();

	// �̱��� �ν��Ͻ�.
	static OptionHandler* m_pInstance;

	// ���� �Լ���
	void Init();

	// �ɼ� ���� Ǯ.
	std::unordered_map<ENEMY::CREATE_OPTION, CreateOption> m_CreateOptionMap;
	std::unordered_map<ENEMY::FIRE_OPTION, FireOption> m_FireOptionMap;
};