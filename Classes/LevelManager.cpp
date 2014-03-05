#include "LevelManager.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

LevelManager* LevelManager::s_instance = NULL;


LevelManager::LevelManager(void)
{
	m_dict = CCDictionary::createWithContentsOfFile(LEVEL_FILE);
	m_dict->retain();
	
// 	CCDictElement* pElement = NULL;
// 	CCDICT_FOREACH(theDict, pElement)
// 	{
// 		CCLOG("----");
// 		CCDictionary* question = (CCDictionary*)pElement->getObject();
// 
// 		std::string count = pElement->getStrKey();
// 		CCLOG("Quest: %s", count.c_str());
// 
// 		CCString* quest = (CCString*)question->objectForKey("quest");
// 		CCLOG("%s", quest->m_sString.c_str());
// 
// 		CCString* a = (CCString*)question->objectForKey("a");
// 		CCLOG("%s", a->getCString());
// 
// 		CCString* b = (CCString*)question->objectForKey("b");
// 		CCLOG("%s", b->getCString());
// 
// 		CCString* c = (CCString*)question->objectForKey("c");
// 		CCLOG("%s", c->getCString());
// 
// 		CCString* d = (CCString*)question->objectForKey("d");
// 		CCLOG("%s", d->getCString());
// 
// 		CCString* answer = (CCString*)question->objectForKey("answer");
// 		CCLOG("%s", answer->getCString());
// 	}
}

LevelManager* LevelManager::shareLevelLoader()
{
	if (s_instance == NULL)
	{
		s_instance = new LevelManager();
	}
	
	return s_instance;
}

LevelData* LevelManager::getLevel( int level )
{
	string sLevel = CCString::createWithFormat("%d", level)->getCString();
	CCDictionary* question = (CCDictionary*)m_dict->objectForKey(sLevel);
	
	if (question != NULL)
	{
		string quest = ((CCString*)question->objectForKey("quest"))->getCString();
		string a = ((CCString*)question->objectForKey("a"))->getCString();
		string b = ((CCString*)question->objectForKey("b"))->getCString();
		string c = ((CCString*)question->objectForKey("c"))->getCString();
		string d = ((CCString*)question->objectForKey("d"))->getCString();
		int answer = ((CCString*)question->objectForKey("answer"))->intValue();

		LevelData* ld = LevelData::create(quest, a, b, c, d, answer);
		return ld;
	} 
	else
	{
		return NULL;
	}
}
