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

public:
	CCMenu* m_menu;
	CCMenuItemImage* m_itFacbook;

public:
	
	void onShowDialog();
	void onCloseDialog();
	virtual void keyBackClicked();
    void playSoloCallback(CCObject* pSender);
	void playWarCallback(CCObject* pSender);	
	void scoreCallback(CCObject* pSender);
	void moreDiamondCallback(CCObject* pSender);
	void guideCallback(CCObject* pSender);
	void settingCallback(CCObject* pSender);
	void soundCallback(CCObject* pSender);
	void facebookCallback(CCObject* pSender);
	void checkLogIn(CCObject* pSender);

	void onLogInCompleted(CCNode *sender, void *data);
	void onGetProfileCompleted( CCNode *sender, void *data );
	void onGetAvatarCompleted( CCNode* pSender, void *data );

	void onCheckLogInCompleted(CCNode *sender, void *data);
};

#endif // __MENU_SCENE_H__
