#pragma once

#include "iMap.h"
#include "cChunk.h"

#define g_pMap cMap::GetInstance()

class cMap : public iMap
{
private:
	vector<D3DXVECTOR3>	m_vecPosition;
	LPD3DXMESH			m_pMesh;
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9			m_stMtl;
	SYNTHESIZE(string, m_sFolder, Folder);
	SYNTHESIZE(string, m_sFileName, FileName);
	SYNTHESIZE(string, m_sTextureName, TextureName);
	SYNTHESIZE_ONLY_GETTER(DWORD, m_dTile, Tile);
	static void Load(LPVOID pThis);
public:
	cMap();
	virtual ~cMap();

	static cMap* GetInstance();

	void Setup();
	void Update();
	virtual void Render();
	virtual bool GetHeight(IN float x, IN float z, OUT float& y);

	void Destroy();
};

