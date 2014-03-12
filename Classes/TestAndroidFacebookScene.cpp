#include "TestAndroidFacebookScene.h"
#include "MenuScene.h"
#include "MyMacro.h"
#include "NDKHelper\NDKHelper.h"


TestAndroidFacebookScene::~TestAndroidFacebookScene()
{
	NDKHelper::RemoveSelectorsInGroup("HelloWorldSelectors");
}

CCScene* TestAndroidFacebookScene::scene()
{
    CCScene *scene = CCScene::create();
    TestAndroidFacebookScene *layer = TestAndroidFacebookScene::create();
    scene->addChild(layer);
    return scene;
}

bool TestAndroidFacebookScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	MY_ADD_SPRITE(bg, "menu_background.png", ccp(400, 640));

	CCMenu *menuRequest = CCMenu::create();
	menuRequest->setPosition(CCPointZero);
	addChild(menuRequest);


	// log in
	CCLabelTTF *labelPost1 = CCLabelTTF::create("Log In", "Arial", 48);
	labelPost1->setFontFillColor(ccc3(0,0,0));
	CCMenuItemLabel *itemPost1 = CCMenuItemLabel::create(labelPost1, this, menu_selector(TestAndroidFacebookScene::LogIn));
	itemPost1->setAnchorPoint(ccp(0.0f, 0.5f));
	itemPost1->setPosition(ccp(20, 1220));
	menuRequest->addChild(itemPost1);
	

	// get Profile
	CCLabelTTF *labelPost2 = CCLabelTTF::create("Get Profile", "Arial", 48);
	labelPost2->setFontFillColor(ccc3(0,0,0));
	CCMenuItemLabel *itemPost2 = CCMenuItemLabel::create(labelPost2, this, menu_selector(TestAndroidFacebookScene::GetProfile));
	itemPost2->setAnchorPoint(ccp(0.0f, 0.5f));
	itemPost2->setPosition(ccp(20, 1160));
	menuRequest->addChild(itemPost2);

	//Log Out
	CCLabelTTF *labelPost3 = CCLabelTTF::create("Log Out", "Arial", 48);
	labelPost3->setFontFillColor(ccc3(0,0,0));
	CCMenuItemLabel *itemPost3 = CCMenuItemLabel::create(labelPost3, this, menu_selector(TestAndroidFacebookScene::LogOut));
	itemPost3->setAnchorPoint(ccp(0.0f, 0.5f));
	itemPost3->setPosition(ccp(20, 1100));
	menuRequest->addChild(itemPost3);

	//Publish Feed
	CCLabelTTF *labelPost4 = CCLabelTTF::create("Publish Feed", "Arial", 48);
	labelPost4->setFontFillColor(ccc3(0,0,0));
	CCMenuItemLabel *itemPost4 = CCMenuItemLabel::create(labelPost4, this, menu_selector(TestAndroidFacebookScene::PublishFeed));
	itemPost4->setAnchorPoint(ccp(0.0f, 0.5f));
	itemPost4->setPosition(ccp(20, 1040));
	menuRequest->addChild(itemPost4);



	this->setKeypadEnabled(true);
    return true;
}

void TestAndroidFacebookScene::keyBackClicked()
{
	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}


//////////////////////////////////////////////////////////////////////////
//Menu

void TestAndroidFacebookScene::LogIn( CCNode* pSender )
{
	NDKHelper::AddSelector(TEST_GROUP_NAME,
		"onLogInCompleted",
		callfuncND_selector(TestAndroidFacebookScene::onLogInCompleted),
		this);

	SendMessageWithParams(string("LogIn"), NULL);
}

void TestAndroidFacebookScene::LogOut( CCNode* pSender )
{
	NDKHelper::AddSelector(TEST_GROUP_NAME,
		"onLogOutCompleted",
		callfuncND_selector(TestAndroidFacebookScene::onLogOutCompleted),
		this);

	SendMessageWithParams(string("LogOut"), NULL);
}

void TestAndroidFacebookScene::GetProfile( CCNode* pSender )
{
	NDKHelper::AddSelector(TEST_GROUP_NAME,
		"onGetProfileCompleted",
		callfuncND_selector(TestAndroidFacebookScene::onGetProfileCompleted),
		this);

	SendMessageWithParams(string("GetProfile"), NULL);
}

void TestAndroidFacebookScene::PublishFeed( CCNode* pSender )
{
	NDKHelper::AddSelector(TEST_GROUP_NAME,
		"onPublishFeedCompleted",
		callfuncND_selector(TestAndroidFacebookScene::onPublishFeedCompleted),
		this);

	//message
	//name
	//caption
	//description
	//picture
	//link
	string withDialog = "true";
	string message = "This is the message";
	string name = "This is the name";
	string caption = "This is the caption";
	string description = "This is the description";
	string picture = "This is the picture";
	string link = "This is the link";


	CCDictionary* prms = CCDictionary::create();
	prms->setObject(CCString::create(withDialog), "withDialog");
	prms->setObject(CCString::create(message), "message");
	prms->setObject(CCString::create(name), "name");
	prms->setObject(CCString::create(caption), "caption");
	prms->setObject(CCString::create(description), "description");
	prms->setObject(CCString::create(picture), "picture");
	prms->setObject(CCString::create(link), "link");
	
	SendMessageWithParams(string("PublishFeed"), prms);
}

//////////////////////////////////////////////////////////////////////////
//Callback

void TestAndroidFacebookScene::onLogInCompleted( CCNode *sender, void *data )
{
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Log In Completed: TRUE");
		} 
		else
		{
			CCLOG("CPP Log In Completed: FALSE");
		}
	}
}

void TestAndroidFacebookScene::onLogOutCompleted( CCNode *sender, void *data )
{
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Log Out Completed: TRUE");
		} 
		else
		{
			CCLOG("CPP Log Out Completed: FALSE");
		}
	}
}

void TestAndroidFacebookScene::onGetProfileCompleted( CCNode *sender, void *data )
{
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Get Profile Completed: TRUE");

			CCString* s;
			s = (CCString*)convertedData->objectForKey("id");			CCLOG("id = %s", s->getCString());
			s = (CCString*)convertedData->objectForKey("firstName");	CCLOG("firstName = %s", s->getCString());
			s = (CCString*)convertedData->objectForKey("name");			CCLOG("name = %s", s->getCString());
			s = (CCString*)convertedData->objectForKey("birthday");		CCLOG("birthday = %s", s->getCString());
			s = (CCString*)convertedData->objectForKey("picture");		CCLOG("picture = %s", s->getCString());
		} 
		else
		{
			CCLOG("CPP Get Profile Completed: FALSE");
		}		
	}
}

void TestAndroidFacebookScene::onPublishFeedCompleted( CCNode *sender, void *data )
{
	if (data != NULL)
	{
		CCDictionary *convertedData = (CCDictionary *)data;
		CCString* s = (CCString*)convertedData->objectForKey("isSuccess");
		if (s->boolValue())
		{
			CCLOG("CPP Publish Feed Completed: TRUE");
		} 
		else
		{
			CCLOG("CPP Publish Feed Completed: FALSE");
		}
	}
}
