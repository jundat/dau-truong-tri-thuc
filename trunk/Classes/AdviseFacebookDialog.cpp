#include "AdviseFacebookDialog.h"
#include "DataManager.h"
#include "cocos-ext.h"
#include "NDKHelper/NDKHelper.h"
#include "AudioManager.h"
#include "SoloGameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool AdviseFacebookDialog::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCPoint pexit = ccp(250, 1280 - 820);
	CCPoint pask = ccp(800-250, 1280 - 820);


	CCScale9Sprite* dialog = CCScale9Sprite::create("dialog.png");
	dialog->setPosition(ccp(400, 640));
	dialog->setContentSize(CCSizeMake(680, 480));
	this->addChild(dialog, -2);
	
	CCMenuItemImage* exitButton = CCMenuItemImage::create(
		"yes.png",
		"yesDown.png",
		this,
		menu_selector(AdviseFacebookDialog::yesCallback));
	exitButton->setPosition(pexit);


	CCMenuItemImage* askButton = CCMenuItemImage::create(
		"no.png",
		"noDown.png",
		this,
		menu_selector(AdviseFacebookDialog::noCallback));
	askButton->setPosition(pask);

	CCMenu* menu = CCMenu::create(exitButton, askButton, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	CCLabelTTF* lbAdvise = CCLabelTTF::create("Bạn hãy kết nối Facebook để có thêm càng nhiều bạn, càng nhiều niềm vui!", 
		CONF_STR(FONT_NORMAL), 
		48, 
		CCSizeMake(9.0f * dialog->getContentSize().width / 10.0f, 0), 
		kCCTextAlignmentCenter, 
		kCCVerticalTextAlignmentCenter);
	lbAdvise->setFontFillColor(ccBLACK);
	lbAdvise->setColor(ccBLACK);
	lbAdvise->setPosition(ccp(400, 700));
	this->addChild(lbAdvise);

    return true;
}

void AdviseFacebookDialog::yesCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	NDKHelper::AddSelector("AdviseFacebookDialog",
		"onLogInCompleted",
		callfuncND_selector(AdviseFacebookDialog::onLogInCompleted),
		this);
	SendMessageWithParams(string("LogIn"), NULL);
}

void AdviseFacebookDialog::noCallback( CCObject* pSender )
{
	SoloGameScene* parent = (SoloGameScene*)this->getParent();
	parent->onCloseDialog();
	parent->nextQuestion(NULL);
	this->removeFromParent();
}

void AdviseFacebookDialog::onLogInCompleted( CCNode *sender, void *data )
{
	CCLOG("onLogInCompleted");
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Log In Completed: TRUE");

			NDKHelper::AddSelector("AdviseFacebookDialog",
				"onGetProfileCompleted",
				callfuncND_selector(AdviseFacebookDialog::onGetProfileCompleted),
				this);
			SendMessageWithParams(string("GetProfile"), NULL);
		} 
		else
		{
			CCLOG("CPP Log In Completed: FALSE");
			onError();
		}

		NDKHelper::RemoveSelector("AdviseFacebookDialog", "onLogInCompleted");
	}
}

void AdviseFacebookDialog::onGetProfileCompleted( CCNode *sender, void *data )
{
	CCLOG("onGetProfileCompleted");
	if (data != NULL)
	{
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

			NDKHelper::AddSelector("AdviseFacebookDialog",
				"onGetAvatarCompleted",
				callfuncND_selector(AdviseFacebookDialog::onGetAvatarCompleted),
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
			onError();
		}

		NDKHelper::RemoveSelector("AdviseFacebookDialog", "onGetProfileCompleted");
	}
}

void AdviseFacebookDialog::onGetAvatarCompleted( CCNode* pSender, void *data )
{
	CCLOG("onGetAvatarCompleted");
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Get Avatar Completed: TRUE");
			DataManager::sharedDataManager()->SetFbIsLogIn(true);
			
			CCString* path = (CCString*)convertedData->objectForKey("path");
			DataManager::sharedDataManager()->SetFbPhotoPath(path->getCString());

			//show
			SoloGameScene* parent = (SoloGameScene*) this->getParent();
			parent->refreshUserInfo();
			noCallback(NULL);
		} 
		else
		{
			CCLOG("CPP Get Avatar Completed: FALSE");
			onError();
		}

		NDKHelper::RemoveSelector("AdviseFacebookDialog", "onGetAvatarCompleted");
	}
}

void AdviseFacebookDialog::onError()
{
	CCMessageBox("Không thể kết nối!", "Lỗi");
	noCallback(NULL);
}
