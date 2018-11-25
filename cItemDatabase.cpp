#include "stdafx.h"
#include "cItemDatabase.h"
#include "cCustomFile.h"
#include "cItem.h"


cItemDatabase::cItemDatabase()
{
	Load();
}


cItemDatabase::~cItemDatabase()
{
}

void cItemDatabase::Load()
{
	std::set<string> setKeys;
	setKeys.insert(string("name"));
	setKeys.insert(string("mesh_folder"));
	setKeys.insert(string("mesh_filename"));
	setKeys.insert(string("mesh_subfilename"));
	setKeys.insert(string("item_texture"));
	setKeys.insert(string("gold"));
	setKeys.insert(string("damage"));
	setKeys.insert(string("defense"));
	setKeys.insert(string("level"));
	setKeys.insert(string("item_type"));
	setKeys.insert(string("rotation"));

	FILE* fp;
	fopen_s(&fp, "item/itemSize.txt", "r");
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
		string sPath("item/_");
		sprintf(szBuf, "%d", i);
		sPath += string(szBuf) + string(".txt");
		if (cCustomFile::LoadCustomFile(sPath.c_str(), setKeys, mapData))
		{
			cItem* pItem = new cItem;
			pItem->m_sName = mapData[string("name")];

			pItem->m_sFolder = mapData[string("mesh_folder")];
			pItem->m_sFile = mapData[string("mesh_filename")];
			pItem->m_sSubFile = mapData[string("mesh_subfilename")];

			pItem->m_sImageName = mapData[string("item_texture")];
			pItem->m_fGold = atof(mapData[string("gold")].c_str());
			pItem->m_fDamage = atof(mapData[string("damage")].c_str());
			pItem->m_fDefence = atof(mapData[string("defense")].c_str());
			pItem->m_nLevel = atoi(mapData[string("level")].c_str());
			pItem->m_eItemType = (cItem::eItemType)atoi(mapData[string("item_type")].c_str());
			pItem->m_bIsRotation = atoi(mapData[string("rotation")].c_str());

			m_mapItem[pItem->m_sName] = pItem;
		}
		mapData.clear();
	}

}

cItem* cItemDatabase::GetItem(string sName)
{
	if (m_mapItem.find(sName) == m_mapItem.end())
		return NULL;
	else
	{
		cItem* pItem = new cItem;
		cItem* pOrgItem = m_mapItem[sName];
		
		pItem->m_sName = pOrgItem->m_sName;
		pItem->m_fGold = pOrgItem->m_fGold;
		pItem->m_fDamage = pOrgItem->m_fDamage;
		pItem->m_fDefence = pOrgItem->m_fDefence;
		pItem->m_nLevel = pOrgItem->m_nLevel;
		pItem->m_sFolder = pOrgItem->m_sFolder;
		pItem->m_sFile = pOrgItem->m_sFile;
		pItem->m_sSubFile = pOrgItem->m_sSubFile;

		pItem->m_sImageName = pOrgItem->m_sImageName;

		pItem->SetItemType(pOrgItem->m_eItemType);
		pItem->m_bIsRotation = pOrgItem->m_bIsRotation;

		return pItem;
	}
}

void cItemDatabase::Destroy()
{
	for each(auto p in m_mapItem)
	{
		SAFE_RELEASE(p.second);
	}
}
