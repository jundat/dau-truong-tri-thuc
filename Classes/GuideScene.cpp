#include "MenuScene.h"
#include "GuideScene.h"
#include "cocos-ext.h"
#include "DataManager.h"
#include "MyMacro.h"
#include "AudioManager.h"
#include "Global.h"


USING_NS_CC;
USING_NS_CC_EXT;


CCScene* GuideScene::scene()
{
	CCScene *scene = CCScene::create();
	GuideScene *layer = GuideScene::create();
	scene->addChild(layer);
	return scene;
}

bool GuideScene::init()
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
		GuideScene::menuCallback,
		ccp(60, 60)
		);

	MY_ADD_LABELTTF(lbTitle, "Hướng dẫn", G_FONT_LEADERBOARD, 64, ccBLACK, ccp(400, 1200));


	this->setKeypadEnabled(true);
	return true;
}

void GuideScene::menuCallback(CCObject* pSender)
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void GuideScene::keyBackClicked()
{
	menuCallback(NULL);
}

