#pragma once

#include "cMtlTex.h"

class cGroup : public cObject
{
private:
	int						m_nNumTri;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);
	
public:
	cGroup(void);
	~cGroup(void);

	void Render();
	void BuildVB(std::vector<ST_PNT_VERTEX>& vecVertex);
};

