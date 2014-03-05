#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"
#include "EffectLayer.h"


USING_NS_CC;

#define SOLO_ADD_SCORE		10
#define WAR_ADD_SCORE		20

#define SOLO_SUB_SCORE		10
#define WAR_SUB_SCORE		20


class MainGameScene : public cocos2d::CCLayerColor
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
	CREATE_FUNC(MainGameScene);

	void menuCallback(CCObject* pSender);
	virtual void keyBackClicked();
	void nextQuestion();
	void initLevel(int level);
	void initItems();
	void answerCallback(CCObject* pSender);

public:
	int m_curScore;
	int m_curQuestionNumber;
	int m_curRightAnswer;

	CCLabelTTF* m_lbScore;
	CCLabelTTF* m_lbNumber;
	CCLabelTTF* m_lbQuestion;
	CCLabelTTF* m_lbAnswers[4];
	CCMenuItemImage* m_itAnswers[4];
};

#endif // __MAIN_GAME_SCENE_H__
