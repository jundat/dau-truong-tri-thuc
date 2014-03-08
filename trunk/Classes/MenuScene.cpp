#include "Global.h"
#include "MenuScene.h"
#include "SoloGameScene.h"
#include "ScoreScene.h"
#include "AudioManager.h"
#include "DataManager.h"
#include "GuideScene.h"
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
	
	MY_ADD_SPRITE(bg, "menu_background.png", ccp(400, 640));
	MY_ADD_SPRITE(sprTop, "ImgCrown.png", ccp(400, 1280-292));

	//play button
	MY_ADD_MENU_ITEM(itPlaySolo, 
		"play_button.png", 
		"play_button_down.png", 
		"play_button_down.png", 
		MenuScene::playSoloCallback, 
		ccp(400, 1280-639));

	MY_ADD_MENU_ITEM(itPlayWar, 
		"play_button.png", 
		"play_button_down.png", 
		"play_button_down.png", 
		MenuScene::playWarCallback, 
		ccp(400, 1280-804));
	
	MY_ADD_SPRITE(sprPlaySolo, "solo.png", ccp(400, 1280-642));
	MY_ADD_SPRITE(sprPlayWar, "thi_dau.png", ccp(400, 1280-800));

	//score
	MY_ADD_MENU_ITEM(itScore, 
		"ImgMenuLeaderboard.png", 
		"ImgMenuLeaderboardDown.png", 
		"ImgMenuLeaderboardDown.png", 
		MenuScene::scoreCallback, 
		ccp(250, 1280-1000));

	//facebook
	MY_ADD_MENU_ITEM(itFacebook, 
		"ImgMenuFacebook.png", 
		"ImgMenuFacebookDown.png", 
		"ImgMenuFacebookDown.png", 
		MenuScene::facebookCallback, 
		ccp(400, 1280-1000));

	//guide
	MY_ADD_MENU_ITEM(itGuide, 
		"ImgMenuGuide.png", 
		"ImgMenuGuideDown.png", 
		"ImgMenuFacebookDown.png", 
		MenuScene::guideCallback, 
		ccp(550, 1280-1000));


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

    CCMenu* m_menu = CCMenu::create(soundToggle, NULL);
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

	CCScene *pScene = CCTransitionFade::create(0.5, SoloGameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MenuScene::playWarCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, SoloGameScene::scene());
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

void MenuScene::facebookCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;
	CCMessageBox("Connect Facebook", "Info");
}

void MenuScene::guideCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, GuideScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}
