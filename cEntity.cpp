#include "stdafx.h"
#include "cEntity.h"


cEntity::cEntity()
	: m_pDelegate(NULL)
	, m_pObjMesh(NULL)
	, m_pSphereMesh(NULL)
{
	ZeroMemory(&m_stFrustumSphere, sizeof(ST_SPHERE));
}


cEntity::~cEntity()
{
	SAFE_RELEASE(m_pObjMesh);
}

void cEntity::SphereRender(ST_SPHERE stSphere)
{
#ifdef DEBUG_SPHERE
	/*if (m_pSphereMesh)
	{
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, stSphere.vCenter.x, stSphere.vCenter.y, stSphere.vCenter.z);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	m_pSphereMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	else
	{
	D3DXCreateSphere(g_pD3DDevice, stSphere.fRadius, 8, 8, &m_pSphereMesh, NULL);
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, stSphere.vCenter.x, stSphere.vCenter.y, stSphere.vCenter.z);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	m_pSphereMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}*/
#else

#endif
}

void cEntity::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
