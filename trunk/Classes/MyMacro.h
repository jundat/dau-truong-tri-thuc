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


//Create get/set function for integer value in DataManager
#define MY_GETSET_INT_FUNC(funName, keyword, defaultValue)\
public: int Get##funName(void) {\
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(#keyword, defaultValue);\
}\
public: void Set##funName(int var) {\
	CCUserDefault::sharedUserDefault()->setIntegerForKey(#keyword, var);\
	CCUserDefault::sharedUserDefault()->flush();\
}\
public: void Add##funName(int addValue) {\
	int oldValue = Get##funName();\
	CCUserDefault::sharedUserDefault()->setIntegerForKey(#keyword, (oldValue + addValue));\
	CCUserDefault::sharedUserDefault()->flush();\
}


//Create get/set function for string value in DataManager
#define MY_GETSET_STR_FUNC(funName, keyword, defaultValue)\
public: std::string Get##funName(void) {\
	return CCUserDefault::sharedUserDefault()->getStringForKey(#keyword, defaultValue);\
}\
public: void Set##funName(std::string var) {\
	CCUserDefault::sharedUserDefault()->setStringForKey(#keyword, var);\
	CCUserDefault::sharedUserDefault()->flush();\
}


//Create get/set function for float value in DataManager
#define MY_GETSET_FLOAT_FUNC(funName, keyword, defaultValue)\
public: float Get##funName(void) {\
	return CCUserDefault::sharedUserDefault()->getFloatForKey(#keyword, defaultValue);\
}\
public: void Set##funName(float var) {\
	CCUserDefault::sharedUserDefault()->setFloatForKey(#keyword, var);\
	CCUserDefault::sharedUserDefault()->flush();\
}



//Create get/set function for boolean value in DataManager
#define MY_GETSET_BOOL_FUNC(funName, keyword, defaultValue)\
public: bool Get##funName(void) {\
	return CCUserDefault::sharedUserDefault()->getBoolForKey(#keyword, defaultValue);\
}\
public: void Set##funName(bool var) {\
	CCUserDefault::sharedUserDefault()->setFloatForKey(#keyword, var);\
	CCUserDefault::sharedUserDefault()->flush();\
}




#endif //__MY_MACRO_H__
