#include "stdafx.h"
#include "cBuildingDatabase.h"
#include "cCustomFile.h"
#include "cEntityBuilding.h"
#include "cObjLoader.h"
#include "cMtlTex.h"


cBuildingDatabase::cBuildingDatabase()
{
	Load();
}


cBuildingDatabase::~cBuildingDatabase()
{
}

void cBuildingDatabase::Load()
{
	std::set<string> setKeys;
	setKeys.insert(string("name"));
	setKeys.insert(string("mesh_folder"));
	setKeys.insert(string("mesh_file"));
	setKeys.insert(string("mesh_surface"));

	FILE* fp;
	fopen_s(&fp, "building/buildingSize.txt", "r");
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
		string sPath("building/_");
		sprintf(szBuf, "%d", i);
		sPath += string(szBuf) + string(".txt");
		if (cCustomFile::LoadCustomFile(sPath.c_str(), setKeys, mapData))
		{
			cEntityBuilding* building = new cEntityBuilding;
			building->m_sName = mapData[string("name")];
			
			building->m_pObjMesh = g_pObjManager->GetObjBoundingBox(building->m_vecBoundingBox, building->m_vecMtl, building->m_stFrustumSphere, mapData[string("mesh_folder")].c_str(), mapData[string("mesh_file")].c_str());
			D3DXVECTOR3* pV;

			building->m_pSurfaceMesh = g_pObjManager->GetObjSurface(building->m_vecSurfaceMtl, building->m_vecSurface, mapData[string("mesh_folder")].c_str(), mapData[string("mesh_surface")].c_str());
			
			m_mapDatabase[building->m_sName] = building;
			m_vecDatabase.push_back(building);
		}
		mapData.clear();
	}
}

cEntityBuilding* cBuildingDatabase::GetBuilding(string sName)
{
	if (m_mapDatabase.find(sName) == m_mapDatabase.end())
		return NULL;
	else
	{
		cEntityBuilding* building = new cEntityBuilding;
		building->SetEntityType(cEntity::E_BUILDING);
		m_mapDatabase[sName]->m_pObjMesh->AddRef();
		building->m_sName = m_mapDatabase[sName]->m_sName;
		building->m_vecMtl = m_mapDatabase[sName]->m_vecMtl;
		building->m_stFrustumSphere = m_mapDatabase[sName]->m_stFrustumSphere;
		building->m_pObjMesh = m_mapDatabase[sName]->m_pObjMesh;
		building->m_vecBoundingBox = m_mapDatabase[sName]->m_vecBoundingBox;
		
		building->m_vecSurface = m_mapDatabase[sName]->m_vecSurface;

		building->m_pSurfaceMesh = m_mapDatabase[sName]->m_pSurfaceMesh;
		building->m_vecSurfaceMtl = m_mapDatabase[sName]->m_vecSurfaceMtl;

		
		return building;
	}
}

cEntityBuilding* cBuildingDatabase::GetBuilding(int& nIndex)
{
	nIndex %= m_vecDatabase.size();
	cEntityBuilding* building = new cEntityBuilding;
	building->SetEntityType(cEntity::E_BUILDING);
	m_vecDatabase[nIndex]->m_pObjMesh->AddRef();
	building->m_sName = m_vecDatabase[nIndex]->m_sName;
	building->m_vecMtl = m_vecDatabase[nIndex]->m_vecMtl;
	building->m_stFrustumSphere = m_vecDatabase[nIndex]->m_stFrustumSphere;
	building->m_pObjMesh = m_vecDatabase[nIndex]->m_pObjMesh;
	building->m_vecBoundingBox = m_vecDatabase[nIndex]->m_vecBoundingBox;
	
	building->m_vecSurface = m_vecDatabase[nIndex]->m_vecSurface;

	building->m_pSurfaceMesh = m_vecDatabase[nIndex]->m_pSurfaceMesh;
	building->m_vecSurfaceMtl = m_vecDatabase[nIndex]->m_vecSurfaceMtl;
	
	return building;
}

void cBuildingDatabase::Destroy()
{
	for each(auto p in m_mapDatabase)
	{
		//for each(auto mtl in p.second->m_vecMtl)
		//{
		//	SAFE_RELEASE(mtl);
		//}
		SAFE_RELEASE(p.second);
	}
}
