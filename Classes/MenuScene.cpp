#include "Global.h"
#include "MenuScene.h"
#include "MainGameScene.h"
#include "ScoreScene.h"
#include "AudioManager.h"
#include "DataManager.h"
#include <time.h>

USING_NS_CC;
USING_NS_CC_EXT;


CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MenuScene *layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MenuScene::init()
{
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
    {
        return false;
    }
	
	CCSprite* bg = CCSprite::create("menu_background.png");
	bg->setPosition(ccp(400, 640));
	this->addChild(bg);

	//top
	//MY_ADD_SPRITE(sprTop, "ImgCrown.png", ccp(400, 400));
	CCSprite* sprTop = CCSprite::create("ImgCrown.png");
	sprTop->setPosition(ccp(400, 1280-292));
	this->addChild(sprTop);

	//play
    CCMenuItemImage* itPlaySolo = CCMenuItemImage::create(
        "play_button.png",
        "play_button_down.png",
        this,
        menu_selector(MenuScene::playSoloCallback));
	itPlaySolo->setPosition(ccp(400, 1280-639));
	
	CCSprite* sprPlaySolo = CCSprite::create("solo.png");
	sprPlaySolo->setPosition(ccp(400, 1280-642));
	this->addChild(sprPlaySolo, 1);

	CCMenuItemImage* itPlayWar = CCMenuItemImage::create(
		"play_button.png",
		"play_button_down.png",
		this,
		menu_selector(MenuScene::playWarCallback));
	itPlayWar->setPosition(ccp(400, 1280-804));

	CCSprite* sprPlayWar = CCSprite::create("thi_dau.png");
	sprPlayWar->setPosition(ccp(400, 1280-800));
	this->addChild(sprPlayWar, 1);

	//score
	CCMenuItemImage *itScore = CCMenuItemImage::create(
		"ImgMenuLeaderboard.png",
		"ImgMenuLeaderboardDown.png",
		this,
		menu_selector(MenuScene::scoreCallback));
	itScore->setPosition(ccp(164, 1280-984));

	//achievement
	CCMenuItemImage *itAchievement = CCMenuItemImage::create(
		"ImgMenuAchi.png",
		"ImgMenuAchiDown.png",
		this,
		menu_selector(MenuScene::achievementCallback));
	itAchievement->setPosition(ccp(319, 1280-984));

	//facebook
	CCMenuItemImage *itFacebook = CCMenuItemImage::create(
		"ImgMenuFacebook.png",
		"ImgMenuFacebookDown.png",
		this,
		menu_selector(MenuScene::facebookCallback));
	itFacebook->setPosition(ccp(480, 1280-984));

	//guide
	CCMenuItemImage *itGuide = CCMenuItemImage::create(
		"ImgMenuGuide.png",
		"ImgMenuGuideDown.png",
		this,
		menu_selector(MenuScene::guideCallback));
	itGuide->setPosition(ccp(635, 1280-984));


	CCMenuItem* soundOn = CCMenuItemImage::create("sound_on.png", NULL, NULL);
	CCMenuItem* soundOff = CCMenuItemImage::create("sound_off.png", NULL, NULL);
	CCMenuItemToggle* soundToggle = CCMenuItemToggle::createWithTarget(this,  menu_selector(MenuScene::soundCallback), soundOn, soundOff, NULL);
	if(AudioManager::sharedAudioManager()->IsEnableBackground())
	{
		soundToggle->setSelectedIndex(0);
	}
	else
	{
		soundToggle->setSelectedIndex(1);
	}
	soundToggle->setAnchorPoint(ccp(0.0f, 0.0f));
	soundToggle->setPosition(ccp(10, 10));

    CCMenu* m_menu = CCMenu::create(itPlaySolo, itPlayWar, itScore, itAchievement, itFacebook, itGuide, soundToggle, NULL);
    m_menu->setPosition(CCPointZero);
    this->addChild(m_menu);


	this->setKeypadEnabled(true);
	STOP_BACKGROUND_MUSIC;
    return true;
}

void MenuScene::keyBackClicked()
{
	PLAY_BUTTON_EFFECT;
	
	CCDirector::sharedDirector()->end();
}

void MenuScene::playSoloCallback(CCObject* pSender)
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, MainGameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MenuScene::playWarCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, MainGameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MenuScene::scoreCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, ScoreScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MenuScene::soundCallback( CCObject* pSender )
{
	if(AudioManager::sharedAudioManager()->IsEnableBackground())
	{
		PLAY_BUTTON_EFFECT;

		AudioManager::sharedAudioManager()->SetEnableBackground(false);
		AudioManager::sharedAudioManager()->SetEnableEffect(false);

		//
		AudioManager::sharedAudioManager()->StopBackground();
	}
	else
	{
		AudioManager::sharedAudioManager()->SetEnableBackground(true);
		AudioManager::sharedAudioManager()->SetEnableEffect(true);
	}
}

void MenuScene::achievementCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

}

void MenuScene::facebookCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

}

void MenuScene::guideCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

}
