#include "LevelManager.h"
#include "cocos2d.h"
#include "jansson/jansson.h"

USING_NS_CC;
using namespace std;

LevelManager* LevelManager::s_instance = NULL;


LevelManager::LevelManager(void)
{
	CCLOG("--------- LEVEL LOAD BEGIN ---------");
	m_dict = CCDictionary::create();
	m_dict->retain();

	//JSON
	CCString* ss = CCString::createWithContentsOfFile(LEVEL_FILE);
	string s = string(ss->getCString());

	json_t *questionList;
	json_error_t error;

	questionList = json_loads(s.c_str(), strlen(s.c_str()), &error);
	int number = json_array_size(questionList);

	m_arrUnsedId = new CCArray();
	m_arrUnsedId->retain();

	for(int i = 0; i < number; i++)
	{
		CCString* strId = CCString::createWithFormat("%d", i+1);
		m_arrUnsedId->addObject(strId);

		json_t *question = json_array_get(questionList, i);
 		json_t* answers = json_object_get(question, "answers");

		LevelData* ld = LevelData::create(
			i+1,
			json_string_value(json_object_get(question, "quest")),
			json_string_value(json_array_get(answers, 0)),
			json_string_value(json_array_get(answers, 1)),
			json_string_value(json_array_get(answers, 2)),
			json_string_value(json_array_get(answers, 3)),
			(int)json_number_value(json_object_get(question, "right"))
			);

		m_dict->setObject(ld, i+1);
	}

	CCLOG("--------- LEVEL LOAD END ---------");
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
	LevelData* ld = (LevelData*)m_dict->objectForKey(level);
	return ld;
}

LevelData* LevelManager::randomUnusedLevel()
{
	int number = m_arrUnsedId->count();

	int rd = (int)(CCRANDOM_0_1() * number); //0 -> (number-1)

	CCString* strChooseLevel = (CCString*)m_arrUnsedId->objectAtIndex(rd);
	int chooseLevel = strChooseLevel->intValue();
	m_arrUnsedId->removeObjectAtIndex(rd); //remove used id

	return getLevel(chooseLevel);
}
