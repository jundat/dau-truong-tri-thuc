#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"
#include "EffectLayer.h"


USING_NS_CC;


class SoloGameScene : public cocos2d::CCLayerColor
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
	CREATE_FUNC(SoloGameScene);

	virtual void onEnterTransitionDidFinish();

	void menuCallback(CCObject* pSender);
	virtual void keyBackClicked();
	void nextQuestion(CCObject* pSender);
	void initLevel(int level);
	void initItems();
	void answerCallback(CCObject* pSender);
	void animationRightChoose();
	void onFinishAnimationRightChoose();

	void itHelp1Callback(CCObject* pSender);
	void itHelp2Callback(CCObject* pSender);
	void itHelp3Callback(CCObject* pSender);

	void scheduleClock(float dt);

public:
	int m_curScore;
	int m_curQuestionNumber;
	int m_curRightAnswer;
	float m_clockCounter;
	bool m_isRight;
	bool m_isPause;
	int m_curDisableChoose;

	CCLabelTTF* m_lbClock;
	CCLabelTTF* m_lbDiamond;
	CCLabelTTF* m_lbScore;
	CCLabelTTF* m_lbNumber;
	CCLabelTTF* m_lbQuestion;
	CCLabelTTF* m_lbAnswers[4];
	CCMenuItemImage* m_itAnswers[4];
	CCMenu* 	m_menu;
	CCSprite* m_sprGameResult;
};

#endif // __MAIN_GAME_SCENE_H__
