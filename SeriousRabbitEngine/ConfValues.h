#pragma once
#include "Single.h"
#include <string>

class ConfValues :public Single < ConfValues >
{

public:
	std::string GetConfigValue(std::string key)  //��config/settings.json�ж�ȡvalue��keyһ����Դ��ConstValues.h�ļ��ľ�̬����
	{
		
		return nullptr;
	}

	void SetConfigValue(std::string key,std::string value)//����config/settings.json��KV
	{
	
	}

};
ConfValues* ConfValues::instance = nullptr;

