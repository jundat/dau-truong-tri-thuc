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

