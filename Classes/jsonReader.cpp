#include "stdafx.h"
#include "jsonReader.h"

JsonReader* JsonReader::m_pInstance = nullptr;

JsonReader* JsonReader::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new JsonReader;
	}
	return m_pInstance;
}

void JsonReader::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
	return;
}

JsonReader::JsonReader()
{

}


JsonReader::~JsonReader()
{

}
