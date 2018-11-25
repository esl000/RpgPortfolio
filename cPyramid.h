#pragma once
class cPyramid
{
private:
	IDirect3DVertexBuffer9*	m_pVertexBuffer;
	D3DXMATRIXA16				m_matWorld;
	D3DMATERIAL9*				m_mMatial;
	std::vector<ST_PN_VERTEX>	m_vecVertex;

public:
	cPyramid(void);
	~cPyramid(void);

	void Setup(D3DCOLOR c, D3DXMATRIXA16& mat);
	void Render();
	void SetMaterial(D3DMATERIAL9* mat) { m_mMatial = mat; }
};

