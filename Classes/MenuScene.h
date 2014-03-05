#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "MyMacro.h"

USING_NS_CC;


class MenuScene : public cocos2d::CCLayerColor
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(MenuScene);
	
	virtual void keyBackClicked();
    void playSoloCallback(CCObject* pSender);
	void playWarCallback(CCObject* pSender);	
	void scoreCallback(CCObject* pSender);
	void achievementCallback(CCObject* pSender);
	void facebookCallback(CCObject* pSender);
	void guideCallback(CCObject* pSender);
	void soundCallback(CCObject* pSender);
};

#endif // __MENU_SCENE_H__
