#pragma once

#define g_pMessageManager cMessageManager::GetInstance()


class cMessageManager
{
public:
	enum eMessageType
	{
		E_MONSTERDIE = 0
	};


private:
	float m_fNoMessageTime;
	float m_fDeleteTime;
	vector<ST_MESSAGE> m_vecMessage;
public:
	SINGLETONE(cMessageManager);

	void Setup();
	void Update();
	void PushMessage(ST_MESSAGE stMessage);
	DWORD FindMessage(DWORD eMType, string sData);
};

