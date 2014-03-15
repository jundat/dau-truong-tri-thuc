/*
 * TutorialScene.h
 *
 *  Created on: 20 Oct 2012
 *      Author: Loc
 */

#ifndef TUTORIALSCENE_H_
#define TUTORIALSCENE_H_

#include "cocos2d.h"
USING_NS_CC;


class TutorialScene : public CCLayer
{
public:
	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(TutorialScene);

	void onTouchbtnNext (CCObject* pSender);
	void onTouchbtnPrev (CCObject* pSender);
	void onTouchbtnHome (CCObject* pSender);
	
	void initControll ();
	CCLayer* initLayerContent(int pageIndex);
	void onChangeLayerComplete(CCNode* psender);

private:
	CCSprite* m_pSpritebackground;
	CCLayer* m_pLayerControll;
	CCLayer* m_pLayerContent;
	int m_index, //trang hien tai
		m_total; //tong so trang
};

#endif /* TUTORIALSCENE_H_ */
