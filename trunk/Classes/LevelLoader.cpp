#include "LevelLoader.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

//cd_catalog.xml
CCString* LevelLoader::s_levelFile = CCStringMake("level.csv");
LevelLoader* LevelLoader::s_instance = NULL;

LevelLoader::LevelLoader(void)
{
	CCDictionary* theDict = CCDictionary::createWithContentsOfFile("questions.plist");
	
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(theDict, pElement)
	{
		CCLOG("----");
		CCDictionary* question = (CCDictionary*)pElement->getObject();

		std::string count = pElement->getStrKey();
		CCLOG("Quest: %s", count.c_str());

		CCString* quest = (CCString*)question->objectForKey("quest");
		CCLOG("%s", quest->m_sString.c_str());

		CCString* a = (CCString*)question->objectForKey("a");
		CCLOG("%s", a->getCString());

		CCString* b = (CCString*)question->objectForKey("b");
		CCLOG("%s", b->getCString());

		CCString* c = (CCString*)question->objectForKey("c");
		CCLOG("%s", c->getCString());

		CCString* d = (CCString*)question->objectForKey("d");
		CCLOG("%s", d->getCString());

		CCString* answer = (CCString*)question->objectForKey("answer");
		CCLOG("%s", answer->getCString());
	}
}

LevelLoader* LevelLoader::shareLevelLoader()
{
	if (s_instance == NULL)
	{
		s_instance = new LevelLoader();
	}
	
	return s_instance;
}

LevelData* LevelLoader::GetValueLowerThan( int keyScore )
{
	return (LevelData*)m_dict->objectForKey(keyScore);
}
