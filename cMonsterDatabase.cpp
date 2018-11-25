#include "stdafx.h"
#include "cMonsterDatabase.h"
#include "cCustomFile.h"
#include "cUnitMonster.h"
#include "cUIImageView.h"

cMonsterDatabase::cMonsterDatabase()
{
	Load();
}


cMonsterDatabase::~cMonsterDatabase()
{
}

void cMonsterDatabase::Load()
{
	std::set<string> setKeys;
	setKeys.insert(string("name"));
	setKeys.insert(string("mesh_folder"));
	setKeys.insert(string("mesh_filename"));
	setKeys.insert(string("monster_Texture"));

	setKeys.insert(string("damage"));
	setKeys.insert(string("defence"));
	setKeys.insert(string("level"));
	setKeys.insert(string("hp"));

	setKeys.insert(string("exp"));
	setKeys.insert(string("money"));
	setKeys.insert(string("giveitem"));

	FILE* fp;
	fopen_s(&fp, "monster/monsterSize.txt", "r");
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
		string sPath("monster/_");
		sprintf(szBuf, "%d", i);
		sPath += string(szBuf) + string(".txt");
		if (cCustomFile::LoadCustomFile(sPath.c_str(), setKeys, mapData))
		{
			cUnitMonster* monster = new cUnitMonster;
			monster->m_sName = mapData[string("name")];
			monster->m_sFolder = mapData[string("mesh_folder")];
			monster->m_sFile = mapData[string("mesh_filename")];
			
			monster->m_sMonsterName = mapData[string("monster_Texture")];

			cSkinnedMesh* pMesh = new cSkinnedMesh(monster->m_sFolder.c_str(), monster->m_sFile.c_str());
			SAFE_DELETE(pMesh);

			monster->m_dwLevel = atoi(mapData[string("level")].c_str());
			monster->m_fMaxHp = atoi(mapData[string("hp")].c_str());
			monster->m_fCurrentHp = monster->m_fMaxHp;

			monster->m_nExp = atoi(mapData[string("exp")].c_str());
			monster->m_nMoney = atoi(mapData[string("money")].c_str());
			monster->m_fOrigDamage = atoi(mapData[string("damage")].c_str());
			monster->m_fOrigDefence = atoi(mapData[string("defence")].c_str());

			char szBuf[1024];
			strcpy(szBuf, mapData[string("giveitem")].c_str());

			char* szToken = NULL;
			char* szContext = NULL;
			szToken = strtok_s(szBuf, ",\n", &szContext);
			while (true)
			{
				if (!szToken)
					break;
				monster->m_vecItems.push_back(string(szToken));
				szToken = strtok_s(szContext, ",\n", &szContext);
			}

			m_mapMonster[monster->m_sName] = monster;
			m_vecMonster.push_back(monster);
		}
		mapData.clear();
	}
}

void cMonsterDatabase::Destroy()
{
	for each(auto p in m_mapMonster)
	{
		SAFE_RELEASE(p.second);
	}
}

cUnitMonster* cMonsterDatabase::GetMonster(std::string sName)
{
	if (m_mapMonster.find(sName) == m_mapMonster.end())
		return NULL;
	else
	{
		cUnitMonster* monster = new cUnitMonster;
		cUnitMonster* pOrg = m_mapMonster[sName];
		monster->SetEntityType(cEntity::E_UNIT);
		
		monster->m_sMonsterName = pOrg->m_sMonsterName;
		
		monster->m_sName = pOrg->m_sName;
		monster->m_sFolder = pOrg->m_sFolder;
		monster->m_sFile = pOrg->m_sFile;
		monster->m_dwLevel = pOrg->m_dwLevel;
		monster->m_fMaxHp = pOrg->m_fMaxHp;
		monster->m_fCurrentHp = pOrg->m_fCurrentHp;
		monster->m_nExp = pOrg->m_nExp;
		monster->m_nMoney = pOrg->m_nMoney;
		monster->m_vecItems = pOrg->m_vecItems;
		monster->m_fOrigDamage = pOrg->m_fOrigDamage;
		monster->m_fOrigDefence = pOrg->m_fOrigDefence;

		return monster;
	}
}

cUnitMonster* cMonsterDatabase::GetMonster(int& nIndex)
{
	nIndex %= m_vecMonster.size();
	cUnitMonster* monster = new cUnitMonster;
	cUnitMonster* pOrg = m_vecMonster[nIndex];
	
	monster->m_sMonsterName = pOrg->m_sMonsterName;
	
	monster->m_sName = pOrg->m_sName;
	monster->m_sFolder = pOrg->m_sFolder;
	monster->m_sFile = pOrg->m_sFile;
	monster->m_dwLevel = pOrg->m_dwLevel;
	monster->m_fMaxHp = pOrg->m_fMaxHp;
	monster->m_fCurrentHp = pOrg->m_fCurrentHp;
	monster->m_nExp = pOrg->m_nExp;
	monster->m_nMoney = pOrg->m_nMoney;
	monster->m_vecItems = pOrg->m_vecItems;
	monster->m_fOrigDamage = pOrg->m_fOrigDamage;
	monster->m_fOrigDefence = pOrg->m_fOrigDefence;

	return monster;
}
