#include "stdafx.h"
#include "cNpcDataBase.h"
#include "cUnitCustomNpc.h"
#include "cCustomFile.h"


cNpcDataBase::cNpcDataBase()
{
	Load();
}


cNpcDataBase::~cNpcDataBase()
{
}

void cNpcDataBase::Load()
{
	std::set<string> setKeys;
	setKeys.insert(string("name"));
	setKeys.insert(string("lore"));
	setKeys.insert(string("mesh_folder"));
	setKeys.insert(string("mesh_filename"));
	setKeys.insert(string("level"));
	setKeys.insert(string("quest"));
	setKeys.insert(string("moveNpc"));

	FILE* fp;
	fopen_s(&fp, "npc/npcSize.txt", "r");
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
		string sPath("npc/_");
		sprintf(szBuf, "%d", i);
		sPath += string(szBuf) + string(".txt");
		if (cCustomFile::LoadCustomFile(sPath.c_str(), setKeys, mapData))
		{
			cUnitCustomNpc* pNpc = new cUnitCustomNpc;
			pNpc->SetName(mapData[string("name")]);
			pNpc->SetLore(mapData[string("lore")]);
			pNpc->SetLevel(atoi(mapData[string("level")].c_str()));
			pNpc->SetQuest(mapData[string("quest")]); 
			pNpc->SetFolder(mapData[string("mesh_folder")]);
			pNpc->SetFile(mapData[string("mesh_filename")]);
			pNpc->SetMoveNpc(mapData[string("moveNpc")]);
			m_mapDatabase[pNpc->GetName()] = pNpc;
			m_vecDatabase.push_back(pNpc);
			//1인당 1개만 들고있어요 걍
		}
		mapData.clear();
	}
}

void cNpcDataBase::Destroy()
{
	for each(auto p in m_mapDatabase)
	{
		SAFE_RELEASE(p.second);
	}
}

cUnitCustomNpc* cNpcDataBase::GetCustomNpc(std::string sName)
{
	if (m_mapDatabase.find(sName) == m_mapDatabase.end())
		return NULL;
	else
	{
		cUnitCustomNpc* pNpc = new cUnitCustomNpc;
		pNpc->SetEntityType(cEntity::E_UNIT);
		pNpc->SetName(m_mapDatabase[sName]->GetName());
		pNpc->SetLore(m_mapDatabase[sName]->GetLore());
		pNpc->SetLevel(m_mapDatabase[sName]->GetLevel());
		pNpc->SetQuest(m_mapDatabase[sName]->GetQuest());
		pNpc->SetFolder(m_mapDatabase[sName]->GetFolder());
		pNpc->SetFile(m_mapDatabase[sName]->GetFile());
		return pNpc;
	}
}

cUnitCustomNpc* cNpcDataBase::GetCustomNpc(int& nIndex)
{
	nIndex %= m_vecDatabase.size();

	cUnitCustomNpc* pNpc = new cUnitCustomNpc;
	pNpc->SetEntityType(cEntity::E_UNIT);
	pNpc->SetName(m_vecDatabase[nIndex]->GetName());
	pNpc->SetLore(m_vecDatabase[nIndex]->GetLore());
	pNpc->SetLevel(m_vecDatabase[nIndex]->GetLevel());
	pNpc->SetQuest(m_vecDatabase[nIndex]->GetQuest());
	pNpc->SetFolder(m_vecDatabase[nIndex]->GetFolder());
	pNpc->SetFile(m_vecDatabase[nIndex]->GetFile());
	return pNpc;
}
