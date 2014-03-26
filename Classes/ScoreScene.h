#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "NDKHelper/NDKHelper.h"
#include "FriendLeaderboardLayer.h"

#include <algorithm>

USING_NS_CC;
USING_NS_CC_EXT;

class ScoreScene : public cocos2d::CCLayer, public GameClientDelegate
{
public:
	virtual bool init();
	CREATE_FUNC(ScoreScene);
	static cocos2d::CCScene* scene() ;

	void menuCallback(CCObject* pSender);
	virtual void keyBackClicked();
	void onSendRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
	virtual void onEnterTransitionDidFinish();

	void getFacebookScores();
	void onGetScoresCompleted( CCNode *sender, void *data );

	void loginFacebook( CCObject* pSender );
	void onLogInCompleted(CCNode *sender, void *data);
	void onGetProfileCompleted( CCNode *sender, void *data );
	void onGetAvatarCompleted( CCNode* pSender, void *data );

public:
	CCArray* m_arrFriendSoloScores;
	CCArray* m_arrFriendWarScores;
	CCArray* m_arrWorldSoloScores;
	CCArray* m_arrWorldWarScores;

	FriendLeaderboardLayer* m_friendSoloBoard;

};

#endif // __SCORE_SCENE_H__
