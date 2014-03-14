#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include <algorithm>

USING_NS_CC;
USING_NS_CC_EXT;

class SettingScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(SettingScene);
	static cocos2d::CCScene* scene() ;

	void menuCallback(CCObject* pSender);
	virtual void keyBackClicked();
};

#endif // __SETTING_SCENE_H__
