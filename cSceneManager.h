#pragma once

class iScene;

#define g_pSceneManager cSceneManager::GetInstance()

class cSceneManager
{
private:
	std::map<string, iScene*> m_mapScene;
	iScene* m_pCurrentScene;

public:
	SINGLETONE(cSceneManager);
	
	bool AddScene(string sKey, iScene* pScene);
	bool ChangeScene(string sKey);

	iScene* GetScene(string sKey);
	iScene* GetCurrentScene();

	void Destroy();
};

