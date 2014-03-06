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

std::string DataManager::GetName()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey("NAME", std::string(G_DEFAULT_NAME));
}

void DataManager::SetName( const char* name )
{
	CCUserDefault::sharedUserDefault()->setStringForKey("NAME", std::string(name));
	CCUserDefault::sharedUserDefault()->flush();
}


std::string DataManager::GetUsername()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey("USERNAME", std::string("NULL"));
}

void DataManager::SetUsername(const char* username)
{
	CCUserDefault::sharedUserDefault()->setStringForKey("USERNAME", std::string(username));
	CCUserDefault::sharedUserDefault()->flush();
}


std::string DataManager::GetPassword()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey("PASSWORD", std::string("NULL"));
}

void DataManager::SetPassword(const char* pass )
{
	CCUserDefault::sharedUserDefault()->setStringForKey("PASSWORD", std::string(pass));
	CCUserDefault::sharedUserDefault()->flush();
}


std::string DataManager::GetFbID()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey("FB_ID", std::string("NULL"));
}

void DataManager::SetFbID( const char* fbID )
{
	CCUserDefault::sharedUserDefault()->setStringForKey("FB_ID", std::string(fbID));
	CCUserDefault::sharedUserDefault()->flush();
}


std::string DataManager::GetFbUserName()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey("FB_USER_NAME", std::string("NULL"));
}

void DataManager::SetFbUserName( const char* fbusernam )
{
	CCUserDefault::sharedUserDefault()->setStringForKey("FB_USER_NAME", std::string(fbusernam));
	CCUserDefault::sharedUserDefault()->flush();
}


std::string DataManager::GetFbFullName()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey("FB_FULL_NAME", std::string("NULL"));
}

void DataManager::SetFbFullName( const char* fbusernam )
{
	CCUserDefault::sharedUserDefault()->setStringForKey("FB_FULL_NAME", std::string(fbusernam));
	CCUserDefault::sharedUserDefault()->flush();
}


std::string DataManager::GetFbPhotoPath()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey("FB_PHOTO_PATH", std::string("NULL"));
}

void DataManager::SetPhotoPath( const char* path )
{
	CCUserDefault::sharedUserDefault()->setStringForKey("FB_PHOTO_PATH", std::string(path));
	CCUserDefault::sharedUserDefault()->flush();
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


int DataManager::SoloGetLastQuestionIndex()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("SOLO_LAST_QUESTION_INDEX", 0);
}

void DataManager::SoloSetLastQuestionIndex( int index )
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("SOLO_LAST_QUESTION_INDEX", index);
	CCUserDefault::sharedUserDefault()->flush();
}


// int DataManager::GetDiamond()
// {
// 	return CCUserDefault::sharedUserDefault()->getIntegerForKey("DIAMON", G_DEFAULT_DIAMON);
// }
// 
// void DataManager::SetDiamond( int diamon )
// {
// 	CCUserDefault::sharedUserDefault()->setIntegerForKey("DIAMON", diamon);
// 	CCUserDefault::sharedUserDefault()->flush();
// }


//////////////////////////////////////////////////////////////////////////


//Default value = 0
int	DataManager::GetValueFromKey(const char* key)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(key, 0);
}

void DataManager::SetValueFromKey(const char* key, int val)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey(key, val);
	CCUserDefault::sharedUserDefault()->flush();
}


//////////////////////////////////////////////////////////////////////////

//Default value = 0
// int DataManager::GetSoloScore()
// {
// 	return CCUserDefault::sharedUserDefault()->getIntegerForKey("SOLO_SCORE", 0);
// }
// 
// void DataManager::SetSoloScore(int score)
// {
// 	CCUserDefault::sharedUserDefault()->setIntegerForKey("SOLO_SCORE", score);
// 	CCUserDefault::sharedUserDefault()->flush();
// }

