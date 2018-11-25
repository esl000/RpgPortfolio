#pragma once

class cCustomQuest;

#define g_pQuestDatabase cQuestDatabase::GetInstance()

class cQuestDatabase
{
private:
	std::map<string, cCustomQuest*> m_mapDatabase;
	void Load();
public:
	SINGLETONE(cQuestDatabase);
	
	cCustomQuest* GetQuest(string sName);
	void Destroy();
};

