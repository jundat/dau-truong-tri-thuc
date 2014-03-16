#pragma once

#ifndef __LEVEL_LOADER_H__
#define __LEVEL_LOADER_H__

#include "Global.h"
#include "MyMacro.h"
#include "cocos2d.h"
#include "jansson/jansson.h"

USING_NS_CC;
using namespace std;


#define LEVEL_FILE		"questions.json"



class LevelData : public CCObject {
public:
	LevelData(){};
	LevelData(int id, string quest, string a, string b, string c, string d, int right) {
		m_id = id;
		m_quest = string(quest);

		m_arrChoice[0] = string(a);
		m_arrChoice[1] = string(b);
		m_arrChoice[2] = string(c);
		m_arrChoice[3] = string(d);
		
		m_right = right;
	}

	LevelData Clone() {
		LevelData newLd;

		newLd.m_id = m_id;
		newLd.m_quest = string(this->m_quest);
		
		newLd.m_arrChoice[0] = string(this->m_arrChoice[0]);
		newLd.m_arrChoice[1] = string(this->m_arrChoice[1]);
		newLd.m_arrChoice[2] = string(this->m_arrChoice[2]);
		newLd.m_arrChoice[3] = string(this->m_arrChoice[3]);

		newLd.m_right = this->m_right;

		return newLd;
	}

	static LevelData* create(int id, string quest, string a, string b, string c, string d, int answer) {
		LevelData* ld = new LevelData(id, quest,  a,  b,  c,  d,  answer);
		ld->autorelease();
		return ld;
	}

	CCObject* copyWithZone(CCZone *pZone)
	{
		CCZone *pNewZone = NULL;
		LevelData *pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
		{
			pRet = (LevelData*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new LevelData();
			pZone = pNewZone = new CCZone(pRet);
		}
		CCObject::copyWithZone(pZone);
		// copy member data
		
		pRet->m_id = m_id;
		pRet->m_quest = string(m_quest);
		pRet->m_arrChoice[0] = string(m_arrChoice[0]);
		pRet->m_arrChoice[1] = string(m_arrChoice[1]);
		pRet->m_arrChoice[2] = string(m_arrChoice[2]);
		pRet->m_arrChoice[3] = string(m_arrChoice[3]);
		pRet->m_right = m_right;

		CC_SAFE_DELETE(pNewZone);
		return pRet;
	}

	const char* toString() {
		CCString* s = CCString::createWithFormat("%d - Quest: %s\nA: %s\nB: %s\nC: %s\nD: %s\nAnswer: %d",
			m_id,
			m_quest.c_str(),
			m_arrChoice[0].c_str(),
			m_arrChoice[1].c_str(),
			m_arrChoice[2].c_str(),
			m_arrChoice[3].c_str(),
			m_right
			);
		return s->getCString();
	}

	int m_id;
	string m_quest;
	string m_arrChoice[4];
	int m_right;
};


class LevelManager
{
public:
	LevelManager(void);
	~LevelManager(void){
		MY_RELEASE(m_dict);
	}

	static LevelManager* shareLevelLoader();
	LevelData* getLevelInRandom(int idx);
	
public:
	CCDictionary* m_dict;
	json_t* m_questionsObject;

protected:
	LevelData* getLevel(int level);
	static LevelManager* s_instance;

public:
	static bool sortPairIntInt (PairIntInt* a, PairIntInt* b) 
	{
		return (a->keyRd < b->keyRd);
	};
};


#endif //__LEVEL_LOADER_H__