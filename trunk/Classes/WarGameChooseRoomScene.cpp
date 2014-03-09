#include "MenuScene.h"
#include "WarGameChooseRoomScene.h"
#include "cocos-ext.h"
#include "DataManager.h"
#include "MyMacro.h"
#include "AudioManager.h"
#include "Global.h"
#include "MyMacro.h"


USING_NS_CC;
USING_NS_CC_EXT;


CCScene* WarGameChooseRoomScene::scene()
{
	CCScene *scene = CCScene::create();
	WarGameChooseRoomScene *layer = WarGameChooseRoomScene::create();
	scene->addChild(layer);
	return scene;
}

bool WarGameChooseRoomScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	MY_ADD_SPRITE(bg, "score_background.png", ccp(400, 640));
	
	MY_ADD_MENU_ITEM(
		backItem, 
		"back.png",
		"backDown.png",
		"backDown.png",
		WarGameChooseRoomScene::menuCallback,
		ccp(60, 60)
		);
	
	MY_ADD_SPRITE(tableBorder, "table.png", ccp(400, 1280-726));

	//////////////////////////////////////////////////////////////////////////
	


	//////////////////////////////////////////////////////////////////////////

	this->setKeypadEnabled(true);
	return true;
}

void WarGameChooseRoomScene::menuCallback(CCObject* pSender)
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void WarGameChooseRoomScene::keyBackClicked()
{
	menuCallback(NULL);
}


//table delegate

void WarGameChooseRoomScene::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{

}

cocos2d::CCSize WarGameChooseRoomScene::tableCellSizeForIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	return CCSizeMake(0,0);
}

cocos2d::extension::CCTableViewCell* WarGameChooseRoomScene::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	return new cocos2d::extension::CCTableViewCell();
}

unsigned int WarGameChooseRoomScene::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 0;
}

//end table delegate




