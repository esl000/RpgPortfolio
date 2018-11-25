#pragma once

#include <string>
#include <map>

//fmod.hpp �߰�
#include "inc/fmod.hpp"

//lib��ũ
#pragma comment (lib, "lib/fmodex_vc.lib")

#define g_pSoundManager soundManager::GetInstance()

//ä�� ����, ���� ����
#define EXTRACHANNELBUFFER 40
#define SOUNDBUFFER 40

//�� ���� ���� : ���۰� �۾Ƽ� ������ ������ �ذ�
//������ ���� ä���� �����Ͽ� �ش�.

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

	//���������?
	bool isPlaySound(string keyName);

	//�����ߴ���?
	bool isPauseSound(string keyName);

	//���� ����
	int getSoundLength(string keyName);

	//�������� �߰���
	void setVolume(string keyName, float volume);

};

