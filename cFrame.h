#pragma once

#include "cMtlTex.h"

class cFrame : public cObject
{
	friend class cAseLoad;

private:
	std::vector<cFrame*>		m_vecChild;
	D3DXMATRIXA16				m_matLocal;
	std::vector<ST_POS_SAMPLE>	m_vecPosTrack;
	std::vector<ST_ROT_SAMPLE>	m_vecRotTrack;
	LPD3DXMESH					m_pMesh;

	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, WorldMatrix);
	SYNTHESIZE(std::string, m_sNodeName, NodeName);
	SYNTHESIZE(std::string, m_sNodeParent, NodeParent);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);

public:
	cFrame(void);
	~cFrame(void);

	void Render();
	void Update(D3DXMATRIXA16* pmatParent, int nTick);
	void BuildMesh(std::vector<ST_PNT_VERTEX>& vecVertex);
	cFrame* FindNode(std::string sNodeName);
	void AddChild(cFrame* pChild);
	void Destroy();
	void CalcOriginLocalTM(D3DXMATRIXA16* pmatParent);
	void CalcLocalMatrixT(OUT D3DXMATRIXA16& matT, IN int nTick);
	void CalcLocalMatrixR(OUT D3DXMATRIXA16& matR, IN int nTick);
};

