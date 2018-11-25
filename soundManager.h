#pragma once

#include <string>
#include <map>

//fmod.hpp 추가
#include "inc/fmod.hpp"

//lib링크
#pragma comment (lib, "lib/fmodex_vc.lib")

#define g_pSoundManager soundManager::GetInstance()

//채널 버퍼, 사운드 버퍼
#define EXTRACHANNELBUFFER 40
#define SOUNDBUFFER 40

//총 사운드 버퍼 : 버퍼가 작아서 씹히는 문제를 해결
//여분의 사운드 채널을 생성하여 준다.

#define TOTALSOUNDBUFFER EXTRACHANNELBUFFER + SOUNDBUFFER

using namespace FMOD;

class soundManager
{
public:
	SINGLETONE(soundManager);
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;
	typedef map<string, int> arrNumber;
	typedef map<string, int>::iterator arrNumberIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

	int _number;
	arrNumber _mNumber;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool bgm, bool loop);
	void play(string keyName, float volume); // 0.0 ~ 1.0
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	//재생중인지?
	bool isPlaySound(string keyName);

	//정지했는지?
	bool isPauseSound(string keyName);

	//사운드 길이
	int getSoundLength(string keyName);

	//볼륨조절 추가함
	void setVolume(string keyName, float volume);

};

