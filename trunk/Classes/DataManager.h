
#ifndef __DATA_MANAGER__
#define __DATA_MANAGER__

#include "cocos2d.h"
#include "MyMacro.h"
#include <time.h>
USING_NS_CC;


class DataManager
{
private:
	DataManager();
	static DataManager *s_instance;

public:
	static DataManager* sharedDataManager();

	std::string GetFbPhotoPath();
	void SetPhotoPath(const char* path);

	std::string GetFbID();
	void SetFbID(const char* profileID);

	std::string GetFbUserName();
	void SetFbUserName(const char* fbusernam);

	std::string GetFbFullName();
	void SetFbFullName(const char* fbusernam);

	//facebook

	std::string	GetName();
	void		SetName(const char* name);

	std::string	GetUsername();
	void		SetUsername(const char* username);

	std::string	GetPassword();
	void		SetPassword(const char* pass);

	//////////////////////////////////////////////////////////////////////////

	int		GetValueFromKey(const char* key);
	void	SetValueFromKey(const char* key, int val);

	tm*		GetTime(const char* key);
	void	SetTime(const char* key, tm* time);

	int		SoloGetLastQuestionIndex();
	void	SoloSetLastQuestionIndex(int boom);

// 	int		GetDiamond();
// 	void	SetDiamond(int diamon);
	
	MY_CREATE_FUNCTION(int, Diamond, "DIAMOND", 0);

	//////////////////////////////////////////////////////////////////////////

// 	int		GetSoloScore();
// 	void	SetSoloScore(int score);

	MY_CREATE_FUNCTION(int, SoloScore, "SOLO_SCORE", 0);

	~DataManager(void);
};

#endif
