#pragma once

#ifndef __CONFIG_LOADER_H__
#define __CONFIG_LOADER_H__

#include "cocos2d.h"
#include "jansson/jansson.h"

USING_NS_CC;
using namespace std;

#define CONFIG_FILE		"config.json"


class ConfigLoader
{
public:
	ConfigLoader(void);
	~ConfigLoader(void);

	static ConfigLoader* shareConfigLoader();

	const char* getStringValue(const char* key);
	int			getIntValue(const char* key);
	float		getFloatValue(const char* key);

protected:
	static ConfigLoader* s_instance;
	
private:
	json_t* m_configObject;
};


#endif //__CONFIG_LOADER_H__