#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <string>

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

//URL
extern std::string G_URL_PROFILE;
extern std::string G_URL_FRIEND;
extern std::string G_URL_DEVICE;
extern std::string G_URL_SCORE;


//////////////////////////////////////////////////////////////////////////
//VARIANT


extern int		G_DESIGN_WIDTH;
extern int		G_DESIGN_HEIGHT;
extern float	G_SCALE_FACTOR;

extern int		G_DEFAULT_DIAMON;
extern int		G_DIAMON_PER_LIFE;
extern float	G_TIME_TO_REFRESH_FRIENDS;




#endif //__GLOBAL_H__
