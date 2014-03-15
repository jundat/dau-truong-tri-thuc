
#ifndef __DATA_MANAGER__
#define __DATA_MANAGER__

#include "cocos2d.h"
#include "MyMacro.h"
#include "Global.h"
#include <time.h>
USING_NS_CC;


class DataManager
{
private:
	DataManager();
	static DataManager *s_instance;

public:
	static DataManager* sharedDataManager();

	//////////////////////////////////////////////////////////////////////////
	//Common
	
	tm*		GetTime(const char* key);
	void	SetTime(const char* key, tm* time);

	//////////////////////////////////////////////////////////////////////////
	//Facebook

	MY_GETSET_STR_FUNC(FbPhotoPath, "FB_ID", std::string(""));
	MY_GETSET_STR_FUNC(FbID, "FB_ID", std::string(""));
	MY_GETSET_STR_FUNC(FbUserName, "FB_USERNAME", std::string(""));
	MY_GETSET_STR_FUNC(FbFullName, "FB_FULL_NAME", std::string(""));

	//////////////////////////////////////////////////////////////////////////
	//Normal Account

	MY_GETSET_STR_FUNC(Name, "NAME", std::string(CONF_STR(DEFAULT_USER_NAME)));
	MY_GETSET_STR_FUNC(UserName, "USER_NAME", std::string(""));
	MY_GETSET_STR_FUNC(Password, "PASSWORD", std::string(""));

	//////////////////////////////////////////////////////////////////////////
	//In game
	
	//COMMON
	MY_GETSET_INT_FUNC(Diamond, "DIAMOND", CONF_INT(DEFAULT_DIAMON));

	//SOLO
	MY_GETSET_INT_FUNC(SoloScore, "SOLO_SCORE", 0);
	MY_GETSET_INT_FUNC(SoloLastQuestionIndex, "SOLO_LAST_QUESTION_INDEX", 0);
	MY_GETSET_INT_FUNC(SoloNumberOfFinishedQuestion, "SOLO_NUMBER_OF_FINISHED_QUESTION", 0);
	MY_GETSET_INT_FUNC(SoloNumberOfRightQuestion, "SOLO_NUMBER_OF_RIGHT_QUESTION", 0);
	
	//WAR
	MY_GETSET_INT_FUNC(WarScore, "WAR_SCORE", 0);
	MY_GETSET_INT_FUNC(WarNumberOfWin, "WAR_NUMBER_OF_WIN", 0);
	MY_GETSET_INT_FUNC(WarNumberOfLose, "WAR_NUMBER_OF_LOSE", 0);


	~DataManager(void);
};

#endif
