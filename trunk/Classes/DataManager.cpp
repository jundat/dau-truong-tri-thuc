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

