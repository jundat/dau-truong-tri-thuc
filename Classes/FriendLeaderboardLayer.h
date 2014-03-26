#ifndef __FRIEND_LEADER_BOARD_H__
#define __FRIEND_LEADER_BOARD_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


class FriendLeaderboardLayer : public cocos2d::CCLayer,
	public cocos2d::extension::CCTableViewDataSource, 
	public cocos2d::extension::CCTableViewDelegate
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(FriendLeaderboardLayer);
	
	void updateData(CCArray* arrFriendSoloScores);

	//table delegate
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	//table delegate

public:
	CCArray* m_arrScores;
	CCTableView* m_table;
};


#endif //__FRIEND_LEADER_BOARD_H__