
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




class QuestionResult : public CCObject
{
public:
	int m_questId;
	int m_isRight;
	int m_time;

public:
	QuestionResult() 
	{
		m_questId = -1;
		m_isRight = 0;
		m_time = -1;
	}

	QuestionResult(int _questId, int _isRight, int _time)
	{
		m_questId = _questId;
		m_isRight = _isRight;
		m_time = _time;
	}

	CCObject* copyWithZone(CCZone *pZone)
	{
		CCZone *pNewZone = NULL;
		QuestionResult *pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
		{
			pRet = (QuestionResult*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new QuestionResult();
			pZone = pNewZone = new CCZone(pRet);
		}
		CCObject::copyWithZone(pZone);
		// copy member data
		//pRet->m_nTag = m_nTag;
		pRet->m_questId = m_questId;
		pRet->m_isRight = m_isRight;
		pRet->m_time = m_time;

		CC_SAFE_DELETE(pNewZone);
		return pRet;
	}

	string toJson()
	{
		CCString* s = CCString::createWithFormat("{\"questId\": %d, \"isRight\": %d, \"time\": %d}", m_questId, m_isRight, m_time);
		return string(s->getCString());
	}
};




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
	//user
	MY_GETSET_STR_FUNC(UserID, "USER_ID", std::string(""));


	//////////////////////////////////////////////////////////////////////////
	//Facebook
	MY_GETSET_BOOL_FUNC(FbIsLogIn, "FB_IS_LOG_IN", false);
	MY_GETSET_STR_FUNC(FbPhotoPath, "FB_PHOTO_PATH", std::string(""));
	MY_GETSET_STR_FUNC(FbID, "FB_ID", std::string(""));
	MY_GETSET_STR_FUNC(FbUserName, "FB_USERNAME", std::string(""));
	MY_GETSET_STR_FUNC(FbFullName, "FB_FULL_NAME", std::string(""));

	MY_GETSET_INT_FUNC(AdviseFacebookTimes, "ADVISE_FACEBOOK_TIMES", CONF_INT(ADVISE_FACEBOOK_TIMES));

	//////////////////////////////////////////////////////////////////////////
	//Normal Account

	MY_GETSET_STR_FUNC(Name, "NAME", std::string(CONF_STR(DEFAULT_USER_NAME)));
	MY_GETSET_STR_FUNC(UserName, "USER_NAME", std::string(""));
	MY_GETSET_STR_FUNC(Password, "PASSWORD", std::string(""));

	//////////////////////////////////////////////////////////////////////////
	//Rate
	MY_GETSET_BOOL_FUNC(IsRatedApp, "IS_RATED_APP", false);

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

	CCArray* GetQuestResults();
	void SetQuestResults( CCArray* arrQuestResults );

};

#endif
