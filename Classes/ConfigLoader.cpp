#include "ConfigLoader.h"
#include "cocos2d.h"
#include "Global.h"
#include "DataManager.h"

USING_NS_CC;
using namespace std;

ConfigLoader* ConfigLoader::s_instance = NULL;


ConfigLoader::ConfigLoader(void)
{
	CCLOG("----------- READ CONFIG FROM FILE: BEGIN ------------");

	//JSON
	string s = string(CCString::createWithContentsOfFile(CONFIG_FILE)->getCString());
	CCLOG("%s", s.c_str());
	json_error_t error;

	m_clientConfigObject = json_loads(s.c_str(), strlen(s.c_str()), &error);

	CCLOG("----------- READ CONFIG FROM FILE: END ------------");
}

ConfigLoader::~ConfigLoader(void)
{
}

ConfigLoader* ConfigLoader::shareConfigLoader()
{
	if (s_instance == NULL)
	{
		s_instance = new ConfigLoader();
	}
	
	return s_instance;
}


void ConfigLoader::getConfigFromServer()
{
	CCLOG("--------- GET CONFIG FROM SERVER: BEGIN -----------");

	string url_config = CONF_STR(URL_CONFIG);
	GameClientManager::sharedGameClientManager()->sendRequest(url_config.c_str(), this, httpresponse_selector(ConfigLoader::_onGetConfigCompleted), "data={}&method=get");

	CCLOG("---------- GET CONFIG FROM SERVER: END ------------");
}

const char* ConfigLoader::getStringValue(const char* key)
{
	json_t* jsonValue = json_object_get(m_clientConfigObject, key);
	CCAssert(json_is_string(jsonValue), "Could not file config STRING");

	return json_string_value(jsonValue);
}

int ConfigLoader::getIntValue( const char* key )
{
	json_t* jsonValue = json_object_get(m_clientConfigObject, key);
	CCAssert(json_is_number(jsonValue), "Could not file config INT");

	return (int)json_number_value(jsonValue);
}

float ConfigLoader::getFloatValue( const char* key )
{
	json_t* jsonValue = json_object_get(m_clientConfigObject, key);
	CCAssert(json_is_number(jsonValue), "Could not file config FLOAT");

	return (float)json_number_value(jsonValue);
}

bool ConfigLoader::getBoolValue( const char* key )
{
	json_t* jsonValue = json_object_get(m_clientConfigObject, key);

	CCAssert(json_is_boolean(jsonValue), "Could not file config BOOL");
	
	if (json_is_true(jsonValue))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ConfigLoader::_onGetConfigCompleted( CCHttpClient *sender, CCHttpResponse *response )
{
	/*
	"{
		version: "1.0",
		winScore: 3,
		loseScore: -1,
		diamondForSkip: 3,
		diamondForExplusive: 1,
		diamondForInfinite: 1,
		connectionTimeout: 10 // second
	}"
	*/

	if (!response)
	{
		return;
	}

	//Show info
	CCLOG("---BEGIN GET CONFIG FROM SERVER---");
	CCLOG("Status: [%i]", response->getResponseCode());

	if (!response->isSucceed())
	{
		CCLOG("Request failed: %s", response->getErrorBuffer());
	}
	else
	{
		std::vector<char> *buffer = response->getResponseData();
		std::string str(buffer->begin(), buffer->end());

		CCLOG("Content: %s", str.c_str());

		json_error_t error;

		json_t *version;
		json_t *winScore;
		json_t *loseScore;
		json_t *diamondForSkip;
		json_t *diamondForExplusive;
		json_t *diamondForInfinite;
		json_t *connectionTimeout;

		m_serverConfigObject = json_loads(str.c_str(), strlen(str.c_str()), &error);

		//-------------------
		//get

		version = json_object_get(m_serverConfigObject, "version");
		winScore = json_object_get(m_serverConfigObject, "winScore");
		loseScore = json_object_get(m_serverConfigObject, "loseScore");
		diamondForSkip = json_object_get(m_serverConfigObject, "diamondForSkip");
		diamondForExplusive = json_object_get(m_serverConfigObject, "diamondForExplusive");
		diamondForInfinite = json_object_get(m_serverConfigObject, "diamondForInfinite");
		connectionTimeout = json_object_get(m_serverConfigObject, "connectionTimeout");

		//-------------------
		//show

		CCLOG("version: %s", json_string_value(version));
		CCLOG("winScore: %d", (int)json_number_value(winScore));
		CCLOG("loseScore: %d", (int)json_number_value(loseScore));
		CCLOG("diamondForSkip: %d", (int)json_number_value(diamondForSkip));
		CCLOG("diamondForExplusive: %d", (int)json_number_value(diamondForExplusive));
		CCLOG("diamondForInfinite: %d", (int)json_number_value(diamondForInfinite));
		CCLOG("connectionTimeout: %d", (int)json_number_value(connectionTimeout));

		//-------------------
		//save

		DataManager::sharedDataManager()->SetSoloAddScore((int)json_number_value(winScore));
		DataManager::sharedDataManager()->SetSoloSubScore((int)json_number_value(loseScore));
		DataManager::sharedDataManager()->SetDiamondForSkip((int)json_number_value(diamondForSkip));
		DataManager::sharedDataManager()->SetDiamondForInfinite((int)json_number_value(diamondForInfinite));
		DataManager::sharedDataManager()->SetDiamondForExclusive((int)json_number_value(diamondForExplusive));
		
		//...
	}
	CCLOG("---END GET CONFIG FROM SERVER---");
}