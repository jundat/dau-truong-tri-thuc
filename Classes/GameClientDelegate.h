#ifndef __GAME_CLIENT_DELEGATE_H__
#define __GAME_CLIENT_DELEGATE_H__

#include "cocos2d.h"
#include "GameClientObjects.h"

USING_NS_CC;

class GameClientDelegate
{
public:

	virtual void onSendUserProfileCompleted( bool isSuccess ){}
	virtual void onGetUserProfileCompleted(bool isSuccess, UserProfile* acc){}

	virtual void onSendFriendListCompleted( bool isSuccess ){}
	//array of FacebookAccount (our code)
	virtual void onGetFriendListCompleted( bool isSuccess, CCArray* arrFriends){}

	virtual void onSendDeviceProfileCompleted( bool isSuccess ){}
	virtual void onGetDeviceProfileCompleted(bool isSuccess, DeviceProfile* deviceProfile){}

	virtual void onSendScoreCompleted( bool isSuccess ){}
	virtual void onGetScoreCompleted( bool isSuccess, int score, std::string time ){}

// 	virtual void onSendItemsCompleted( bool isSuccess, int newScore ){}
// 	virtual void onGetItemsCompleted(bool isSuccess, CCArray* arrGameItems){}
};


#endif //__GAME_CLIENT_DELEGATE_H__