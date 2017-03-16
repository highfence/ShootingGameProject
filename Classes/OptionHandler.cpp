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

