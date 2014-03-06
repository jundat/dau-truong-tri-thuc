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

	CCSprite* bg = CCSprite::create("guide_background.png");
	bg->setPosition(ccp(400, 640));
	this->addChild(bg);

	CCMenuItemImage *backItem = CCMenuItemImage::create(
		"back.png",
		"backDown.png",
		this,
		menu_selector(GuideScene::menuCallback));
	backItem->setAnchorPoint(ccp(0.0f, 0.0f));
	backItem->setPosition(ccp(10, 10));


	CCMenu* pMenu = CCMenu::create(backItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);


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

