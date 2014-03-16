#include "MoreDiamondDialog.h"
#include "MenuScene.h"
#include "DataManager.h"
#include "cocos-ext.h"
#include "MyMacro.h"
#include "NDKHelper/NDKHelper.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool MoreDiamondDialog::init()
{
    if ( !CCLayer::init() )
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
	MenuScene* parent = (MenuScene*)this->getParent();
	parent->setTouchEnabled(true);
	parent->onCloseDialog();
	this->removeFromParent();
}

void MoreDiamondDialog::rateCallback( CCObject* pSender )
{
	NDKHelper::AddSelector("MORE_DIAMOND_DIALOG",
		"onRateCompleted",
		callfuncND_selector(MoreDiamondDialog::onRateCompleted),
		this);

	CCDictionary* prms = CCDictionary::create();
	prms->setObject(CCString::create(CONF_STR(URL_RATE)), "link");

	SendMessageWithParams(string("Rate"), prms);
}

void MoreDiamondDialog::inviteCallback( CCObject* pSender )
{
	NDKHelper::AddSelector("MORE_DIAMOND_DIALOG",
		"onInviteAllCompleted",
		callfuncND_selector(MoreDiamondDialog::onInviteAllCompleted),
		this);

	CCDictionary* prms = CCDictionary::create();
	prms->setObject(CCString::create(CONF_STR(INVITE_MESSAGE)), "message");

	SendMessageWithParams(string("InviteAll"), prms);
}

void MoreDiamondDialog::shareCallback( CCObject* pSender )
{
	CCMessageBox("share", "info");
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

		NDKHelper::RemoveSelector("MORE_DIAMOND_DIALOG", "onRateCompleted");
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

			m_itlbInvite->setEnabled(false);
			m_itlbInvite->setOpacity(100);
		}
		else
		{
			CCLOG("CPP Invite All Completed: FALSE");
		}

		NDKHelper::RemoveSelector("MORE_DIAMOND_DIALOG", "onInviteAllCompleted");
	}
}

void MoreDiamondDialog::onShareCompleted( CCNode *sender, void *data )
{

}
