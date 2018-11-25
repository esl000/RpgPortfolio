#pragma once

#include "iMap.h"

class cHeightMap : public iMap
{
	friend class cTileManager;
private:
	D3DMATERIAL9					m_stMtl;
	LPDIRECT3DTEXTURE9			m_pTexture;
	std::string					m_sTexure;
	int							m_nTile;
	std::vector<D3DXVECTOR3>		m_vecVertex;
	LPDIRECT3DTEXTURE9			m_pTextureBlending;
	LPDIRECT3DTEXTURE9			m_pDiffuseTexture[3];
	LPDIRECT3DTEXTURE9			m_pSpecularTexture[3];
	SYNTHESIZE(LPD3DXEFFECT, m_pEffect, Shader);
	SYNTHESIZE_PASS_BY_REF(ST_CHUNK_INDEX, m_stIndex, Index);
	SYNTHESIZE(ST_SPHERE, m_stFrustumSphere, FrustumSphere);
	SYNTHESIZE(ST_CHUNK, m_vChunk, Chunk);
	SYNTHESIZE_ONLY_GETTER(LPD3DXMESH, m_pMesh, Mesh);
public:
	cHeightMap(void);
	~cHeightMap(void);

	void Load(char* szFolder, char* szRawFile, char* szTexture, int nBytePerColor = 1);

public:
	virtual void Render() override;
	virtual bool GetHeight(IN float x, IN float z, OUT float& y) override;

	void ConnectVertex();
};

