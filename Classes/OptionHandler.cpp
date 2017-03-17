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
	CreateOption 아이디를 넣으면 그에 해당하는 옵션의 참조자를 반환해주는 함수.
*/
CreateOption & OptionHandler::GetCreateOption(const ENEMY::CREATE_OPTION createOptionId)
{
	auto iter = m_CreateOptionMap.find(createOptionId); 
	return (*iter).second.GetOption();
}

/*
	FireOption 아이디를 넣으면 그에 해당하는 옵션의 참조자를 반환해주는 함수.
*/
FireOption & OptionHandler::GetFireOption(const ENEMY::FIRE_OPTION fireOptionId)
{
	auto iter = m_FireOptionMap.find(fireOptionId);
	return (*iter).second.GetOption();
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
