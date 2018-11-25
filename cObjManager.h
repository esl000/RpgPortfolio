#pragma once

class cObjLoader;
class cMtlTex;

#define g_pObjManager cObjManager::GetInstance()

class cObjManager
{
private:
	map<string, LPD3DXMESH> m_mapMesh;
	map<string, vector<cMtlTex*>> m_mapMtl;
	map<string, ST_SPHERE> m_mapSphere;
	map<string, vector<ST_BOUNDINGBOX>> m_mapBoundingBox;
	map<string, vector<ST_FACE>> m_mapSurface;

public:
	SINGLETONE(cObjManager);

	void Destroy();

	LPD3DXMESH GetObj(OUT vector<cMtlTex*>& vecMtl, OUT ST_SPHERE& stBoundingSphere, IN const char* szFolder, IN const char* szPath);
	LPD3DXMESH GetObjBoundingBox(OUT vector<ST_BOUNDINGBOX>& vecBox, OUT vector<cMtlTex*>& vecMtl, OUT ST_SPHERE& stBoundingSphere, IN const char* szFolder, IN const char* szPath);
	LPD3DXMESH GetObjSurface(OUT vector<cMtlTex*>& vecMtl, OUT vector<ST_FACE>& vecFace, IN const char* szFolder, IN const char* szPath);
};

