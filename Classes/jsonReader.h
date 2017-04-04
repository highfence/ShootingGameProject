#pragma once

class JsonReader
{
public :
	JsonReader* GetInstance();
	void DeleteInstance();
	


private :
	JsonReader();
	~JsonReader();

	static JsonReader* m_pInstance;

};