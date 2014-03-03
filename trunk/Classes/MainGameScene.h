#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"
#include "EffectLayer.h"


USING_NS_CC;

class MainGameScene : public cocos2d::CCLayerColor
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
	CREATE_FUNC(MainGameScene);

	void menuCallback(CCObject* pSender);
	virtual void keyBackClicked();
};

#endif // __MAIN_GAME_SCENE_H__
