#ifndef __ADVISE_FACEBOOK_DIALOG_H__
#define __ADVISE_FACEBOOK_DIALOG_H__

#include "cocos2d.h"
USING_NS_CC;

class AdviseFacebookDialog : public cocos2d::CCLayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(AdviseFacebookDialog);

public:
	void yesCallback(CCObject* pSender);
	void noCallback( CCObject* pSender );
	
	void onError();
	void onLogInCompleted(CCNode *sender, void *data);
	void onGetProfileCompleted( CCNode *sender, void *data );
	void onGetAvatarCompleted( CCNode* pSender, void *data );

};

#endif // __ADVISE_FACEBOOK_DIALOG_H__
