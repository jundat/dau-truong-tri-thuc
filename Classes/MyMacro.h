#ifndef __MY_MACRO_H__
#define __MY_MACRO_H__

#include "cocos2d.h"
USING_NS_CC;


#define MY_LIMIT_VALUE(x, minX, maxX) \
{\
	if(x < minX) { x = minX; }\
	if(x > maxX) { x = maxX; }\
}


#define MY_RELEASE(pObj) \
do\
{\
	if((pObj) != NULL) {\
		(pObj)->release();\
		delete (pObj);\
		(pObj) = NULL;\
	}\
} while(0)


#define MY_ADD_SPRITE(sprName, sprFile, pos) \
do\
{\
	CCSprite* sprName = CCSprite::create(#sprFile);\
	sprName->setPosition(pos);\
	this->addChild(sprName);\
} while(0)


//Create get/set function in DataManager
#define MY_CREATE_FUNCTION(varType, funName, keyword, defaultValue)\
public: varType Get##funName(void) {\
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(#keyword, defaultValue);\
}\
public: void Set##funName(varType var) {\
	CCUserDefault::sharedUserDefault()->setIntegerForKey(#keyword, var);\
	CCUserDefault::sharedUserDefault()->flush();\
}

// \
// public: void add##funName(varType addValue) {\
// 	varType oldValue = get##funName(void);\
// 	CCUserDefault::sharedUserDefault()->setIntegerForKey(#keyword, oldValue + addValue);\
// 	CCUserDefault::sharedUserDefault()->flush();\
// }\
// public: void sub##funName(varType subValue) {\
// 	varType oldValue = get##funName(void);\
// 	CCUserDefault::sharedUserDefault()->setIntegerForKey(#keyword, oldValue - subValue);\
// 	CCUserDefault::sharedUserDefault()->flush();\
// }



#endif //__MY_MACRO_H__
