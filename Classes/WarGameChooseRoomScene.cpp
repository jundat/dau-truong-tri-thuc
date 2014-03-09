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
	
	m_numberOfSubject = 0;

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
	
	MY_SEND_REQUEST(CONF_STR(URL_SUBJECT), this, WarGameChooseRoomScene::onGetSubjectListCompleted, "");

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
	return m_numberOfSubject;
}

void WarGameChooseRoomScene::onGetSubjectListCompleted( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!response)
	{
		return;
	}

	//Show info
	CCLOG("------- BEGIN %s -------", response->getHttpRequest()->getTag());
	CCLOG("Status: [%i]", response->getResponseCode());

	if (!response->isSucceed())
	{
		CCLOG("Request failed: %s", response->getErrorBuffer());
	}
	else
	{
		std::vector<char> *buffer = response->getResponseData();
		std::string str(buffer->begin(), buffer->end());

		CCLOG("Content: %s", str.c_str());

		//get score from response
		json_t *root;
		json_error_t error;
		json_t *subjectList;

		root = json_loads(str.c_str(), strlen(str.c_str()), &error);
		subjectList = json_object_get(root, "list");

		//foreach to get all friend, insert to list
		int m_numberOfSubject = json_array_size(subjectList);
		CCArray* arrSubjects = CCArray::create();

		for(int i = 0; i < m_numberOfSubject; i++)
		{
			json_t *subject = json_array_get(subjectList, i);

			json_t* subjectId;
			json_t* subjectName;

			subjectId = json_object_get(subject, "subjectId");
			subjectName = json_object_get(subject, "subjectName");
			
			CCLOG("%d: ", (int)json_number_value(subjectId));
			CCLOG("%s: ", json_string_value(subjectName));

			Subject* sub = Subject::create((int)json_number_value(subjectId), json_string_value(subjectName));
			arrSubjects->addObject(sub);
		}


	}

	CCLOG("------- END %s -------", response->getHttpRequest()->getTag());
}


//end table delegate




