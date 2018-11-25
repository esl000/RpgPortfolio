#pragma once

class cGroup;
class cMtlTex;

class cObjLoader
{
private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;

public:
	cObjLoader(void);
	~cObjLoader(void);

	void Load(IN char* szFullPath, OUT std::vector<cGroup*>& vecGroup);
	LPD3DXMESH Load(IN const char* szFolder, IN const char* szPath, OUT std::vector<cMtlTex*>& vecMtlTex, OUT ST_SPHERE& stBoundingSphere);
	LPD3DXMESH LoadObject(IN const char* szFolder, IN const char* szPath, OUT std::vector<cMtlTex*>& vecMtlTex, OUT std::vector<ST_BOUNDINGBOX>& vecBox, OUT ST_SPHERE& stBoundingSphere);
	LPD3DXMESH LoadSurface(IN const char* szFolder, IN const char* szPath, OUT std::vector<cMtlTex*>& vecMtlTex, OUT std::vector<ST_FACE>& vecFace);
	void LoadMtlLib(IN const char* szFolder, IN char* szPath);
};

