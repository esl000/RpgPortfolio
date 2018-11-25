#include "stdafx.h"
#include "cMessageManager.h"


cMessageManager::cMessageManager()
	: m_fDeleteTime(3)
	, m_fNoMessageTime(0)
{
}


cMessageManager::~cMessageManager()
{
}

void cMessageManager::Setup()
{

}

void cMessageManager::Update()
{
	m_fNoMessageTime += g_pTimeManager->GetElapsedTime();

	if (m_fDeleteTime <= m_fNoMessageTime)
	{
		m_fNoMessageTime = 0;
		m_vecMessage.clear();
	}
}

void cMessageManager::PushMessage(ST_MESSAGE stMessage)
{
	m_vecMessage.push_back(stMessage);
	m_fNoMessageTime = 0;
}


DWORD cMessageManager::FindMessage(DWORD eMType, string sData)
{ 
	DWORD dwCount = 0;
	for (size_t i = 0; i < m_vecMessage.size();)
	{
		if (m_vecMessage[i].dwFlag == eMType &&
			m_vecMessage[i].sData == sData)
		{
			++dwCount;
			m_vecMessage.erase(m_vecMessage.begin() + i);
		}
		else
		{
			++i;
		}
	}
	return dwCount;
}
