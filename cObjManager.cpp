#include "stdafx.h"
#include "cObjManager.h"
#include "cObjLoader.h"
#include "cMtlTex.h"


cObjManager::cObjManager()
{
}


cObjManager::~cObjManager()
{
}

void cObjManager::Destroy()
{
	for each (auto p in m_mapMesh)
	{
		SAFE_RELEASE(p.second);
	}

	for each (auto p in m_mapMtl)
	{
		for each (auto ps in p.second)
		{
			SAFE_RELEASE(ps);
		}
	}

	int a = 0;
}

LPD3DXMESH cObjManager::GetObj(OUT vector<cMtlTex*>& vecMtl, OUT ST_SPHERE& stBoundingSphere, IN const char* szFolder, IN const char* szPath)
{
	string sFullPath = string(szFolder) + string("/") + string(szPath);
	if (m_mapMesh.find(sFullPath) == m_mapMesh.end())
	{
		cObjLoader* pObj = new cObjLoader;
		m_mapMesh[sFullPath] = pObj->Load(szFolder, szPath, m_mapMtl[string(sFullPath)], m_mapSphere[string(sFullPath)]);
		SAFE_DELETE(pObj);
	}


	m_mapMesh[sFullPath]->AddRef();
	vecMtl = m_mapMtl[sFullPath];
	stBoundingSphere = m_mapSphere[string(sFullPath)];
	return m_mapMesh[sFullPath];
}

LPD3DXMESH cObjManager::GetObjBoundingBox(OUT vector<ST_BOUNDINGBOX>& vecBox, OUT vector<cMtlTex*>& vecMtl, OUT ST_SPHERE& stBoundingSphere, IN const char* szFolder, IN const char* szPath)
{
	string sFullPath = string(szFolder) + string("/") + string(szPath);
	if (m_mapMesh.find(sFullPath) == m_mapMesh.end())
	{
		cObjLoader* pObj = new cObjLoader;
		m_mapMesh[sFullPath] = pObj->LoadObject(szFolder, szPath, m_mapMtl[string(sFullPath)], m_mapBoundingBox[sFullPath], m_mapSphere[string(sFullPath)]);
		SAFE_DELETE(pObj);
	}


	m_mapMesh[sFullPath]->AddRef();
	vecMtl = m_mapMtl[sFullPath];
	stBoundingSphere = m_mapSphere[string(sFullPath)];
	vecBox = m_mapBoundingBox[sFullPath];
	return m_mapMesh[sFullPath];
}

LPD3DXMESH cObjManager::GetObjSurface(OUT vector<cMtlTex*>& vecMtl, OUT vector<ST_FACE>& vecFace, IN const char* szFolder, IN const char* szPath)
{
	string sFullPath = string(szFolder) + string("/") + string(szPath);
	if (m_mapSurface.find(sFullPath) == m_mapSurface.end())
	{
		cObjLoader* pObj = new cObjLoader;
		m_mapMesh[sFullPath] = pObj->LoadSurface(szFolder, szPath, m_mapMtl[sFullPath], m_mapSurface[sFullPath]);
		SAFE_DELETE(pObj);
	}

	vecMtl = m_mapMtl[sFullPath];
	vecFace = m_mapSurface[sFullPath];
	return m_mapMesh[sFullPath];
}
