#pragma once

#include "cMtlTex.h"

class cEntityObject : public cEntity
{
	friend class cObjectDatabase;
protected:
	vector<cMtlTex*>	m_vecMtl;
	vector<D3DXVECTOR3> vecOrgBB;
	SYNTHESIZE_ONLY_GETTER(bool, m_bCollision, Collision);
	SYNTHESIZE_ONLY_GETTER(bool, m_isBBox, BBox);
	SYNTHESIZE_ONLY_GETTER(vector<D3DXVECTOR3>, m_vecBoudingBox, vecBB);
	SYNTHESIZE_ONLY_GETTER(D3DXVECTOR3, m_vBoundingBoxCenter, BBCenter);
	SYNTHESIZE_ONLY_GETTER(D3DXMATRIXA16, m_matBBWorld, BBWorld);
	SYNTHESIZE_ONLY_GETTER(LPD3DXMESH, m_pBoundingBox, BoundingBox);
	SYNTHESIZE(std::string, m_sName, Name);
public:
	cEntityObject();
	~cEntityObject();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

