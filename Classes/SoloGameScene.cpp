#include "SoloGameScene.h"
#include "AudioManager.h"
#include "MenuScene.h"
#include "DataManager.h"
#include <time.h>
#include "PauseDialog.h"
#include "LevelManager.h"

USING_NS_CC;



CCScene* SoloGameScene::scene()
{
    CCScene *scene = CCScene::create();
    SoloGameScene *layer = SoloGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool SoloGameScene::init()
{
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
    {
        return false;
    }
	
	m_curScore = DataManager::sharedDataManager()->GetSoloScore();
	m_curQuestionNumber = DataManager::sharedDataManager()->GetSoloLastQuestionIndex();
	m_curRightAnswer = -1;
	m_clockCounter = CONF_INT(SOLO_TIME_FOR_QUESTION);
	m_isRight = false;
	m_isPause = false;
	m_curDisableChoose = 4;

	MY_ADD_SPRITE(bg, "game_background.png", ccp(400, 640));
	
	MY_ADD_SPRITE(avatar, "avatar.png", ccp(86, 1280-86));

	string name = DataManager::sharedDataManager()->GetName();
	name = MY_LIMIT_STR(name, 12, "..");
	MY_ADD_LABELTTF(lbName, name.c_str(), CONF_STR(FONT_NORMAL), 36, ccBLACK, ccp(86, 1280-195));

	MY_ADD_SPRITE(score, "score.png", ccp(203, 1280-41));
	MY_ADD_LABELTTF(_lbScore, CCString::createWithFormat("%d", m_curScore)->getCString(), CONF_STR(FONT_NORMAL), 48, ccBLACK, ccp(240, 1280-46));
	_lbScore->setAnchorPoint(ANCHOR_LEFT);
	m_lbScore = _lbScore;

	MY_ADD_SPRITE(sprDiamond, "diamond.png", ccp(203, 1280-100));
	int diamond = DataManager::sharedDataManager()->GetDiamond();
	MY_ADD_LABELTTF(_lbDiamond, CCString::createWithFormat("%d", diamond)->getCString(), CONF_STR(FONT_NORMAL), 48, ccBLACK, ccp(240, 1280-100));
	_lbDiamond->setAnchorPoint(ANCHOR_LEFT);
	m_lbDiamond = _lbDiamond;
	
	MY_ADD_SPRITE(sprClock, "clock.png", ccp(400, 1280-200));

	MY_ADD_LABELTTF( _lbClock, CCString::createWithFormat("%d", (int)m_clockCounter)->getCString(), 
		CONF_STR(FONT_NORMAL), 64, ccBLACK, sprClock->getPosition());
	_lbClock->setAnchorPoint(ANCHOR_MID);
	m_lbClock = _lbClock;

	MY_ADD_MENU_ITEM(itBack, "back.png", "backDown.png", "backDown.png", SoloGameScene::menuCallback, ccp(60, 60));
	
	//HELP

	MY_ADD_MENU_ITEM(itHelp1, "help1.png", "help1Down.png", "help1Down.png", SoloGameScene::itHelp1Callback, ccp(740, 1280-60));
	MY_ADD_MENU_ITEM(itHelp2, "help2.png", "help2Down.png", "help2Down.png", SoloGameScene::itHelp2Callback, ccp(640, 1280-60));
	MY_ADD_MENU_ITEM(itHelp3, "help3.png", "help3Down.png", "help3Down.png", SoloGameScene::itHelp3Callback, ccp(540, 1280-60));

	initItems();

	MY_ADD_SPRITE(_sprGameResult, "game_result.png", ccp(400, 640));
	m_sprGameResult = _sprGameResult;
	m_sprGameResult->setVisible(false);

	CCLabelTTF* changeScore = CCLabelTTF::create("", CONF_STR(FONT_NORMAL), 48);
	changeScore->setFontFillColor(ccBLACK);
	changeScore->setPosition(ccp(400, m_sprGameResult->getContentSize().height * 3/4.0f));
	changeScore->setTag(1);
	m_sprGameResult->addChild(changeScore);

	MY_CREATE_MENU_ITEM(itNext, "next.png", "next.png", "next.png", SoloGameScene::nextQuestion, ccp(400, m_sprGameResult->getContentSize().height/2));
	m_sprGameResult->addChild(menuitNext);

	nextQuestion(NULL);
	
	PLAY_BACKGROUND_MUSIC;
    return true;
}

void SoloGameScene::onEnterTransitionDidFinish()
{
	this->schedule(schedule_selector(SoloGameScene::scheduleClock), 0.5f);
	this->setKeypadEnabled(true);
}

void SoloGameScene::menuCallback(CCObject* pSender)
{
	PLAY_BUTTON_EFFECT;

	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void SoloGameScene::keyBackClicked()
{
	menuCallback(NULL);
}

void SoloGameScene::answerCallback( CCObject* pSender )
{
	if (m_isPause)
	{
		return;
	}
	
	this->unschedule(schedule_selector(SoloGameScene::scheduleClock));

	CCMenuItemImage* it = (CCMenuItemImage*) pSender;
	it->selected();
	int tag = it->getTag();

	if (tag == m_curRightAnswer)
	{
		//CCMessageBox("RIGHT", "ANSWER");
		PLAY_GET_BOMB_EFFECT;
		m_curScore += CONF_INT(SOLO_ADD_SCORE);
		m_isRight = true;
	}
	else
	{
		//CCMessageBox("WRONG", "ANSWER");
		PLAY_OUT_PORP_EFFECT;
		m_curScore -= CONF_INT(SOLO_SUB_SCORE);
		if(m_curScore < 0) m_curScore = 0;
		m_isRight = false;
	}

	animationRightChoose();
	m_lbScore->setString(CCString::createWithFormat("%d", m_curScore)->getCString());
	DataManager::sharedDataManager()->SetSoloScore(m_curScore);
}

void SoloGameScene::nextQuestion(CCObject* pSender)
{
	//UI
	m_sprGameResult->setVisible(false);
	for (int i = 0; i < 4; ++i)
	{
		m_itAnswers[i]->setEnabled(true);
		m_itAnswers[i]->setVisible(true);
		m_itAnswers[i]->unselected();
	}
	
	DataManager::sharedDataManager()->SetSoloLastQuestionIndex(m_curQuestionNumber);
	m_curQuestionNumber++;
	initLevel(m_curQuestionNumber);

	m_isPause = false;
	m_curDisableChoose = 0;
	m_clockCounter = CONF_INT(SOLO_TIME_FOR_QUESTION);
	this->schedule(schedule_selector(SoloGameScene::scheduleClock), 0.5f);
}

void SoloGameScene::initItems()
{
	MY_ADD_SPRITE(sprQuest, "question.png", ccp(400, 1280-537));
	
	MY_ADD_LABELTTF( _lbNumber, "", CONF_STR(FONT_NORMAL), 64, ccBLACK, ccp(400, 1280-340));
	m_lbNumber = _lbNumber;

	MY_ADD_LABELTTF( _lbQuestion, "", CONF_STR(FONT_NORMAL), 48, ccBLACK, ccp(400, 1280-600) );
	m_lbQuestion = _lbQuestion;

	for (int i = 0; i < 4; ++i)
	{
		m_itAnswers[i] = CCMenuItemImage::create("answer.png", "answer_down.png", "answer_disable.png", this, menu_selector(SoloGameScene::answerCallback));
		m_itAnswers[i]->setPosition(ccp(400, 1280-843 - i*94));
		m_itAnswers[i]->setTag(i);
	}

	CCMenu* menu = CCMenu::create(m_itAnswers[0], m_itAnswers[1], m_itAnswers[2], m_itAnswers[3], NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	for (int i = 0; i < 4; ++i)
	{
		m_lbAnswers[i] = CCLabelTTF::create("", CONF_STR(FONT_NORMAL), 48);
		m_lbAnswers[i]->setFontFillColor(ccBLACK);
		m_lbAnswers[i]->setAnchorPoint(ANCHOR_LEFT);
		m_lbAnswers[i]->setPosition(ccp(140, 1280-840 - i*94));
		this->addChild(m_lbAnswers[i]);
	}
}

void SoloGameScene::initLevel( int level )
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


void SoloGameScene::itHelp1Callback( CCObject* pSender )
{
	if (m_isPause)
	{
		return;
	}
	
	//CCMessageBox("Help1", "Info");
	int diamond = DataManager::sharedDataManager()->GetDiamond();
	if (diamond < CONF_INT(DIAMON_PER_HELP1))
	{
		PLAY_OUT_PORP_EFFECT;
		return;
	}
	
	if (m_curDisableChoose >= 2)
	{
		PLAY_OUT_PORP_EFFECT;
		return;
	}
	

	bool isOK = false;
	while(isOK == false)
	{
		int rd = (int)(CCRANDOM_0_1() * 4);
		
		if (rd != m_curRightAnswer)
		{
			if (m_itAnswers[rd]->isEnabled())
			{
				m_itAnswers[rd]->setEnabled(false);
				m_curDisableChoose++;
				
				DataManager::sharedDataManager()->AddDiamond(- CONF_INT(DIAMON_PER_HELP1));
				m_lbDiamond->setString(CCString::createWithFormat("%d", DataManager::sharedDataManager()->GetDiamond())->getCString());
				PLAY_GET_BOMB_EFFECT;
				isOK = true;
			}			
		}
	}
}

void SoloGameScene::itHelp2Callback( CCObject* pSender )
{
	CCMessageBox("not implement", "Info");
}

void SoloGameScene::itHelp3Callback( CCObject* pSender )
{
	if (m_isPause)
	{
		return;
	}

	//CCMessageBox("Help3", "Info");
	int diamond = DataManager::sharedDataManager()->GetDiamond();
	if (diamond < CONF_INT(DIAMON_PER_HELP3))
	{
		PLAY_OUT_PORP_EFFECT;
		return;
	}


	DataManager::sharedDataManager()->AddDiamond(- CONF_INT(DIAMON_PER_HELP3));
	m_lbDiamond->setString(CCString::createWithFormat("%d", DataManager::sharedDataManager()->GetDiamond())->getCString());
	PLAY_GET_BOMB_EFFECT;

	nextQuestion(NULL);
}

void SoloGameScene::scheduleClock( float dt )
{
	m_clockCounter -= dt;
	m_clockCounter = (m_clockCounter < -1) ? -1 : m_clockCounter;

	CCString* s = CCString::createWithFormat("%d", (int)(m_clockCounter + 1));
	m_lbClock->setString(s->getCString());

	if (m_clockCounter == -1)
	{
		this->unschedule(schedule_selector(SoloGameScene::scheduleClock));

		m_lbScore -= CONF_INT(SOLO_SUB_SCORE);
		if(m_curScore < 0) m_curScore = 0;
		m_isRight = false;
		animationRightChoose();
	}
}

void SoloGameScene::animationRightChoose()
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
				CCCallFunc::create(this, callfunc_selector(SoloGameScene::onFinishAnimationRightChoose))
			)
		);
}

void SoloGameScene::onFinishAnimationRightChoose()
{
	m_sprGameResult->setVisible(true);
	
	CCLabelTTF* changeScore = dynamic_cast<CCLabelTTF*>(m_sprGameResult->getChildByTag(1));

	if (NULL != changeScore)
	{
		if (m_isRight)
		{
			changeScore->setString(CCString::createWithFormat("+%d", CONF_INT(SOLO_ADD_SCORE))->getCString());
		} 
		else
		{
			changeScore->setString(CCString::createWithFormat("-%d", CONF_INT(SOLO_SUB_SCORE))->getCString());
		}
	}
}
