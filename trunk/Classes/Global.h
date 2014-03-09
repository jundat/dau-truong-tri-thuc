#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <string>
#include "ConfigLoader.h"


//////////////////////////////////////////////////////////////////////////
//MACRO

#define CONF_BOOL(config)		ConfigLoader::shareConfigLoader()->getBoolValue(#config)
#define CONF_INT(config)		ConfigLoader::shareConfigLoader()->getIntValue(#config)
#define CONF_FLOAT(config)		ConfigLoader::shareConfigLoader()->getFloatValue(#config)
#define CONF_STR(config)		ConfigLoader::shareConfigLoader()->getStringValue(#config)


//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//CONSTANT
#define G_CCWHITE4				ccc4(255, 255, 255, 255)
#define G_FONT_NORMAL			"Roboto-Medium.ttf"
#define G_FONT_LEADERBOARD		"Villa.ttf"

#define G_NUMBER_FRIEND_TO_GET	100

//GAME CONSTANT
#define G_APP_ID				"Exeption_DTTT"
#define G_DEFAULT_NAME			"Việt Nam"
#define G_AVATAR_SIZE			128

#define G_CHECK_INSTALLED		"CHECK_INSTALLED"
#define G_INSTALLED				1
#define G_FPS					1/60.0f
#define G_SMALL_DEVIVE_SIZE		320
#define	G_DEFAULT_VOLUME		0.25f


//////////////////////////////////////////////////////////////////////////
//

#define		G_IS_TEST_POSTGET

//URL
#define     G_URL_PROFILE
#define     G_URL_DEVICE
#define     G_URL_FRIEND
#define     G_URL_SCORE


//////////////////////////////////////////////////////////////////////////
//VARIANT


#define    	G_DESIGN_WIDTH
#define    	G_DESIGN_HEIGHT
#define    	G_SCALE_FACTOR

#define    	G_DEFAULT_DIAMON
#define    	G_DIAMON_PER_LIFE
#define		G_DIAMON_PER_HELP1
#define		G_DIAMON_PER_HELP2
#define		G_DIAMON_PER_HELP3
#define    	G_TIME_TO_REFRESH_FRIENDS

#define		G_SOLO_TIME_FOR_QUESTION
#define		G_SOLO_ADD_SCORE
#define		G_SOLO_SUB_SCORE

#define		G_WAR_TIME_FOR_QUESTION
#define		G_WAR_ADD_SCORE
#define		G_WAR_SUB_SCORE

#endif //__GLOBAL_H__
