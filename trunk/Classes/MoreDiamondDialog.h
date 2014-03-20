#ifndef __MORE_DIAMOND_DIALOG_H__
#define __MORE_DIAMOND_DIALOG_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class MoreDiamondDialog : public cocos2d::CCLayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(MoreDiamondDialog);

private:
	CCMenuItemLabel* m_itlbRate;
	CCMenuItemLabel* m_itlbInvite;
	CCMenuItemLabel* m_itlbShare;

	string m_curOperator;

public:
	virtual void keyBackClicked();
	void rateCallback( CCObject* pSender );
	void inviteCallback( CCObject* pSender );
	void shareCallback( CCObject* pSender );

	void onLogInCompleted(CCNode *sender, void *data);
	void onGetProfileCompleted( CCNode *sender, void *data );
	void onGetAvatarCompleted( CCNode* pSender, void *data );

	void onRateCompleted( CCNode *sender, void *data );
	void onInviteAllCompleted( CCNode *sender, void *data );
	void onPublishFeedCompleted( CCNode *sender, void *data );

	void exitCallback( CCObject* pSender );
};

#endif // __MORE_DIAMOND_DIALOG_H__
