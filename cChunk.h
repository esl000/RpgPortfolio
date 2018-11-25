#pragma once
class cChunk : public cGameObject
{
private:
	LPD3DXMESH m_pMesh;
	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	SYNTHESIZE(ST_CHUNK, m_stChunk, Chunk);
public:
	cChunk();
	~cChunk();
	virtual void Setup(vector<ST_PNT_VERTEX>& vecVertex, DWORD dwSize);
	virtual void Render();
};

