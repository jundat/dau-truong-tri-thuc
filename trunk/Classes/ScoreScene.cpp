#include "MenuScene.h"
#include "ScoreScene.h"
#include "cocos-ext.h"
#include "DataManager.h"
#include "MyMacro.h"
#include "AudioManager.h"
#include "Global.h"
#include "MyMacro.h"
#include "GameClientManager.h"


USING_NS_CC;
USING_NS_CC_EXT;


CCScene* ScoreScene::scene()
{
	CCScene *scene = CCScene::create();
	ScoreScene *layer = ScoreScene::create();
	scene->addChild(layer);
	return scene;
}

bool ScoreScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	MY_ADD_SPRITE(bg, "score_background.png", ccp(400, 640));
	
	MY_ADD_MENU_ITEM(
		backItem, 
		"back.png",
		"backDown.png",
		"backDown.png",
		ScoreScene::menuCallback,
		ccp(60, 60)
		);
	
	MY_ADD_LABELTTF(lbTitle, "Bảng xếp hạng", CONF_STR(FONT_LEADERBOARD), 64, ccBLACK, ccp(400, 1200));

	//check if connect facebook
	//auto connect

	//get leaderboard

	//



	//MY_SEND_REQUEST("http://127.0.0.1:1337/", this, ScoreScene::onSendRequestCompleted, "HELLO");
	//GameClientManager::sharedGameClientManager()->sendRequest("http://127.0.0.1:1337/", this, httpresponse_selector(ScoreScene::onSendRequestCompleted), "HELLO");
	
	this->setKeypadEnabled(true);
	return true;
}

void ScoreScene::onSendRequestCompleted(CCHttpClient *sender, CCHttpResponse *response)
{
// 	if (!response)
// 	{
// 		return;
// 	}
// 
// 	//Show info
// 	CCLOG("------- BEGIN %s -------", response->getHttpRequest()->getTag());
// 	CCLOG("Status: [%i]", response->getResponseCode());
// 
// 	if (!response->isSucceed())
// 	{
// 		CCLOG("Request failed: %s", response->getErrorBuffer());
// 	}
// 	else
// 	{
// 		std::vector<char> *buffer = response->getResponseData();
// 		std::string str(buffer->begin(), buffer->end());
// 
// 		CCLOG("Content: %s", str.c_str());
//	}
// 	CCLOG("------- END %s -------", response->getHttpRequest()->getTag()
}

void ScoreScene::menuCallback(CCObject* pSender)
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void ScoreScene::keyBackClicked()
{
	menuCallback(NULL);
}

void ScoreScene::loginFacebook( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	NDKHelper::AddSelector("ScoreScene",
		"onLogInCompleted",
		callfuncND_selector(ScoreScene::onLogInCompleted),
		this);
	SendMessageWithParams(string("LogIn"), NULL);
}


//////////////////////////////////////////////////////////////////////////

void ScoreScene::onLogInCompleted( CCNode *sender, void *data )
{
	CCLOG("onLogInCompleted");
	static int counter = 0;
	if (data != NULL)
	{
		counter++;
		CCLOG("CPP data != NULL");
		CCDictionary *convertedData = (CCDictionary *)data;
		CCLOG("CPP get isSuccess");
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Log In Completed: TRUE");

			NDKHelper::AddSelector("ScoreScene",
				"onGetProfileCompleted",
				callfuncND_selector(ScoreScene::onGetProfileCompleted),
				this);
			SendMessageWithParams(string("GetProfile"), NULL);
		} 
		else
		{
			CCLOG("CPP Log In Completed: FALSE");
		}

		NDKHelper::RemoveSelector("ScoreScene", "onLogInCompleted");
	}
}

void ScoreScene::onGetProfileCompleted( CCNode *sender, void *data )
{
	CCLOG("onGetProfileCompleted");
	static int counter = 0;
	if (data != NULL)
	{
		counter++;

		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Get Profile Completed: TRUE");

			string fbId = ((CCString*)convertedData->objectForKey("id"))->getCString();
			string firstName = ((CCString*)convertedData->objectForKey("firstName"))->getCString();
			string name = ((CCString*)convertedData->objectForKey("name"))->getCString();
			string username = ((CCString*)convertedData->objectForKey("username"))->getCString();
			string birthday = ((CCString*)convertedData->objectForKey("birthday"))->getCString();
			string picture50x50 = ((CCString*)convertedData->objectForKey("picture"))->getCString();

			//save

			DataManager::sharedDataManager()->SetFbID(fbId);
			DataManager::sharedDataManager()->SetFbFullName(name);
			DataManager::sharedDataManager()->SetName(name);
			DataManager::sharedDataManager()->SetFbUserName(username);

			//////////////////////////////////////////////////////////////////////////

			NDKHelper::AddSelector("ScoreScene",
				"onGetAvatarCompleted",
				callfuncND_selector(ScoreScene::onGetAvatarCompleted),
				this);

			string w = "128";
			string h = "128";

			CCDictionary* prms = CCDictionary::create();
			prms->setObject(CCString::create(fbId), "fbId");
			prms->setObject(CCString::create(w), "width");
			prms->setObject(CCString::create(h), "height");

			SendMessageWithParams(string("GetAvatar"), prms);
		} 
		else
		{
			CCLOG("CPP Get Profile Completed: FALSE");
		}

		NDKHelper::RemoveSelector("ScoreScene", "onGetProfileCompleted");
	}
}

void ScoreScene::onGetAvatarCompleted( CCNode* pSender, void *data )
{
	CCLOG("onGetAvatarCompleted");
	static int counter = 0;
	if (data != NULL)
	{
		counter++;

		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Get Avatar Completed: TRUE");

			CCString* path = (CCString*)convertedData->objectForKey("path");

			DataManager::sharedDataManager()->SetFbPhotoPath(path->getCString());
		} 
		else
		{
			CCLOG("CPP Get Avatar Completed: FALSE");
		}

		NDKHelper::RemoveSelector("ScoreScene", "onGetAvatarCompleted");
	}
}

