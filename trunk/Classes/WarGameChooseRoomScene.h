#ifndef __WAR_GAME_CHOOSE_ROOM_SCENE_H__
#define __WAR_GAME_CHOOSE_ROOM_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include <algorithm>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;



class WarGameChooseRoomScene : public cocos2d::CCLayer,
	public cocos2d::extension::CCTableViewDataSource, 
	public cocos2d::extension::CCTableViewDelegate
{
public:
	virtual bool init();
	CREATE_FUNC(WarGameChooseRoomScene);
	static cocos2d::CCScene* scene() ;

	void menuCallback(CCObject* pSender);
	virtual void keyBackClicked();



	//table delegate
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	//table delegate
};

#endif // __WAR_GAME_CHOOSE_ROOM_SCENE_H__
