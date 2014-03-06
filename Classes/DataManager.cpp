#include "DataManager.h"
#include "Global.h"
#include "MyMacro.h"


DataManager* DataManager::s_instance = 0;


DataManager* DataManager::sharedDataManager()
{
	if(DataManager::s_instance == 0)
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
