#include "AppDelegate.h"
#include "Global.h"
#include "SoloGameScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "DataManager.h"
#include "ConfigLoader.h"
#include "LevelManager.h"
#include "AudioManager.h"
#include "IntroScene.h"
#include <time.h>
#include "TestPostGetScene.h"
#include "HelloWorldScene.h"


USING_NS_CC;
using namespace CocosDenshion;



AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {

	ConfigLoader::shareConfigLoader();
	LevelManager::shareLevelLoader();

	GameClientManager::sharedGameClientManager()->setUrls(
		CONF_STR(URL_PROFILE),
		CONF_STR(URL_DEVICE),
		CONF_STR(URL_FRIEND),
		CONF_STR(URL_FRIEND)
		);



    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	
#ifdef WIN32
	pEGLView->setFrameSize(CONF_INT(DESIGN_WIDTH), CONF_INT(DESIGN_HEIGHT));
	pEGLView->setFrameZoomFactor(CONF_FLOAT(SCALE_FACTOR));
#endif
	
    pDirector->setOpenGLView(pEGLView);
    pDirector->setAnimationInterval(1.0f / CONF_INT(FPS));
	
	CCSize realSize = pEGLView->getFrameSize();
	
	if (realSize.width < CONF_INT(SMALL_DEVICE_SIZE)) //mini device
	{
		pEGLView->setDesignResolutionSize(CONF_INT(DESIGN_WIDTH), CONF_INT(DESIGN_HEIGHT), kResolutionExactFit);
	} 
	else
	{
		pEGLView->setDesignResolutionSize(CONF_INT(DESIGN_WIDTH), CONF_INT(DESIGN_HEIGHT), kResolutionShowAll);
	}
	
	AudioManager::sharedAudioManager()->SetVolumeMusic(CONF_FLOAT(DEFAULT_VOLUME));
	AudioManager::sharedAudioManager()->SetVolumeFX(CONF_FLOAT(DEFAULT_VOLUME));


    CCScene *pScene;
	if (CONF_BOOL(IS_TEST_POSTGET))
	{
		pScene = TestPostGetScene::scene();
	}
	else
	{
		pScene = HelloWorld::scene(); // MenuScene::scene(); // TestPostGetScene::scene(); // IntroScene::scene(); //  MenuScene::scene(); //  MainGameScene::scene(); //
	}

	pDirector->runWithScene(pScene);

    return true;
}


void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}


void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
