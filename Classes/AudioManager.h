/*
 * AudioManager.h
 *
 *  Created on: 20 Oct 2012
 *      Author: Loc
 */

#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "MyMacro.h"


#define		PLAY_BUTTON_EFFECT				AudioManager::sharedAudioManager()->PlayEffect("button.wav")
#define		PLAY_BACKGROUND_MUSIC			AudioManager::sharedAudioManager()->PlayBackground("game_music.ogg")
#define		STOP_BACKGROUND_MUSIC			AudioManager::sharedAudioManager()->StopBackground()

#define		PLAY_GET_BOMB_EFFECT			AudioManager::sharedAudioManager()->PlayEffect("get_bomb.wav")
#define		PLAY_GET_DOUBLE_LAZER_EFFECT	AudioManager::sharedAudioManager()->PlayEffect("get_double_laser.wav")
#define		PLAY_OUT_PORP_EFFECT			AudioManager::sharedAudioManager()->PlayEffect("out_porp.wav")
#define		PLAY_RING_EFFECT			AudioManager::sharedAudioManager()->PlayEffect("ring.wav")

class AudioManager
{
public:
	static AudioManager* sharedAudioManager();
	bool IsEnableBackground();
	bool IsEnableEffect();
	bool IsPlayingBackground();
	void SetEnableBackground(bool b);
	void SetEnableEffect(bool b);

	float GetVolumeMusic();
	void SetVolumeMusic(float _value);
	float GetVolumeFX();
	void SetVolumeFX(float _value);

	void LoadBackground(const char* path);
	void PlayBackground(const char* path, bool isPlayAgain = false, bool loop = true);
	void PauseBackground();
	void StopBackground();
	void PlayEffect(const char* path,  bool isLoop = false);
	void StopLoopEffect(const char* path);

private:
	AudioManager();
	~AudioManager() {
		MY_RELEASE(m_loopEffects);
	}

	bool m_isPlayingBackground;
	bool m_bEnableBackground;
	bool m_bEnableEffect;

	CCDictionary* m_loopEffects;
};

#endif /* AUDIOMANAGER_H_ */
