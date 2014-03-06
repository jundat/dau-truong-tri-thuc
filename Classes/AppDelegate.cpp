#include "AppDelegate.h"
#include "Global.h"
#include "MainGameScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "DataManager.h"
#include "ConfigLoader.h"
#include "LevelManager.h"
#include "AudioManager.h"
#include "IntroScene.h"
#include <time.h>
#include "TestPostGetScene.h"


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

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	
#ifdef WIN32
	pEGLView->setFrameSize(G_DESIGN_WIDTH, G_DESIGN_HEIGHT);
	pEGLView->setFrameZoomFactor(G_SCALE_FACTOR);
#endif
	
    pDirector->setOpenGLView(pEGLView);
    pDirector->setAnimationInterval(G_FPS);
	
	CCSize realSize = pEGLView->getFrameSize();
	
	if (realSize.width < G_SMALL_DEVIVE_SIZE) //mini device
	{
		pEGLView->setDesignResolutionSize(G_DESIGN_WIDTH, G_DESIGN_HEIGHT, kResolutionExactFit);
	} 
	else
	{
		pEGLView->setDesignResolutionSize(G_DESIGN_WIDTH, G_DESIGN_HEIGHT, kResolutionShowAll);
	}
	
	AudioManager::sharedAudioManager()->SetVolumeMusic(G_DEFAULT_VOLUME);
	AudioManager::sharedAudioManager()->SetVolumeFX(G_DEFAULT_VOLUME);


    CCScene *pScene = MenuScene::scene(); // TestPostGetScene::scene(); // IntroScene::scene(); //  MenuScene::scene(); //  MainGameScene::scene(); //
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
