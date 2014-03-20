#include "QuitDialog.h"
#include "MenuScene.h"
#include "DataManager.h"
#include "cocos-ext.h"
#include "MyMacro.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool QuitDialog::init()
{
    if ( !CCLayerColor::initWithColor(DIM_COLOR) )
    {
        return false;
    }

	CCPoint pexit = ccp(250, 1280 - 820);
	CCPoint pask = ccp(800-250, 1280 - 820);


	CCScale9Sprite* dialog = CCScale9Sprite::create("dialog.png");
	dialog->setPosition(ccp(400, 640));
	dialog->setContentSize(CCSizeMake(680, 480));
	this->addChild(dialog);
	
	CCMenuItemImage* exitButton = CCMenuItemImage::create(
		"yes.png",
		"yesDown.png",
		this,
		menu_selector(QuitDialog::yesCallback));
	exitButton->setPosition(pexit);


	CCMenuItemImage* askButton = CCMenuItemImage::create(
		"no.png",
		"noDown.png",
		this,
		menu_selector(QuitDialog::noCallback));
	askButton->setPosition(pask);

	CCMenu* menu = CCMenu::create(exitButton, askButton, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	CCLabelTTF* labelTitle = CCLabelTTF::create("Bạn có muốn\nthoát game?", "Roboto-Medium.ttf", 48);
	labelTitle->setFontFillColor(ccc3(56, 56, 56));
	labelTitle->setColor(ccc3(56, 56, 56));
	labelTitle->setPosition(ccp(400, 660));
	this->addChild(labelTitle);

	this->setKeypadEnabled(true);
    return true;
}

void QuitDialog::yesCallback( CCObject* pSender )
{
	CCDirector::sharedDirector()->end();
}


void QuitDialog::noCallback( CCObject* pSender )
{
	MenuScene* parent = (MenuScene*)this->getParent();
	parent->setTouchEnabled(true);
	parent->onCloseDialog();
	this->removeFromParent();
}

void QuitDialog::keyBackClicked()
{
	noCallback(NULL);
}
