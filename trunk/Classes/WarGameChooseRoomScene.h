#ifndef __WAR_GAME_CHOOSE_ROOM_SCENE_H__
#define __WAR_GAME_CHOOSE_ROOM_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include <algorithm>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


class Subject : public CCObject
{
public:
	int subjectId;
	string subjectName;

public:
	Subject() 
	{
		subjectId = -1;
		subjectName = string();
	}

	Subject(int id, const char* name)
	{
		subjectId = id;
		subjectName = string(name);
	}

	static Subject* create(int id, const char* name)
	{
		Subject* sub = new Subject(id, name);
		sub->autorelease();
		return sub;
	}

	CCObject* copyWithZone(CCZone *pZone)
	{
		CCZone *pNewZone = NULL;
		Subject *pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
		{
			pRet = (Subject*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new Subject();
			pZone = pNewZone = new CCZone(pRet);
		}
		CCObject::copyWithZone(pZone);
		//copy subdata

		pRet->subjectId = subjectId;
		pRet->subjectName = string(subjectName);		

		CC_SAFE_DELETE(pNewZone);
		return pRet;
	}
};


class War
{
public:
	string oppId;
	string oppName;
	int oppWin;
	int oppLose;

	string quest;
	string answers[4];
	int right;
};


class WarGameChooseRoomScene : public cocos2d::CCLayer,
	public cocos2d::extension::CCTableViewDataSource, 
	public cocos2d::extension::CCTableViewDelegate
{
public:
	virtual bool init();
	CREATE_FUNC(WarGameChooseRoomScene);
	static cocos2d::CCScene* scene() ;

	void startCallback(CCObject* pSender);
	void menuCallback(CCObject* pSender);
	virtual void keyBackClicked();

	virtual void onEnterTransitionDidFinish();
	void onGetSubjectListCompleted(CCHttpClient *sender, CCHttpResponse *response);
	void onJoinCompleted( CCHttpClient *sender, CCHttpResponse *response );
	void gotoMaingame();

	//table delegate
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	//table delegate


public: 
	int m_numberOfSubject;
	CCArray* m_arrSubjects;
	CCTableView* m_tableSubjects;
	CCSize m_cellSize;
	int m_curSubjectId;
	CCSprite* m_cellSelect;
	War* m_curWar;
};

#endif // __WAR_GAME_CHOOSE_ROOM_SCENE_H__
