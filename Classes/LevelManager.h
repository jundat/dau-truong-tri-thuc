#pragma once

#ifndef __LEVEL_LOADER_H__
#define __LEVEL_LOADER_H__

#include "Global.h"
#include "MyMacro.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#define NUM_ENEMY_TYPE	15
#define LEVEL_FILE		"questions.plist"


class LevelData : public CCObject {
public:
	LevelData(){};
	LevelData(string quest, string a, string b, string c, string d, int answer) {
		m_quest = string(quest);

		m_arrChoice[0] = string(a);
		m_arrChoice[1] = string(b);
		m_arrChoice[2] = string(c);
		m_arrChoice[3] = string(d);
		
		m_answer = answer;
	}

	LevelData Clone() {
		LevelData newLd;

		newLd.m_quest = string(this->m_quest);
		
		newLd.m_arrChoice[0] = string(this->m_arrChoice[0]);
		newLd.m_arrChoice[1] = string(this->m_arrChoice[1]);
		newLd.m_arrChoice[2] = string(this->m_arrChoice[2]);
		newLd.m_arrChoice[3] = string(this->m_arrChoice[3]);

		newLd.m_answer = this->m_answer;

		return newLd;
	}

	static LevelData* create(string quest, string a, string b, string c, string d, int answer) {
		LevelData* ld = new LevelData( quest,  a,  b,  c,  d,  answer);
		ld->autorelease();
		return ld;
	}

	const char* ToString() {
		CCString* s = CCString::createWithFormat("Quest: %s\nA: %s\nB: %s\nC: %s\nD: %s\nAnswer: %d",
			m_quest.c_str(),
			m_arrChoice[0].c_str(),
			m_arrChoice[1].c_str(),
			m_arrChoice[2].c_str(),
			m_arrChoice[3].c_str(),
			m_answer
			);
		return s->getCString();
	}

	string m_quest;
	string m_arrChoice[4];
	int m_answer;
};

class LevelManager
{
public:
	LevelManager(void);
	~LevelManager(void){
		MY_RELEASE(m_dict);
	}

	static LevelManager* shareLevelLoader();
	LevelData* getLevel(int level);
	
public:
	CCDictionary* m_dict;

protected:
	static LevelManager* s_instance;
};


#endif //__LEVEL_LOADER_H__