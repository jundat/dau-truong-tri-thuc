#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include <algorithm>

USING_NS_CC;
USING_NS_CC_EXT;

class ScoreScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(ScoreScene);
	static cocos2d::CCScene* scene() ;

	void menuCallback(CCObject* pSender);
	virtual void keyBackClicked();
	void onSendRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
};

#endif // __SCORE_SCENE_H__
