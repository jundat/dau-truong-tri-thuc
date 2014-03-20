#include "MoreDiamondDialog.h"
#include "MenuScene.h"
#include "DataManager.h"
#include "cocos-ext.h"
#include "MyMacro.h"
#include "NDKHelper/NDKHelper.h"
#include "AudioManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool MoreDiamondDialog::init()
{
    if ( !CCLayerColor::initWithColor(DIM_COLOR) )
    {
        return false;
    }

	CCPoint pask = ccp(400, 1280 - 1000);
	
	CCScale9Sprite* dialog = CCScale9Sprite::create("dialog.png");
	dialog->setPosition(ccp(400, 1280-750));
	dialog->setContentSize(CCSizeMake(768, 640));
	this->addChild(dialog);

	CCScale9Sprite* dialogTop = CCScale9Sprite::create("dialog.png");
	dialogTop->setPosition(ccp(400, 1280-481));
	dialogTop->setContentSize(CCSizeMake(768, 100));
	this->addChild(dialogTop);

	MY_ADD_LABELTTF(labelTitle, "Thêm kim cương", CONF_STR(FONT_NORMAL), 48, ccBLACK, ccp(400, 1280 - 484));

	MY_ADD_MENU_ITEM_LABEL(itlbRate, CCString::createWithFormat("+ %d: Rate 5 sao", CONF_INT(DIAMOND_FOR_RATE))->getCString(), 
		CONF_STR(FONT_NORMAL), 48, ccBLACK, MoreDiamondDialog::rateCallback, ANCHOR_LEFT, ccp(188, 1280-628));
	MY_ADD_MENU_ITEM_LABEL(itlbInvite, CCString::createWithFormat("+ %d: Mời 1 bạn", CONF_INT(DIAMOND_FOR_INVITE))->getCString(),
		CONF_STR(FONT_NORMAL), 48, ccBLACK, MoreDiamondDialog::inviteCallback, ANCHOR_LEFT, ccp(188, 1280-738));
	MY_ADD_MENU_ITEM_LABEL(itlbShare, CCString::createWithFormat("+ %d: Chia sẻ", CONF_INT(DIAMOND_FOR_SHARE))->getCString(), 
		CONF_STR(FONT_NORMAL), 48, ccBLACK, MoreDiamondDialog::shareCallback, ANCHOR_LEFT, ccp(188, 1280-848));

	m_itlbRate = itlbRate;
	m_itlbInvite = itlbInvite;
	m_itlbShare = itlbShare;

	MY_ADD_SPRITE(sprRate, "rateIcon.png", ccp(108, 1280-628));
	MY_ADD_SPRITE(sprInvite, "inviteIcon.png", ccp(108, 1280-738));
	MY_ADD_SPRITE(sprShare, "shareIcon.png", ccp(108, 1280-848));

	//check
	if (DataManager::sharedDataManager()->GetIsRatedApp() == true)
	{
		m_itlbRate->setEnabled(false);
		m_itlbRate->setOpacity(100);
	}


	MY_ADD_MENU_ITEM(itExit, "exit_button.png", "exit_button_press.png", "exit_button_press.png", MoreDiamondDialog::exitCallback, pask);

	this->setKeypadEnabled(true);
    return true;
}

void MoreDiamondDialog::keyBackClicked()
{
	exitCallback(NULL);
}

void MoreDiamondDialog::exitCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	MenuScene* parent = (MenuScene*)this->getParent();
	parent->setTouchEnabled(true);
	parent->onCloseDialog();
	this->removeFromParent();
}

void MoreDiamondDialog::rateCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	NDKHelper::AddSelector("MoreDiamondDialog",
		"onRateCompleted",
		callfuncND_selector(MoreDiamondDialog::onRateCompleted),
		this);

	CCDictionary* prms = CCDictionary::create();
	prms->setObject(CCString::create(CONF_STR(URL_RATE)), "link");

	SendMessageWithParams(string("Rate"), prms);
}

void MoreDiamondDialog::inviteCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	bool isLogIn = DataManager::sharedDataManager()->GetFbIsLogIn();
	if (isLogIn)
	{
		NDKHelper::AddSelector("MoreDiamondDialog",
			"onInviteAllCompleted",
			callfuncND_selector(MoreDiamondDialog::onInviteAllCompleted),
			this);

		CCDictionary* prms = CCDictionary::create();
		prms->setObject(CCString::create(CONF_STR(INVITE_MESSAGE)), "message");

		SendMessageWithParams(string("InviteAll"), prms);
	} 
	else
	{
		m_curOperator = string("invite");
		NDKHelper::AddSelector("MoreDiamondDialog",
			"onLogInCompleted",
			callfuncND_selector(MoreDiamondDialog::onLogInCompleted),
			this);
		SendMessageWithParams(string("LogIn"), NULL);
	}
}

void MoreDiamondDialog::shareCallback( CCObject* pSender )
{
	PLAY_BUTTON_EFFECT;

	bool isLogIn = DataManager::sharedDataManager()->GetFbIsLogIn();
	if (isLogIn)
	{
		NDKHelper::AddSelector("MoreDiamondDialog",
			"onPublishFeedCompleted",
			callfuncND_selector(MoreDiamondDialog::onPublishFeedCompleted),
			this);

		string message = "Game này được, có bạn chơi cùng thì khỏi chê!";
		string name = "The Croods";
		string caption = "Thánh thức cùng bạn bè";
		string description = "Game hay, thuộc thể loại này nọ...";
		string picture = "http://vfossa.vn/tailen/news/2012_01/knowledge.jpg";
		string link = "https://play.google.com/store/apps/details?id=com.supercell.hayday";

		CCDictionary* prms = CCDictionary::create();
		prms->setObject(CCString::create(message), "message");
		prms->setObject(CCString::create(name), "name");
		prms->setObject(CCString::create(caption), "caption");
		prms->setObject(CCString::create(description), "description");
		prms->setObject(CCString::create(picture), "picture");
		prms->setObject(CCString::create(link), "link");

		SendMessageWithParams(string("PublishFeed"), prms);
	} 
	else
	{
		m_curOperator = string("share");
		NDKHelper::AddSelector("MoreDiamondDialog",
			"onLogInCompleted",
			callfuncND_selector(MoreDiamondDialog::onLogInCompleted),
			this);
		SendMessageWithParams(string("LogIn"), NULL);
	}	
}

//

void MoreDiamondDialog::onRateCompleted( CCNode *sender, void *data )
{
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Rate Completed: TRUE");
			CCString* s = (CCString*)convertedData->objectForKey("responseType");
			CCLOG("%s", s->getCString());
			if (s->compare("RATE") == 0)
			{
				CCMessageBox(
					CCString::createWithFormat("Bạn được nhận +%d kim cương.", CONF_INT(DIAMOND_FOR_RATE))->getCString(),
					"Thưởng");
				DataManager::sharedDataManager()->AddDiamond(CONF_INT(DIAMOND_FOR_RATE));
				DataManager::sharedDataManager()->SetIsRatedApp(true);

				m_itlbRate->setEnabled(false);
				m_itlbRate->setOpacity(100);
			}
		} 
		else
		{
			CCLOG("CPP Rate Completed: FALSE");
		}

		NDKHelper::RemoveSelector("MoreDiamondDialog", "onRateCompleted");
	}
}

void MoreDiamondDialog::onInviteAllCompleted( CCNode *sender, void *data )
{
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Invite All Completed: TRUE");
			CCString* requestId = (CCString*)convertedData->objectForKey("requestId");
			CCLOG("requestId: %s", requestId->getCString());

			CCArray *arrFriends = (CCArray *)convertedData->objectForKey("invitedFriends");

			int count = arrFriends->count();
			int total = CONF_INT(DIAMOND_FOR_INVITE) * count;

			DataManager::sharedDataManager()->AddDiamond(total);
			CCMessageBox(CCString::createWithFormat("Bạn nhận được:\n%d x %d bạn = %d kim cương", 
				CONF_INT(DIAMOND_FOR_INVITE), count, total)->getCString(),
				"Thưởng");
		}
		else
		{
			CCLOG("CPP Invite All Completed: FALSE");
			CCMessageBox("Không thể mời bạn", "Lỗi");
		}

		NDKHelper::RemoveSelector("MoreDiamondDialog", "onInviteAllCompleted");
	}
}

void MoreDiamondDialog::onPublishFeedCompleted( CCNode *sender, void *data )
{
	CCLOG("onPublishFeedCompleted");
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Publish Feed Completed: TRUE");
			
			CCMessageBox(
				CCString::createWithFormat("Bạn được nhận +%d kim cương.", CONF_INT(DIAMOND_FOR_SHARE))->getCString(),
				"Thưởng");
			DataManager::sharedDataManager()->AddDiamond(CONF_INT(DIAMOND_FOR_SHARE));
		} 
		else
		{
			CCLOG("CPP Publish Feed Completed: FALSE");
			CCMessageBox("Không thể chia sẻ", "Lỗi");
		}

		NDKHelper::RemoveSelector("MoreDiamondDialog", "onPublishFeedCompleted");
	}
}


void MoreDiamondDialog::onLogInCompleted( CCNode *sender, void *data )
{
	CCLOG("onLogInCompleted");
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Log In Completed: TRUE");

			NDKHelper::AddSelector("MoreDiamondDialog",
				"onGetProfileCompleted",
				callfuncND_selector(MoreDiamondDialog::onGetProfileCompleted),
				this);
			SendMessageWithParams(string("GetProfile"), NULL);
		} 
		else
		{
			CCLOG("CPP Log In Completed: FALSE");
			CCMessageBox("Không thể kết nối", "Lỗi");
		}

		NDKHelper::RemoveSelector("MoreDiamondDialog", "onLogInCompleted");
	}
}

void MoreDiamondDialog::onGetProfileCompleted( CCNode *sender, void *data )
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

			NDKHelper::AddSelector("MoreDiamondDialog",
				"onGetAvatarCompleted",
				callfuncND_selector(MoreDiamondDialog::onGetAvatarCompleted),
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
			CCMessageBox("Không thể kết nối", "Lỗi");
		}

		NDKHelper::RemoveSelector("MoreDiamondDialog", "onGetProfileCompleted");
	}
}

void MoreDiamondDialog::onGetAvatarCompleted( CCNode* pSender, void *data )
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

			MenuScene* parent = (MenuScene*) this->getParent();
			parent->m_itFacbook->runAction(CCFadeOut::create(0.5f));

			//show
			if (m_curOperator.compare("invite") == 0)
			{
				inviteCallback(NULL);
			} 
			else if (m_curOperator.compare("share") == 0)
			{
				shareCallback(NULL);
			}
		} 
		else
		{
			CCLOG("CPP Get Avatar Completed: FALSE");
			CCMessageBox("Không thể kết nối", "Lỗi");
		}

		NDKHelper::RemoveSelector("MoreDiamondDialog", "onGetAvatarCompleted");
	}
}
