#include "stdafx.h"
#include "OptionHandler.h"

OptionHandler* OptionHandler::m_pInstance = nullptr;

// OptionHandler 싱글톤 구현.
OptionHandler* OptionHandler::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new OptionHandler();
	}
	return m_pInstance;
}

// 싱글톤 삭제 함수.
void OptionHandler::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

/*
	생성자. init호출.
*/
OptionHandler::OptionHandler()
{
	Init();
}

/*
	소멸자. deleteInstance 호출.
*/
OptionHandler::~OptionHandler()
{
	DeleteInstance();
}

/*
	초기화 함수.
*/
void OptionHandler::Init()
{

	return;
}

