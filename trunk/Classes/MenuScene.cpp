#include "Global.h"
#include "MenuScene.h"
#include "SoloGameScene.h"
#include "ScoreScene.h"
#include "AudioManager.h"
#include "DataManager.h"
#include "GuideScene.h"
#include "SettingScene.h"
#include "WarGameChooseRoomScene.h"
#include "NDKHelper/NDKHelper.h"
#include <time.h>
#include "TutorialScene.h"
#include "QuitDialog.h"
#include "MoreDiamondDialog.h"

USING_NS_CC;
USING_NS_CC_EXT;



#define FACEBOOK_RETRY_TIMES	1



CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MenuScene *layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

void MenuScene::onEnterTransitionDidFinish()
{
//	GameClientManager::sharedGameClientManager()->setDelegate(this);
//	string fbId = DataManager::sharedDataManager()->GetFbID();
//	int score = DataManager::sharedDataManager()->GetSoloScore();
//
//	//send to server
//	GameClientManager::sharedGameClientManager()->sendScore(CONF_STR(APP_ID), fbId, score);
//
//	//send score to facebook ////////////////////////////////////////////////////////////
// 	NDKHelper::AddSelector("MENU",
// 		"onPostScoreCompleted",
// 		callfuncND_selector(MenuScene::onPostScoreCompleted),
// 		this);
//
// 	CCDictionary* prms = CCDictionary::create();
// 	prms->setObject(CCString::createWithFormat("%d", score), "score"
//	SendMessageWithParams(string("PostScore"), prms);
}

bool MenuScene::init()
{
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
    {
        return false;
    }


	MY_ADD_SPRITE(bg, "game_background.png", ccp(400, 640));
	MY_ADD_SPRITE(sprTop, "menu_top.png", ccp(377, 1280-227));

	m_menu = CCMenu::create();
	m_menu->setPosition(CCPointZero);
	this->addChild(m_menu);

	//play button
	MY_CREATE_MENU_ITEM(itPlaySolo, 
		"play_button.png", 
		"play_button_down.png", 
		"play_button_down.png", 
		MenuScene::playSoloCallback, 
		ccp(400, 1280-739)); //639
	m_menu->addChild(itPlaySolo);

	CCLabelTTF* lbVendor = CCLabelTTF::create("...Exception Games...", CONF_STR(FONT_NORMAL), 36);
	lbVendor->setPosition(ccp(400, lbVendor->getContentSize().height));
	lbVendor->setColor(ccBLACK);
	this->addChild(lbVendor);

// 	MY_CREATE_MENU_ITEM(itPlayWar, 
// 		"play_button.png", 
// 		"play_button_down.png", 
// 		"play_button_down.png", 
// 		MenuScene::playWarCallback, 
// 		ccp(400, 1280-804));
// 	m_menu->addChild(itPlayWar);
	
//	MY_ADD_SPRITE(sprPlaySolo, "solo.png", ccp(400, 1280-642));
//	MY_ADD_SPRITE(sprPlayWar, "thi_dau.png", ccp(400, 1280-800));

	//score
// 	MY_CREATE_MENU_ITEM(itScore, 
// 		"ImgMenuLeaderboard.png", 
// 		"ImgMenuLeaderboardDown.png", 
// 		"ImgMenuLeaderboardDown.png", 
// 		MenuScene::scoreCallback, 
// 		ccp(175, 1280-1000));
// 	m_menu->addChild(itScore);

	//more diamond
// 	MY_CREATE_MENU_ITEM(itMoreDiamond, 
// 		"moreDiamond.png", 
// 		"moreDiamondDown.png", 
// 		"moreDiamondDown.png", 
// 		MenuScene::moreDiamondCallback, 
// 		ccp(325, 1280-1000));
// 	m_menu->addChild(itMoreDiamond);

	//guide
// 	MY_CREATE_MENU_ITEM(itGuide, 
// 		"ImgMenuGuide.png", 
// 		"ImgMenuGuideDown.png", 
// 		"ImgMenuGuideDown.png", 
// 		MenuScene::guideCallback, 
// 		ccp(475, 1280-1000));
// 	m_menu->addChild(itGuide);

	//setting
// 	MY_CREATE_MENU_ITEM(itSetting, 
// 		"ImgMenuSetting.png", 
// 		"ImgMenuSettingDown.png", 
// 		"ImgMenuSettingDown.png", 
// 		MenuScene::settingCallback, 
// 		ccp(625, 1280-1000));
// 	m_menu->addChild(itSetting);
	
	//facebook
// 	MY_CREATE_MENU_ITEM(itFacebook, 
// 		"facebook.png", 
// 		"facebookDown.png", 
// 		"facebookDown.png",
// 		MenuScene::facebookCallback, 
// 		ccp(622, 1280-1220));
// 	m_itFacbook = itFacebook;
// 	m_itFacbook->setVisible(false);
// 	m_menu->addChild(m_itFacbook);

//	checkLogIn(NULL);

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
	//soundToggle->setAnchorPoint(ccp(0.0f, 0.0f));
	soundToggle->setPosition(ccpSub(itPlaySolo->getPosition(), ccp(0, itPlaySolo->getContentSize().height/2 + soundToggle->getContentSize().height/2)));
	m_menu->addChild(soundToggle);



	this->setKeypadEnabled(true);
	STOP_BACKGROUND_MUSIC;
    return true;
}

void MenuScene::onShowDialog()
{
	m_menu->setEnabled(false);
	this->setKeypadEnabled(false);
}

void MenuScene::onCloseDialog()
{
	m_menu->setEnabled(true);
	this->setKeypadEnabled(true);
}

void MenuScene::keyBackClicked()
{
	PLAY_BUTTON_EFFECT;

	QuitDialog* dialog = QuitDialog::create();
	this->addChild(dialog, 10);
	this->onShowDialog();
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

	CCScene *pScene = CCTransitionFade::create(0.5, WarGameChooseRoomScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MenuScene::scoreCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, ScoreScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MenuScene::moreDiamondCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;
	
	MoreDiamondDialog* dialog = MoreDiamondDialog::create();
	this->addChild(dialog, 10);
	this->onShowDialog();
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
	
	NDKHelper::AddSelector("MENU",
		"onLogInCompleted",
		callfuncND_selector(MenuScene::onLogInCompleted),
		this);
	SendMessageWithParams(string("LogIn"), NULL);
}

void MenuScene::guideCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, TutorialScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MenuScene::settingCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, SettingScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

//////////////////////////////////////////////////////////////////////////

void MenuScene::onLogInCompleted( CCNode *sender, void *data )
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

			NDKHelper::AddSelector("MENU",
				"onGetProfileCompleted",
				callfuncND_selector(MenuScene::onGetProfileCompleted),
				this);
			SendMessageWithParams(string("GetProfile"), NULL);
		} 
		else
		{
			CCLOG("CPP Log In Completed: FALSE");

			if (counter <= FACEBOOK_RETRY_TIMES)
			{
				NDKHelper::AddSelector("MENU",
					"onLogInCompleted",
					callfuncND_selector(MenuScene::onLogInCompleted),
					this);
				SendMessageWithParams(string("LogIn"), NULL);

				return;
			} 
			else
			{
				CCMessageBox("Fail to connect facebook", "Error");
			}
		}

		NDKHelper::RemoveSelector("MENU", "onLogInCompleted");
	}
}

void MenuScene::onGetProfileCompleted( CCNode *sender, void *data )
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
			
			NDKHelper::AddSelector("MENU",
				"onGetAvatarCompleted",
				callfuncND_selector(MenuScene::onGetAvatarCompleted),
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

			if (counter <= FACEBOOK_RETRY_TIMES)
			{
				NDKHelper::AddSelector("MENU",
					"onGetProfileCompleted",
					callfuncND_selector(MenuScene::onGetProfileCompleted),
					this);
				SendMessageWithParams(string("GetProfile"), NULL);

				return;
			} 
			else
			{
				CCMessageBox("Fail to connect facebook", "Error");
			}
		}

		NDKHelper::RemoveSelector("MENU", "onGetProfileCompleted");
	}
}

void MenuScene::onGetAvatarCompleted( CCNode* pSender, void *data )
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
			DataManager::sharedDataManager()->SetFbIsLogIn(true);

			m_itFacbook->runAction(CCFadeOut::create(0.5f));
			
			CCString* path = (CCString*)convertedData->objectForKey("path");

			DataManager::sharedDataManager()->SetFbPhotoPath(path->getCString());
		} 
		else
		{
			CCLOG("CPP Get Avatar Completed: FALSE");

			if (counter <= FACEBOOK_RETRY_TIMES)
			{
				NDKHelper::AddSelector("MENU",
					"onGetAvatarCompleted",
					callfuncND_selector(MenuScene::onGetAvatarCompleted),
					this);

				string w = "128";
				string h = "128";

				CCDictionary* prms = CCDictionary::create();
				prms->setObject(CCString::create(DataManager::sharedDataManager()->GetFbID()), "fbId");
				prms->setObject(CCString::create(w), "width");
				prms->setObject(CCString::create(h), "height");

				SendMessageWithParams(string("GetAvatar"), prms);

				return;
			} 
			else
			{
				CCMessageBox("Fail to connect facebook", "Error");
			}
		}

		NDKHelper::RemoveSelector("MENU", "onGetAvatarCompleted");
	}
}

void MenuScene::onCheckLogInCompleted( CCNode *sender, void *data )
{
	CCLOG("onCheckLogInCompleted");
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Check Log In Completed: TRUE");

			bool isLogIn = ((CCString*)convertedData->objectForKey("isLogIn"))->boolValue();
			DataManager::sharedDataManager()->SetFbIsLogIn(isLogIn);

			if (isLogIn)
			{
				CCLOG("IS LOG IN");
				m_itFacbook->setVisible(false);
			} 
			else
			{
				CCLOG("IS --NOT-- LOG IN");
				m_itFacbook->setVisible(true);
			}
		} 
		else
		{
			CCLOG("CPP Check Log In Completed: FALSE");
			m_itFacbook->setVisible(true);
			DataManager::sharedDataManager()->SetFbIsLogIn(false);
		}

		NDKHelper::RemoveSelector("MENU", "onCheckLogInCompleted");
	}
}

void MenuScene::checkLogIn( CCObject* pSender )
{
	NDKHelper::AddSelector("MENU",
		"onCheckLogInCompleted",
		callfuncND_selector(MenuScene::onCheckLogInCompleted),
		this);
	SendMessageWithParams(string("CheckLogIn"), NULL);
}

void MenuScene::onPostScoreCompleted( CCNode *sender, void *data )
{
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Post Score Completed: TRUE");
		} 
		else
		{
			CCLOG("CPP Post Score Completed: FALSE");
		}

		NDKHelper::RemoveSelector("MENU", "onPostScoreCompleted");
	}
}

void MenuScene::onSendScoreCompleted( bool isSuccess )
{
	if (isSuccess)
	{
		CCLOG("TRUE");
	} 
	else
	{
		CCLOG("FALSE");
	}
}