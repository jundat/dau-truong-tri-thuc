
#ifndef __DATA_MANAGER__
#define __DATA_MANAGER__

#include "cocos2d.h"
#include "MyMacro.h"
#include "Global.h"
#include <time.h>
#include <vector>
#include "jansson/jansson.h"

USING_NS_CC;
using namespace std;

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
	//Save list int
	json_t*			SetQuestionIdObject(vector<PairIntInt*>* listPairIntInt);
	json_t*			GetQuestionIdObject();

	//////////////////////////////////////////////////////////////////////////
	//Config from server
	
	MY_GETSET_INT_FUNC(SoloAddScore, "SOLO_ADD_SCORE", CONF_INT(SOLO_ADD_SCORE));
	MY_GETSET_INT_FUNC(SoloSubScore, "SOLO_SUB_SCORE", CONF_INT(SOLO_SUB_SCORE));

	MY_GETSET_INT_FUNC(DiamondForSkip, "DIAMOND_FOR_SKIP", CONF_INT(DIAMOND_FOR_SKIP));
	MY_GETSET_INT_FUNC(DiamondForInfinite, "DIAMOND_FOR_INFINITE", CONF_INT(DIAMOND_FOR_INFINITE));
	MY_GETSET_INT_FUNC(DiamondForExclusive, "DIAMOND_FOR_EXCLUSIVE", CONF_INT(DIAMOND_FOR_EXCLUSIVE));



	//////////////////////////////////////////////////////////////////////////
	//Facebook

	MY_GETSET_STR_FUNC(FbPhotoPath, "FB_PHOTO_PATH", std::string(""));
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
	MY_GETSET_INT_FUNC(SoloQuestionNumber, "SOLO_QUESTION_NUMBER", 0);
	MY_GETSET_INT_FUNC(SoloNumberOfFinishedQuestion, "SOLO_NUMBER_OF_FINISHED_QUESTION", 0);
	MY_GETSET_INT_FUNC(SoloNumberOfRightQuestion, "SOLO_NUMBER_OF_RIGHT_QUESTION", 0);
	
	//WAR
	MY_GETSET_INT_FUNC(WarScore, "WAR_SCORE", 0);
	MY_GETSET_INT_FUNC(WarNumberOfWin, "WAR_NUMBER_OF_WIN", 0);
	MY_GETSET_INT_FUNC(WarNumberOfLose, "WAR_NUMBER_OF_LOSE", 0);


	~DataManager(void);
};

#endif
