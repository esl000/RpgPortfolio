#include "StdAfx.h"
#include "cRay.h"


cRay::cRay(void)
	: m_vOrg(0, 0, 0)
	, m_vDir(0, 0, 0)
	, m_eRaySpace(E_NONE)
{
}


cRay::~cRay(void)
{
}

cRay cRay::GetRayAtViewSpace( int nScreenX, int nScreenY )
{
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	cRay r;
	r.m_vDir.x = (( 2.0f * nScreenX) / vp.Width  - 1.0f) / matProj._11;
	r.m_vDir.y = ((-2.0f * nScreenY) / vp.Height + 1.0f) / matProj._22;
	r.m_vDir.z = 1.0f;

	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);

	r.m_eRaySpace = E_VIEW;

	return r;
}

cRay cRay::GetRayAtWorldSpace( int nScreenX, int nScreenY )
{
	cRay r = cRay::GetRayAtViewSpace(nScreenX, nScreenY);

	D3DXMATRIXA16 matView, matInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matInvView, 0, &matView);

	D3DXVec3TransformCoord(&r.m_vOrg, &r.m_vOrg, &matInvView);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvView);

	r.m_eRaySpace = E_WORLD;
	
	return r;
}

cRay cRay::GetCustomRay(D3DXVECTOR3 vPos, D3DXVECTOR3 vDir)
{
	cRay r;
	r.m_vOrg = vPos;
	r.m_vDir = vDir;
	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);
	r.m_eRaySpace = E_WORLD;
	return r;
}

cRay cRay::RayAtLocalSpace(D3DXMATRIXA16& matWorld)
{
	assert(m_eRaySpace == E_WORLD);

	cRay r;

	D3DXMATRIXA16 matInvWorld;

	D3DXMatrixInverse(&matInvWorld, 0, &matWorld);

	D3DXVec3TransformCoord(&r.m_vOrg, &m_vOrg, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_vDir, &m_vDir, &matInvWorld);

	r.m_eRaySpace = E_LOCAL;

	return r;
}

bool cRay::GetPickedPosition( D3DXVECTOR3& vOut, D3DXVECTOR3& v1, D3DXVECTOR3& v2, D3DXVECTOR3& v3 )
{
	assert(m_eRaySpace == E_WORLD);

	float u, v, t;
	if(D3DXIntersectTri(&v1, &v2, &v3, &m_vOrg, &m_vDir, &u, &v, &t))
	{
		vOut = m_vOrg + m_vDir * t;
		return true;
	}
	return false;
}

bool cRay::GetPickedPosition(D3DXVECTOR3& vOut, LPD3DXMESH pMesh, D3DXVECTOR3 vWorldPos)
{
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -vWorldPos.x;
	matInvWorld._42 = -vWorldPos.y;
	matInvWorld._43 = -vWorldPos.z;

	D3DXVECTOR3 vOrg, vDir;
	D3DXVec3TransformCoord(&vOrg, &m_vOrg, &matInvWorld);
	D3DXVec3TransformNormal(&vDir, &m_vDir, &matInvWorld);
	D3DXVec3Normalize(&vDir, &vDir);

	BOOL isPicked;
	DWORD a, b;
	float u, v, y;
	D3DXIntersect(pMesh, &vOrg, &vDir, &isPicked, &a, &u, &v, &y, NULL, &b);
	if (isPicked)
	{
		vOut = vOrg + vDir * y;
		return true;
	}
	return false;
}

bool cRay::IsPicked(ST_SPHERE* pSphere)
{
	assert(pSphere);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pSphere->vCenter.x;
	matInvWorld._42 = -pSphere->vCenter.y;
	matInvWorld._43 = -pSphere->vCenter.z;

	D3DXVECTOR3 vOrg, vDir;
	D3DXVec3TransformCoord(&vOrg, &m_vOrg, &matInvWorld);
	D3DXVec3TransformNormal(&vDir, &m_vDir, &matInvWorld);

	// (q.v)^2 - v.v * (q.q - r.r) >= 0
	float qv = D3DXVec3Dot(&vDir, &vOrg);
	float vv = D3DXVec3Dot(&vDir, &vDir);
	float qq = D3DXVec3Dot(&vOrg, &vOrg);
	float rr = pSphere->fRadius * pSphere->fRadius;

	return qv * qv - vv * (qq - rr) >= 0;
}
