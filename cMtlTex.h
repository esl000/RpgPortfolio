#pragma once

class cMtlTex : public cObject
{

private:

public:
	cMtlTex(void);
	~cMtlTex(void);

	int					m_nAttrId;
	D3DMATERIAL9			m_stMtl;
	LPDIRECT3DTEXTURE9	m_pTexture;
};

