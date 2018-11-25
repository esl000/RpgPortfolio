#pragma once

class cMtlTex;
class cOctree;

class cEntityBuilding : public cEntity
{
	friend class cBuildingDatabase;
protected:
	vector<cMtlTex*>	m_vecMtl;
	vector<cMtlTex*>	m_vecSurfaceMtl;
	vector<ST_BOUNDINGBOX> m_vecBoundingBox;
	LPD3DXMESH		m_pSurfaceMesh;
	vector<ST_FACE> m_vecSurface;
	SYNTHESIZE(cOctree*, m_pRootOctree, Octree);
	SYNTHESIZE(std::string, m_sName, Name);
public:
	cEntityBuilding();
	~cEntityBuilding();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

