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
	//���� �ý��� ����
	System_Create(&_system);

	//ä�μ� ����
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//����, ä�� �����Ҵ�(��)
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	//�޸𸮸� �ѹ� �о�����
	memset(_sound, 0, sizeof(Sound*)* (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*)* (TOTALSOUNDBUFFER));

	_number = 0;

	return S_OK;
}
void soundManager::release(void)
{
	//���� ����
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

	//�޸� �����ش�
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//�ý��� ������
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
	//�����Ҳ���?
	if (loop)
	{
		//BGM���� �ƴ� effect����
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

	//�ʿ� ���带 Ű���� �Բ� �־�����
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
			//���� �÷���
			_system->playSound(FMOD_CHANNEL_FREE, _sound[iterN->second], false, &_channel[iterN->second]);

			//���� ����
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
			//���� ����
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
			//���� ����
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
			//���� ����
			_channel[iterN->second]->setPaused(false);
			break;
		}
	}
}

//���������?
bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[iterN->second]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

//�����ߴ���?
bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//���� ����
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
			//���� ����
			_sound[iterN->second]->getLength(&soundRange, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return soundRange;
}

/////////////////////////////////////////////////
//�������� �߰�
void soundManager::setVolume(string keyName, float volume) // 0.0 ~ 1.0
{
	arrSoundsIter iter = _mTotalSounds.begin();
	arrNumberIter iterN = _mNumber.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, ++iterN)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[iterN->second]->setVolume(volume);
			break;
		}
	}
}