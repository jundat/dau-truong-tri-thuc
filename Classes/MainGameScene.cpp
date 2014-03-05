#include "MainGameScene.h"
#include "AudioManager.h"
#include "MenuScene.h"
#include "LoseDialog.h"
#include "DataManager.h"
#include <time.h>
#include "PauseDialog.h"
#include "LevelManager.h"

USING_NS_CC;

CCScene* MainGameScene::scene()
{
    CCScene *scene = CCScene::create();
    MainGameScene *layer = MainGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainGameScene::init()
{
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
    {
        return false;
    }

	CCSprite* bg = CCSprite::create("game_background.png");
	bg->setPosition(ccp(400, 640));
	this->addChild(bg);

	//////////////////////////////////////////////////////////////////////////

	m_lbQuest = CCLabelTTF::create("Question...", "Roboto-Medium.ttf", 32);
	m_lbQuest->setFontFillColor(ccc3(0, 0, 0));
	m_lbQuest->setAnchorPoint(ccp(0.0f, 1.0f));
	m_lbQuest->setPosition(ccp(20, 1260));
	this->addChild(m_lbQuest);

	//////////////////////////////////////////////////////////////////////////

	CCMenuItemImage *itBack = CCMenuItemImage::create(
		"back.png",
		"back1.png",
		this,
		menu_selector(MainGameScene::menuCallback));
	itBack->setAnchorPoint(ccp(0.0f, 0.0f));
	itBack->setPosition(ccp(0, 0));

	CCMenuItemImage *itNext = CCMenuItemImage::create(
		"next.png",
		"next.png",
		this,
		menu_selector(MainGameScene::nextCallback));
	itNext->setPosition(ccp(400, 128));

	CCMenu* pMenu = CCMenu::create(itBack, itNext, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);


	this->setKeypadEnabled(true);
	PLAY_BACKGROUND_MUSIC;
    return true;
}

void MainGameScene::menuCallback(CCObject* pSender)
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MainGameScene::keyBackClicked()
{
	menuCallback(NULL);
}

void MainGameScene::nextCallback(CCObject* pSender)
{
	static int level = 0;
	level++;

	LevelData* ld = LevelManager::shareLevelLoader()->getLevel(level);
	m_lbQuest->setString(ld->ToString());
}
