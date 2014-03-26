#include "FriendLeaderboardLayer.h"



void FriendLeaderboardLayer::updateData( CCArray* arrFriendSoloScores )
{
	if (m_arrScores != NULL)
	{
		m_arrScores->release();
		m_arrScores = NULL;
	}

	m_arrScores = CCArray::createWithArray(arrFriendSoloScores);
	m_arrScores->retain();

	//reload table
}

bool FriendLeaderboardLayer::init()
{
	if (! CCLayer::init())
	{
		return false;
	}

	m_arrScores = NULL;

	

	return true;
}

void FriendLeaderboardLayer::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{

}

cocos2d::CCSize FriendLeaderboardLayer::tableCellSizeForIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	return CCSizeMake(0, 0);
}

cocos2d::extension::CCTableViewCell* FriendLeaderboardLayer::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	return new cocos2d::extension::CCTableViewCell();
}

unsigned int FriendLeaderboardLayer::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	if (m_arrScores != NULL)
	{
		return m_arrScores->count();
	}
	
	return 0;
}
