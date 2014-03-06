#ifndef __GUIDE_SCENE_H__
#define __GUIDE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include <algorithm>

USING_NS_CC;
USING_NS_CC_EXT;

class GuideScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(GuideScene);
	static cocos2d::CCScene* scene() ;

	void menuCallback(CCObject* pSender);
	virtual void keyBackClicked();
};

#endif // __GUIDE_SCENE_H__
