#pragma once

#ifndef __CONFIG_LOADER_H__
#define __CONFIG_LOADER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "jansson/jansson.h"
#include "HttpClient.h"
#include "GameClientManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define CONFIG_FILE		"config.json"


#define CONF_BOOL(config)		(ConfigLoader::shareConfigLoader()->getBoolValue(#config))
#define CONF_INT(config)		(ConfigLoader::shareConfigLoader()->getIntValue(#config))
#define CONF_FLOAT(config)		(ConfigLoader::shareConfigLoader()->getFloatValue(#config))
#define CONF_STR(config)		(ConfigLoader::shareConfigLoader()->getStringValue(#config))


class ConfigLoader : public CCObject
{
public:
	ConfigLoader(void);
	~ConfigLoader(void);

	static ConfigLoader* shareConfigLoader();

	void		getConfigFromServer();
	const char* getStringValue(const char* key);
	int			getIntValue(const char* key);
	float		getFloatValue(const char* key);
	bool		getBoolValue( const char* key );

private:
	void _onGetConfigCompleted( CCHttpClient *sender, CCHttpResponse *response );

protected:
	static ConfigLoader* s_instance;
	
private:
	json_t* m_clientConfigObject;
	json_t* m_serverConfigObject;
};


#endif //__CONFIG_LOADER_H__