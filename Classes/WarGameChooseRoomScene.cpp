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
	m_arrSubjects= NULL;
	m_tableSubjects = NULL;
	m_curWar = NULL;
	m_curSubjectId = -1;

	MY_ADD_SPRITE(bg, "score_background.png", ccp(400, 640));
	
	MY_ADD_SPRITE(avatar, "big_avatar.png", ccp(131, 1280-131));
	
	MY_ADD_LABELTTF(lbName, DataManager::sharedDataManager()->GetName().c_str(), CONF_STR(FONT_NORMAL), 64, ccBLACK, ccp(277, 1280-44));
	lbName->setAnchorPoint(ANCHOR_LEFT);

	CCString* s = CCString::createWithFormat("%d", DataManager::sharedDataManager()->GetWarNumberOfWin());
	MY_ADD_LABELTTF(lbWin, s->getCString(), CONF_STR(FONT_NORMAL), 64, ccBLACK, ccp(277, 1280-146));
	lbWin->setAnchorPoint(ANCHOR_LEFT);

	s = CCString::createWithFormat("%d", DataManager::sharedDataManager()->GetWarNumberOfLose());
	MY_ADD_LABELTTF(lbLose, s->getCString(), CONF_STR(FONT_NORMAL), 64, ccBLACK, ccp(277, 1280-228));
	lbLose->setAnchorPoint(ANCHOR_LEFT);

	MY_ADD_MENU_ITEM( backItem, "back.png", "backDown.png", "backDown.png", WarGameChooseRoomScene::menuCallback, ccp(60, 60));
	MY_ADD_MENU_ITEM( itStart, "start.png", "startDown.png", "startDown.png", WarGameChooseRoomScene::startCallback, ccp(720, 1280-1200));

	MY_ADD_SPRITE(tableBorder, "table.png", ccp(400, 1280-726));

	//////////////////////////////////////////////////////////////////////////
	//table

	CCSprite* m_cellSelect = CCSprite::create("cellSelect.png");
	m_cellSelect->retain();

	CCSprite* sprCell = CCSprite::create("cell.png");
	m_cellSize = sprCell->getContentSize();
	CCSize tableSize = CCSizeMake(654, 657);

	//vertical
	m_tableSubjects = CCTableView::create(this, tableSize);
	m_tableSubjects->setDirection(kCCScrollViewDirectionVertical);
	m_tableSubjects->setPosition(ccp(400 - tableSize.width/2, 1280-767 - tableSize.height/2));
	m_tableSubjects->setDelegate(this);
	m_tableSubjects->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(m_tableSubjects);


	this->setKeypadEnabled(true);
	return true;
}

void WarGameChooseRoomScene::onEnterTransitionDidFinish()
{
	MY_SEND_REQUEST(CONF_STR(URL_SUBJECT), this, WarGameChooseRoomScene::onGetSubjectListCompleted, "data={}&method=get");
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

void WarGameChooseRoomScene::gotoMaingame()
{

}

void WarGameChooseRoomScene::startCallback( CCObject* pSender )
{
	if (m_curSubjectId != -1)
	{
		PLAY_BUTTON_EFFECT;

		MY_SEND_REQUEST(CONF_STR(URL_JOIN), this, WarGameChooseRoomScene::onJoinCompleted, 
			CCString::createWithFormat("data={ \"fbId\" : \"%s\", \"subjectId\" : \"%d\" }", CONF_STR(APP_ID), m_curSubjectId)->getCString());
	}
	else
	{
		PLAY_OUT_PORP_EFFECT;
	}
}



//table delegate

void WarGameChooseRoomScene::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{
	PLAY_BUTTON_EFFECT;

	m_curSubjectId = cell->getTag();
	CCLOG("TOUCH AT: %d (subjectId)", m_curSubjectId);
	
	for (int i = 0; i < m_numberOfSubject; ++i)
	{
		CCTableViewCell* otherCell = table->cellAtIndex(i);
		if (otherCell)
		{
			otherCell->getChildByTag(1)->runAction(CCTintTo::create(0.25f, 255, 255, 255));
		}
	}

	cell->getChildByTag(1)->runAction(CCTintTo::create(0.25f, 0, 128, 0));
}

cocos2d::CCSize WarGameChooseRoomScene::tableCellSizeForIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	return m_cellSize;
}

cocos2d::extension::CCTableViewCell* WarGameChooseRoomScene::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	Subject* sub = dynamic_cast<Subject*>(m_arrSubjects->objectAtIndex(idx));
	string subjectName = CCString::createWithFormat("%d - %s", (idx + 1), sub->subjectName.c_str())->getCString();
	
	CCTableViewCell* cell = table->cellAtIndex(idx);
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		cell->setTag(sub->subjectId);
		
		CCSprite *sprite = CCSprite::create("cell.png");
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(ccp(0, 0));
		sprite->setTag(1);
		cell->addChild(sprite);

		CCLabelTTF* lbName = CCLabelTTF::create(subjectName.c_str(), CONF_STR(FONT_NORMAL), 48);
		lbName->setAnchorPoint(ANCHOR_LEFT);
		lbName->setPosition(ccp(70, m_cellSize.height/2));
		lbName->setTag(2);
		cell->addChild(lbName);
	}
	else
	{
		cell->getChildByTag(1)->runAction(CCTintTo::create(0.25f, 0, 128, 0));
	}

	return cell;
}

unsigned int WarGameChooseRoomScene::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return m_numberOfSubject;
}

//end table delegate

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
		CCMessageBox("Không thể kết nối máy chủ :/", "Lỗi");
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
		m_numberOfSubject = json_array_size(subjectList);
		if (m_arrSubjects != NULL)
		{
			m_arrSubjects->release();
			m_arrSubjects = NULL;
		}

		m_arrSubjects = CCArray::create();
		m_arrSubjects->retain();

		for(int i = 0; i < m_numberOfSubject; i++)
		{
			json_t *subject = json_array_get(subjectList, i);

			json_t* subjectId;
			json_t* subjectName;
			int id;

			subjectId = json_object_get(subject, "subjectid");
			subjectName = json_object_get(subject, "name");
			id = CCString::createWithFormat("%s", json_string_value(subjectId))->intValue();
			
			CCLOG("%d: ", id);
			CCLOG("%s: ", json_string_value(subjectName));

			Subject* sub = Subject::create(id, json_string_value(subjectName));
			m_arrSubjects->addObject(sub);
		}

		if (m_tableSubjects != NULL)
		{
			m_tableSubjects->reloadData();
		}
	}

	CCLOG("------- END %s -------", response->getHttpRequest()->getTag());
}

void WarGameChooseRoomScene::onJoinCompleted( CCHttpClient *sender, CCHttpResponse *response )
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
		CCMessageBox("Không thể kết nối máy chủ :/", "Lỗi");
	}
	else
	{
		std::vector<char> *buffer = response->getResponseData();
		std::string str(buffer->begin(), buffer->end());

		CCLOG("Content: %s", str.c_str());

		json_t *subject;
		json_error_t error;

		subject = json_loads(str.c_str(), strlen(str.c_str()), &error);

		json_t *oppId, *oppName, *oppWin, *oppLose, *quest, *a, *b, *c, *d, *right;

		oppId = json_object_get(subject, "oppId");
		oppName = json_object_get(subject, "oppName");
		oppWin = json_object_get(subject, "oppWin");
		oppLose = json_object_get(subject, "oppLose");
		quest = json_object_get(subject, "quest");
		a = json_object_get(subject, "a");
		b = json_object_get(subject, "b");
		c = json_object_get(subject, "c");
		d = json_object_get(subject, "d");
		right = json_object_get(subject, "right");

		if (m_curWar != NULL)
		{
			delete m_curWar;
			m_curWar = NULL;
		}

		m_curWar = new War();

		m_curWar->oppId = string(json_string_value(oppId));
		m_curWar->oppName = string(json_string_value(oppName));
		m_curWar->oppWin = (int)json_number_value(oppWin);
		m_curWar->oppLose = (int)json_number_value(oppLose);
		m_curWar->quest = string(json_string_value(quest));
		m_curWar->answers[0] = string(json_string_value(a));
		m_curWar->answers[1] = string(json_string_value(b));
		m_curWar->answers[2] = string(json_string_value(c));
		m_curWar->answers[3] = string(json_string_value(d));
		m_curWar->right = (int)json_number_value(right);

		gotoMaingame();
	}

	CCLOG("------- END %s -------", response->getHttpRequest()->getTag());
}





