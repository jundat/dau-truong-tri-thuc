#include "MenuScene.h"
#include "SettingScene.h"
#include "cocos-ext.h"
#include "DataManager.h"
#include "MyMacro.h"
#include "AudioManager.h"
#include "Global.h"


USING_NS_CC;
USING_NS_CC_EXT;


CCScene* SettingScene::scene()
{
	CCScene *scene = CCScene::create();
	SettingScene *layer = SettingScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	MY_ADD_SPRITE(bg, "guide_background.png", ccp(400, 640));

	MY_ADD_MENU_ITEM(
		backItem, 
		"back.png",
		"backDown.png",
		"backDown.png",
		SettingScene::menuCallback,
		ccp(60, 60)
		);

	MY_ADD_LABELTTF(lbTitle, "Cài đặt", CONF_STR(FONT_LEADERBOARD), 64, ccBLACK, ccp(400, 1200));


	this->setKeypadEnabled(true);
	return true;
}

void SettingScene::menuCallback(CCObject* pSender)
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void SettingScene::keyBackClicked()
{
	menuCallback(NULL);
}

