#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
: _system(NULL),
_channel(NULL),
_sound(NULL)
{
}


soundManager::~soundManager()
{
}


HRESULT soundManager::init(void)
{
	//사운드 시스템 생성
	System_Create(&_system);

	//채널수 설정
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//사운드, 채널 동적할당(꼭)
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	//메모리를 한번 밀어주자
	memset(_sound, 0, sizeof(Sound*)* (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*)* (TOTALSOUNDBUFFER));

	_number = 0;

	return S_OK;
}
void soundManager::release(void)
{
	//사운드 삭제
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	//메모리 지워준다
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//시스템 날려줌
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}


	_mTotalSounds.clear();
	_mNumber.clear();

}
void soundManager::update(void)
{
	_system->update();
}
void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	//루프할꺼니?
	if (loop)
	{
		//BGM인지 아님 effect인지
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	//맵에 사운드를 키값과 함께 넣어주자
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
	_mNumber.insert(make_pair(keyName, _number));
	_number++;
}

void soundManager::play(string keyName, float volume) // 0.0 ~ 1.0
{
	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이
			_system->playSound(FMOD_CHANNEL_FREE, _sound[iterN->second], false, &_channel[iterN->second]);

			//볼륨 설정
			_channel[iterN->second]->setVolume(volume);
			break;
		}
	}

}
void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//볼륨 설정
			_channel[iterN->second]->stop();
			break;
		}
	}
}
void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//볼륨 설정
			_channel[iterN->second]->setPaused(true);
			break;
		}
	}
}
void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//볼륨 설정
			_channel[iterN->second]->setPaused(false);
			break;
		}
	}
}

//재생중인지?
bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//볼륨 설정
			_channel[iterN->second]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

//정지했는지?
bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//볼륨 설정
			_channel[iterN->second]->isPlaying(&isPause);
			break;
		}
	}

	return isPause;
}

int soundManager::getSoundLength(string keyName)
{
	unsigned int soundRange = 0;

	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//볼륨 설정
			_sound[iterN->second]->getLength(&soundRange, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return soundRange;
}

/////////////////////////////////////////////////
//볼륨조절 추가
void soundManager::setVolume(string keyName, float volume) // 0.0 ~ 1.0
{
	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//볼륨 설정
			_channel[iterN->second]->setVolume(volume);
			break;
		}
	}
}