#include "DataManager.h"
#include "Global.h"
#include "MyMacro.h"


DataManager* DataManager::s_instance = NULL;


DataManager* DataManager::sharedDataManager()
{
	if(s_instance == NULL)
	{
		s_instance = new DataManager();
	}

	return s_instance;
}


DataManager::DataManager()
{
}

void DataManager::SetTime( const char* key, tm* time )
{
	CCString* sValue = CCString::createWithFormat("%d:%d:%d_%d-%d-%d", 
		time->tm_hour,
		time->tm_min,
		time->tm_sec,
		time->tm_mday,
		time->tm_mon,
		time->tm_year
	);

	CCUserDefault::sharedUserDefault()->setStringForKey(key, sValue->getCString());
	CCUserDefault::sharedUserDefault()->flush();
}

tm* DataManager::GetTime( const char* key )
{
	std::string sValue = std::string(CCUserDefault::sharedUserDefault()->getStringForKey(key));
	if (sValue.length() <= 0)
	{
		return NULL;
	} 
	else
	{
		int hour, min, sec, mday, mon, year;
		sscanf(sValue.c_str(), "%d:%d:%d_%d-%d-%d", &hour, &min, &sec, &mday, &mon, &year);

		tm* _tm = new tm();
		_tm->tm_hour = hour;
		_tm->tm_min = min;
		_tm->tm_sec = sec;
		_tm->tm_mday = mday;
		_tm->tm_mon = mon;
		_tm->tm_year = year;

		return _tm;	
	}
}

json_t* DataManager::SetQuestionIdObject( vector<PairIntInt*>* listPairIntInt )
{
	vector<PairIntInt*>::iterator it;
	
	string strToSave = string("{");
	int id = 0;

	for (it = listPairIntInt->begin(); it != listPairIntInt->end(); ++it)
	{
		id++;
		PairIntInt* p = (PairIntInt* ) (*it);
		
		strToSave.append(CCString::createWithFormat("\"%d\": %d,", id, p->valueId)->getCString());
	}

	strToSave.append("\"null\": 0}");
	//CCLOG("SET: %s", strToSave.c_str());

	CCUserDefault::sharedUserDefault()->setStringForKey("VECTOR_QUESTION_ID", strToSave.c_str());
	CCUserDefault::sharedUserDefault()->flush();

	json_t *questionObject;
	json_error_t error;

	questionObject = json_loads(strToSave.c_str(), strlen(strToSave.c_str()), &error);	

	return questionObject;
}

json_t* DataManager::GetQuestionIdObject()
{
	string strQuestionList = CCUserDefault::sharedUserDefault()->getStringForKey("VECTOR_QUESTION_ID", "{}");
	CCLOG("GET: %s", strQuestionList.c_str());

	if (strQuestionList.compare("{}") == 0)
	{
		CCLOG("{}: First time get question id list");
		return NULL;
	} 
	else
	{
		json_t *questionObject;
		json_error_t error;

		questionObject = json_loads(strQuestionList.c_str(), strlen(strQuestionList.c_str()), &error);

		return questionObject;
	}
}


CCArray* DataManager::GetQuestResults()
{
	string str = CCUserDefault::sharedUserDefault()->getStringForKey("QUEST_RESULTS", string("{\"list\":[]}")); //empty list
//	CCLOG("GET: %s", str.c_str());

	//get score from response
	json_t *root;
	json_error_t error;
	json_t *questResults;

	root = json_loads(str.c_str(), strlen(str.c_str()), &error);
	questResults = json_object_get(root, "list");

	//foreach to get all friend, insert to list
	int count = json_array_size(questResults);
//	CCLOG("COUNT: %d", count);
	CCArray* arrQuestResults = CCArray::create();

	for(int i = 0; i < count; i++)
	{
		json_t *quest = json_array_get(questResults, i);

		json_t* questId;
		json_t* isRight;
		json_t* answerTime;

		questId = json_object_get(quest, "questId");
		isRight = json_object_get(quest, "isRight");
		answerTime = json_object_get(quest, "time");

// 		CCLOG("(%d : %d : %d)", 
// 			(int)json_number_value(questId),
// 			(int)json_number_value(isRight), 
// 			(int)json_number_value(answerTime));

		QuestionResult* acc = new QuestionResult(
			(int)json_number_value(questId),
			(int)json_number_value(isRight), 
			(int)json_number_value(answerTime));

		arrQuestResults->addObject(acc);
	}

	return arrQuestResults;
}

void DataManager::SetQuestResults( CCArray* arrQuestResults )
{
	if (arrQuestResults == NULL)
	{
		CCUserDefault::sharedUserDefault()->setStringForKey("QUEST_RESULTS", string("{\"list\":[]}"));
		return;
	}


	//parse arrFriendList to json
	std::string strQuestList = std::string("");
	int count = arrQuestResults->count();

	for (int i = 0; i < count; ++i)
	{
		QuestionResult* questResult = (QuestionResult*)arrQuestResults->objectAtIndex(i);
		strQuestList.append(questResult->toJson());

		if (i != count - 1)
		{
			strQuestList.append(",");
		}
	}	

	CCString* strData = CCString::createWithFormat("{\"list\": [%s]}", strQuestList.c_str());
//	CCLOG("SAVE: %s", strData->getCString());

	CCUserDefault::sharedUserDefault()->setStringForKey("QUEST_RESULTS", strData->getCString());
	CCUserDefault::sharedUserDefault()->flush();
}

