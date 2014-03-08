#include "MainGameScene.h"
#include "AudioManager.h"
#include "MenuScene.h"
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
	
	m_curScore = DataManager::sharedDataManager()->GetSoloScore();
	m_curQuestionNumber = DataManager::sharedDataManager()->GetSoloLastQuestionIndex();
	m_curRightAnswer = -1;
	m_clockCounter = CONF_INT(G_SOLO_TIME_FOR_QUESTION);
	m_isRight = false;
	m_isPause = false;

	MY_ADD_SPRITE(bg, "game_background.png", ccp(400, 640));

	MY_ADD_MENU_ITEM(itBack, "back.png", "backDown.png", "backDown.png", MainGameScene::menuCallback, ccp(60, 60));
	
	//HELP

	MY_ADD_MENU_ITEM(itHelp1, "help1.png", "help1Down.png", "help1Down.png", MainGameScene::itHelp1Callback, ccp(740, 1280-60));
	MY_ADD_MENU_ITEM(itHelp2, "help2.png", "help2Down.png", "help2Down.png", MainGameScene::itHelp2Callback, ccp(640, 1280-60));
	MY_ADD_MENU_ITEM(itHelp3, "help3.png", "help3Down.png", "help3Down.png", MainGameScene::itHelp3Callback, ccp(540, 1280-60));

	initItems();

	MY_ADD_SPRITE(_sprGameResult, "game_result.png", ccp(400, 1280-587));
	m_sprGameResult = _sprGameResult;
	m_sprGameResult->setVisible(false);
	MY_CREATE_MENU_ITEM(itNext, "next.png", "next.png", "next.png", MainGameScene::nextQuestion, ccp(400, m_sprGameResult->getContentSize().height/2));
	m_sprGameResult->addChild(menuitNext);

	nextQuestion(NULL);
	
	PLAY_BACKGROUND_MUSIC;
    return true;
}

void MainGameScene::onEnterTransitionDidFinish()
{
	this->schedule(schedule_selector(MainGameScene::scheduleClock), 0.5f);
	this->setKeypadEnabled(true);
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

void MainGameScene::answerCallback( CCObject* pSender )
{
	if (m_isPause)
	{
		return;
	}
	
	this->unschedule(schedule_selector(MainGameScene::scheduleClock));

	CCMenuItemImage* it = (CCMenuItemImage*) pSender;
	int tag = it->getTag();

	if (tag == m_curRightAnswer)
	{
		//CCMessageBox("RIGHT", "ANSWER");
		PLAY_GET_BOMB_EFFECT;
		m_curScore += CONF_INT(G_SOLO_ADD_SCORE);
		m_isRight = true;
	}
	else
	{
		//CCMessageBox("WRONG", "ANSWER");
		PLAY_OUT_PORP_EFFECT;
		m_curScore -= CONF_INT(G_SOLO_SUB_SCORE);
		m_isRight = false;
	}

	animationRightChoose();
	m_lbScore->setString(CCString::createWithFormat("%d", m_curScore)->getCString());
	DataManager::sharedDataManager()->SetSoloScore(m_curScore);
	DataManager::sharedDataManager()->SetSoloLastQuestionIndex(m_curQuestionNumber);
}

void MainGameScene::nextQuestion(CCObject* pSender)
{
	m_sprGameResult->setVisible(false);

	m_curQuestionNumber++;
	initLevel(m_curQuestionNumber);

	m_isPause = false;
	m_clockCounter = CONF_INT(G_SOLO_TIME_FOR_QUESTION);
	this->schedule(schedule_selector(MainGameScene::scheduleClock), 0.5f);
}

void MainGameScene::initItems()
{
	MY_ADD_SPRITE(sprQuest, "question.png", ccp(400, 1280-537));

	MY_ADD_LABELTTF(_lbScore, CCString::createWithFormat("%d", m_curScore)->getCString(), G_FONT_NORMAL, 48, ccBLACK, ccp(20, 1280-60));
	_lbScore->setAnchorPoint(ANCHOR_LEFT);
	m_lbScore = _lbScore;

	MY_ADD_SPRITE(sprDiamond, "diamond.png", ccp(328, 1280-60));

	int diamond = DataManager::sharedDataManager()->GetDiamond();
	MY_ADD_LABELTTF(_lbDiamond, CCString::createWithFormat("%d", diamond)->getCString(), G_FONT_NORMAL, 48, ccBLACK, ccp(380, 1280-60));
	_lbDiamond->setAnchorPoint(ANCHOR_LEFT);
	m_lbDiamond = _lbDiamond;


	MY_ADD_LABELTTF( _lbClock, CCString::createWithFormat("%d", (int)m_clockCounter)->getCString(), 
		G_FONT_NORMAL, 64, ccBLACK, ccp(400, 1280-200));
	_lbClock->setAnchorPoint(ANCHOR_MID);
	m_lbClock = _lbClock;

	MY_ADD_LABELTTF( _lbNumber, "", G_FONT_NORMAL, 64, ccBLACK, ccp(400, 1280-340));
	m_lbNumber = _lbNumber;

	MY_ADD_LABELTTF( _lbQuestion, "", G_FONT_NORMAL, 48, ccBLACK, ccp(400, 1280-600) );
	m_lbQuestion = _lbQuestion;

	for (int i = 0; i < 4; ++i)
	{
		m_itAnswers[i] = CCMenuItemImage::create("answer.png", "answer_down.png", this, menu_selector(MainGameScene::answerCallback));
		m_itAnswers[i]->setPosition(ccp(400, 1280-843 - i*94));
		m_itAnswers[i]->setTag(i);
	}

	CCMenu* menu = CCMenu::create(m_itAnswers[0], m_itAnswers[1], m_itAnswers[2], m_itAnswers[3], NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	for (int i = 0; i < 4; ++i)
	{
		m_lbAnswers[i] = CCLabelTTF::create("", G_FONT_NORMAL, 48);
		m_lbAnswers[i]->setFontFillColor(ccBLACK);
		m_lbAnswers[i]->setAnchorPoint(ANCHOR_LEFT);
		m_lbAnswers[i]->setPosition(ccp(140, 1280-840 - i*94));
		this->addChild(m_lbAnswers[i]);
	}
}

void MainGameScene::initLevel( int level )
{
	LevelData* ld = LevelManager::shareLevelLoader()->getLevel(level);
	
	m_lbQuestion->setString(ld->m_quest.c_str());
	m_curRightAnswer = ld->m_right; //0 -> 3
	m_lbNumber->setString(CCString::createWithFormat("%d", level)->getCString());

	for (int i = 0; i < 4; ++i)
	{
		m_lbAnswers[i]->setString(ld->m_arrChoice[i].c_str());
	}
}


void MainGameScene::itHelp1Callback( CCObject* pSender )
{

}

void MainGameScene::itHelp2Callback( CCObject* pSender )
{

}

void MainGameScene::itHelp3Callback( CCObject* pSender )
{

}

void MainGameScene::scheduleClock( float dt )
{
	m_clockCounter -= dt;
	m_clockCounter = (m_clockCounter < -1) ? -1 : m_clockCounter;

	CCString* s = CCString::createWithFormat("%d", (int)(m_clockCounter + 1));
	m_lbClock->setString(s->getCString());

	if (m_clockCounter == -1)
	{
		this->unschedule(schedule_selector(MainGameScene::scheduleClock));

		m_lbScore -= CONF_INT(G_SOLO_SUB_SCORE);
		m_isRight = false;
		animationRightChoose();
	}
}

void MainGameScene::animationRightChoose()
{
	m_isPause = true;

	m_itAnswers[m_curRightAnswer]->runAction(
			CCSequence::createWithTwoActions(
				CCRepeat::create(
					CCSequence::create(
						CCTintTo::create(0.15f, 0, 255, 0),
						CCTintTo::create(0.15f, 255, 255, 255),
						NULL
					),
					5
				),
				CCCallFunc::create(this, callfunc_selector(MainGameScene::onFinishAnimationRightChoose))
			)
		);
}

void MainGameScene::onFinishAnimationRightChoose()
{
	m_sprGameResult->setVisible(true);
}




