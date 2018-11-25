#include "stdafx.h"
#include "cSceneManager.h"
#include "iScene.h"


cSceneManager::cSceneManager()
	: m_pCurrentScene(NULL)
{
}


cSceneManager::~cSceneManager()
{
}

bool cSceneManager::AddScene(string sKey, iScene* pScene)
{
	if (m_mapScene.find(sKey) != m_mapScene.end())
		return false;
	m_mapScene[sKey] = pScene;
}

bool cSceneManager::ChangeScene(string sKey)
{
	if (m_mapScene.find(sKey) == m_mapScene.end())
		return false;
	iScene* scene = m_pCurrentScene;
	m_pCurrentScene = m_mapScene[sKey];
	//증가된 RefCOunt 내려줌
	SAFE_RELEASE(scene);
	m_mapScene.erase(sKey);
	return true;
}

iScene* cSceneManager::GetScene(string sKey)
{
	if (m_mapScene.find(sKey) == m_mapScene.end())
		return NULL;
	return m_mapScene[sKey];
}

iScene* cSceneManager::GetCurrentScene()
{
	return m_pCurrentScene;
}

void cSceneManager::Destroy()
{
	SAFE_RELEASE(m_pCurrentScene);
	for each(auto p in m_mapScene)
	{
		SAFE_RELEASE(p.second);
	}

	m_mapScene.clear();
}
