
#ifndef __DATA_MANAGER__
#define __DATA_MANAGER__

#include "cocos2d.h"
#include <time.h>
USING_NS_CC;


class DataManager
{
private:
	DataManager();
	static DataManager *s_instance;

public:
	static DataManager* sharedDataManager();

	std::string GetPhotoPath();
	void SetPhotoPath(const char* path);

	std::string GetFbID();
	void SetProfileID(const char* profileID);

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

	int		GetHighScore();
	void	SetHighScore(int score);

	int		GetValueFromKey(const char* key);
	void	SetValueFromKey(const char* key, int val);

	tm*		GetTime(const char* key);
	void	SetTime(const char* key, tm* time);

	int		GetLastQuestion();
	void	SetLastQuestion(int boom);

	int		GetDiamon();
	void	SetDiamon(int diamon);
	
	
	~DataManager(void);
};

#endif
