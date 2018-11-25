#pragma once

#define OCTREEMINIMUMRADIUS 10

class cOctree
{
public:
	enum eDirection
	{
		E_ROOT = 1 << 0,
		E_UP = 1 << 1, // Y +
		E_DOWN = 1 << 2, // Y -
		E_RIGHT = 1 << 3, // X +	
		E_LEFT = 1 << 4, // X - 
		E_TOP = 1 << 5, //Z +
		E_BOTTOM = 1 << 6 // Z-
	};
private:
	vector<DWORD>			m_vecDir;
	void CheckPos(ST_FACE& stFace, D3DXVECTOR3& vCenter, map<DWORD, vector<ST_FACE>>& mapDir);
	LPD3DXMESH			m_pSphere;
	DWORD				m_dwDirection;
	D3DXVECTOR3			m_vCenter;
	float				m_fRadius;
	map<DWORD, cOctree*>	m_mapChild;
	cOctree*				m_pRoot;
	vector<ST_FACE>		m_vecNode;
	SYNTHESIZE(cOctree*, m_pMainRoot, MainRoot);
	SYNTHESIZE_ONLY_GETTER(ST_SPHERE, m_stSphere, Sphere);
public:
	cOctree();
	~cOctree();

	void SetOctree(DWORD dwDirection, D3DXVECTOR3 vCenter, float fRadius, vector<ST_FACE>& vecFace);
	vector<ST_FACE> GetNode();

	bool isPicked(cRay r, D3DXVECTOR3& vDest);
	void GetNearOctree(IN ST_SPHERE stSphere, OUT set<cOctree*>& setOctree);
	bool OnlyPicking(cRay r, D3DXVECTOR3& vDest);
	void Render();
	bool RootPicked(cRay r, D3DXVECTOR3& vDest);
	virtual void SphereRender(ST_SPHERE stSphere);
};

