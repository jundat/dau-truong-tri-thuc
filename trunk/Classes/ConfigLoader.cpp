#include "ConfigLoader.h"
#include "cocos2d.h"

USING_NS_CC;

//////////////////////////////////////////////////////////////////////////


ConfigLoader* ConfigLoader::s_instance = NULL;


ConfigLoader::ConfigLoader(void)
{
	CCLOG("-----------CONFIG------------");
	m_dict = CCDictionary::createWithContentsOfFile(CONFIG_FILE);

	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(m_dict, pElement)
	{
		CCString* val = (CCString*)pElement->getObject();
		std::string key = pElement->getStrKey();
		CCLOG("%s : %s", key.c_str(), val->getCString());
	}
	CCLOG("------------CONFIG-----------");

	//URL
	G_URL_PROFILE	= std::string(GetValue(std::string("G_URL_PROFILE"))->getCString());
	G_URL_FRIEND	= std::string(GetValue(std::string("G_URL_FRIEND"))->getCString());
	G_URL_DEVICE	= std::string(GetValue(std::string("G_URL_DEVICE"))->getCString());
	G_URL_SCORE		= std::string(GetValue(std::string("G_URL_SCORE"))->getCString());


	//////////////////////////////////////////////////////////////////////////

	//save to variant
	G_DESIGN_WIDTH	= GetValue(std::string("G_DESIGN_WIDTH"))->intValue();
	G_DESIGN_HEIGHT = GetValue(std::string("G_DESIGN_HEIGHT"))->intValue();
	G_SCALE_FACTOR	= GetValue(std::string("G_SCALE_FACTOR"))->floatValue();

	G_DEFAULT_DIAMON	= GetValue(std::string("G_DEFAULT_DIAMON"))->intValue();
	G_DIAMON_PER_LIFE	= GetValue(std::string("G_DIAMON_PER_LIFE"))->intValue();
	G_TIME_TO_REFRESH_FRIENDS	= GetValue(std::string("G_TIME_TO_REFRESH_FRIENDS"))->floatValue();	
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

const CCString* ConfigLoader::GetValue(const std::string key )
{
	const CCString* val = m_dict->valueForKey(key);
	if (val->length() == 0)
	{
		CCLOG("NOT A VALID KEY CONFIG: %s", key.c_str());
		return CCStringMake("NULL_STRING");
	}

	return val;
}
