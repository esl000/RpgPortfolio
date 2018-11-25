#include "stdafx.h"
#include "cQuestDatabase.h"
#include "cCustomFile.h"
#include "cCustomQuest.h"


cQuestDatabase::cQuestDatabase()
{
	this->Load();
	//int a = 0;
}


cQuestDatabase::~cQuestDatabase()
{
}

void cQuestDatabase::Load()
{
	std::set<string> setKeys;
	setKeys.insert(string("questkind"));

	setKeys.insert(string("name"));
	setKeys.insert(string("lore"));

	setKeys.insert(string("level"));
	setKeys.insert(string("prevquest"));

	setKeys.insert(string("target"));
	setKeys.insert(string("targetdeath"));
	setKeys.insert(string("takeitem"));
	setKeys.insert(string("takeitemamount"));

	setKeys.insert(string("exp"));
	setKeys.insert(string("money"));
	setKeys.insert(string("giveitem"));

	FILE* fp;
	fopen_s(&fp, "quest/questSize.txt", "r");
	if (!fp)
		return;

	int dwSize = 0;
	fscanf_s(fp, "%d", &dwSize);
	fclose(fp);

	if (dwSize <= 0)
		return;

	std::map<string, string> mapData;

	for (int i = 0; i < dwSize; ++i)
	{
		char szBuf[1024];
		string sPath("quest/_");
		sprintf(szBuf, "%d", i);
		sPath += string(szBuf) + string(".txt");
		if (cCustomFile::LoadCustomFile(sPath.c_str(), setKeys, mapData))
		{
			cCustomQuest* quest = new cCustomQuest;
			quest->m_sQuestKind = mapData[string("questkind")];

			quest->m_sName = mapData[string("name")];
			quest->m_sLore = mapData[string("lore")];

			quest->m_dwLevel = atoi(mapData[string("level")].c_str());
			quest->m_sPrevQuest = mapData[string("prevquest")];

			quest->m_sTarget = mapData[string("target")];
			quest->m_nTargetDeath = atoi(mapData[string("targetdeath")].c_str());
			quest->m_sTakeitem = mapData[string("takeitem")];
			quest->m_nTakeitemAmount = atoi(mapData[string("takeitemamount")].c_str());

			quest->m_nExp = atoi(mapData[string("exp")].c_str());
			quest->m_nMoney = atoi(mapData[string("money")].c_str());

			quest->m_sGiveitems = mapData[string("giveitems")];
			m_mapDatabase[quest->m_sName] = quest;
		}
		mapData.clear();
	}
}

cCustomQuest* cQuestDatabase::GetQuest(string sName)
{
	if (m_mapDatabase.find(sName) == m_mapDatabase.end())
		return NULL;
	else
		return m_mapDatabase[sName];
}

void cQuestDatabase::Destroy()
{
	for each(auto p in m_mapDatabase)
	{
		SAFE_DELETE(p.second);
	}
}
