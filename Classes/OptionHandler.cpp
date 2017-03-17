#include "stdafx.h"
#include "OptionHandler.h"

OptionHandler* OptionHandler::m_pInstance = nullptr;

// OptionHandler �̱��� ����.
OptionHandler* OptionHandler::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new OptionHandler();
	}
	return m_pInstance;
}

// �̱��� ���� �Լ�.
void OptionHandler::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

/*
	CreateOption ���̵� ������ �׿� �ش��ϴ� �ɼ��� �����ڸ� ��ȯ���ִ� �Լ�.
*/
CreateOption & OptionHandler::GetCreateOption(const ENEMY::CREATE_OPTION createOptionId)
{
	auto iter = m_CreateOptionMap.find(createOptionId); 
	return (*iter).second.GetOption();
}

/*
	FireOption ���̵� ������ �׿� �ش��ϴ� �ɼ��� �����ڸ� ��ȯ���ִ� �Լ�.
*/
FireOption & OptionHandler::GetFireOption(const ENEMY::FIRE_OPTION fireOptionId)
{
	auto iter = m_FireOptionMap.find(fireOptionId);
	return (*iter).second.GetOption();
}

/*
	������. initȣ��.
*/
OptionHandler::OptionHandler()
{
	Init();
}

/*
	�Ҹ���. deleteInstance ȣ��.
*/
OptionHandler::~OptionHandler()
{
	DeleteInstance();
}

/*
	�ʱ�ȭ �Լ�.
*/
void OptionHandler::Init()
{

	return;
}
