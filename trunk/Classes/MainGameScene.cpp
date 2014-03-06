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

	CCSprite* bg = CCSprite::create("game_background.png");
	bg->setPosition(ccp(400, 640));
	this->addChild(bg);

	//////////////////////////////////////////////////////////////////////////

	CCMenuItemImage *itBack = CCMenuItemImage::create(
		"back.png",
		"backDown.png",
		this,
		menu_selector(MainGameScene::menuCallback));
	itBack->setAnchorPoint(ccp(0.0f, 0.0f));
	itBack->setPosition(ccp(10, 10));

	CCMenu* pMenu = CCMenu::create(itBack, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	initItems();
	nextQuestion();

	this->setKeypadEnabled(true);
	PLAY_BACKGROUND_MUSIC;
    return true;
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
	CCMenuItemImage* it = (CCMenuItemImage*) pSender;
	int tag = it->getTag();

	if (tag == m_curRightAnswer)
	{
		//CCMessageBox("RIGHT", "ANSWER");
		PLAY_GET_BOMB_EFFECT;
		m_curScore += SOLO_ADD_SCORE;
	}
	else
	{
		//CCMessageBox("WRONG", "ANSWER");
		PLAY_OUT_PORP_EFFECT;
		m_curScore -= SOLO_ADD_SCORE;
	}

	m_lbScore->setString(CCString::createWithFormat("%d", m_curScore)->getCString());
	DataManager::sharedDataManager()->SetSoloScore(m_curScore);
	DataManager::sharedDataManager()->SetSoloLastQuestionIndex(m_curQuestionNumber);

	nextQuestion();

}

void MainGameScene::nextQuestion()
{
	m_curQuestionNumber++;
	initLevel(m_curQuestionNumber);
}

void MainGameScene::initItems()
{
	CCSprite* sprQuest = CCSprite::create("question.png");
	sprQuest->setPosition(ccp(400, 1280-537));
	this->addChild(sprQuest);

	m_lbScore = CCLabelTTF::create(CCString::createWithFormat("%d", m_curScore)->getCString(), "Roboto-Medium.ttf", 72);
	m_lbScore->setFontFillColor(ccc3(0,0,0));
	m_lbScore->setAnchorPoint(ccp(0.0f, 0.5f));
	m_lbScore->setPosition(ccp(23, 1280-43));
	this->addChild(m_lbScore);

	m_lbNumber = CCLabelTTF::create("", "Roboto-Medium.ttf", 64);
	m_lbNumber->setFontFillColor(ccc3(0,0,0));
	m_lbNumber->setAnchorPoint(ccp(0.5f, 0.5f));
	m_lbNumber->setPosition(ccp(400, 1280-340));
	this->addChild(m_lbNumber);

	m_lbQuestion = CCLabelTTF::create("", "Roboto-Medium.ttf", 48);
	m_lbQuestion->setFontFillColor(ccc3(0,0,0));
	m_lbQuestion->setAnchorPoint(ccp(0.5f, 0.5f));
	m_lbQuestion->setPosition(ccp(400, 1280-600));
	this->addChild(m_lbQuestion);

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
		m_lbAnswers[i] = CCLabelTTF::create("", "Roboto-Medium.ttf", 48);
		m_lbAnswers[i]->setFontFillColor(ccc3(0,0,0));
		m_lbAnswers[i]->setAnchorPoint(ccp(0.0f, 0.5f));
		m_lbAnswers[i]->setPosition(ccp(140, 1280-840 - i*94));
		this->addChild(m_lbAnswers[i]);
	}
}

void MainGameScene::initLevel( int level )
{
	LevelData* ld = LevelManager::shareLevelLoader()->getLevel(level);
	
	m_lbQuestion->setString(ld->m_quest.c_str());
	m_curRightAnswer = ld->m_answer; //0 -> 3
	m_lbNumber->setString(CCString::createWithFormat("%d", level)->getCString());

	for (int i = 0; i < 4; ++i)
	{
		m_lbAnswers[i]->setString(ld->m_arrChoice[i].c_str());
	}
}


