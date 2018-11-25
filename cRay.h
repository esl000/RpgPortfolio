#pragma once
class cRay
{
private:
	SYNTHESIZE_ONLY_GETTER(D3DXVECTOR3, m_vOrg, Position);
	SYNTHESIZE_ONLY_GETTER(D3DXVECTOR3, m_vDir, Direction);

	enum eRaySpace
	{
		E_NONE,
		E_VIEW,
		E_WORLD,
		E_LOCAL
	};

	eRaySpace m_eRaySpace;

public:
	cRay(void);
	~cRay(void);
	
	static cRay GetRayAtViewSpace(int nScreenX, int nScreenY);
	static cRay GetRayAtWorldSpace(int nScreenX, int nScreenY);
	static cRay GetCustomRay(D3DXVECTOR3 vPos, D3DXVECTOR3 vDir);
	cRay RayAtLocalSpace(D3DXMATRIXA16& matWorld);
	bool GetPickedPosition(D3DXVECTOR3& vOut, LPD3DXMESH pMesh, D3DXVECTOR3 vWorldPos);
	bool GetPickedPosition(D3DXVECTOR3& vOut, D3DXVECTOR3& v1, D3DXVECTOR3& v2, D3DXVECTOR3& v3);
	bool IsPicked(ST_SPHERE* pSphere);
};

