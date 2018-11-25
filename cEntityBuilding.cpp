#include "stdafx.h"
#include "cEntityBuilding.h"
#include "cMtlTex.h"
#include "cOctree.h"


cEntityBuilding::cEntityBuilding()
	: m_sName("")
	, m_pRootOctree(NULL)
	, m_pSurfaceMesh(NULL)
{
}


cEntityBuilding::~cEntityBuilding()
{
	SAFE_DELETE(m_pRootOctree);
}

void cEntityBuilding::Setup()
{
#ifdef MAPTOOL
	m_stFrustumSphere.vCenter = m_vPosition;
	m_stFrustumSphere.fRadius *= 1.4;
#else

	D3DXMATRIXA16 matWorld, matR, matT;
	float fAngle = atan2f(m_vDirection.x, m_vDirection.z) - D3DX_PI;
	D3DXMatrixRotationY(&matR, fAngle);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	matWorld = matR * matT;



	for (size_t i = 0; i < m_vecSurface.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecSurface[i].v1, &m_vecSurface[i].v1, &matWorld);
		D3DXVec3TransformCoord(&m_vecSurface[i].v2, &m_vecSurface[i].v2, &matWorld);
		D3DXVec3TransformCoord(&m_vecSurface[i].v3, &m_vecSurface[i].v3, &matWorld);
	}

	m_pRootOctree = new cOctree;
	m_pRootOctree->SetMainRoot(m_pRootOctree);
	m_pRootOctree->SetOctree(cOctree::E_ROOT,
		m_vPosition,
		m_stFrustumSphere.fRadius * 3,
		m_vecSurface);

	m_stFrustumSphere.vCenter = m_vPosition;
	m_stFrustumSphere.fRadius *= 1.4;

#endif
}

void cEntityBuilding::Update()
{
#ifdef MAPTOOL
	m_stFrustumSphere.vCenter = m_vPosition;
#else
#endif
}

void cEntityBuilding::Render()
{
	LPD3DXEFFECT pEffect = g_pShaderManager->getEffect("objshader.fx");
	D3DXMATRIXA16 matWorld, matR, matT;
	float fAngle = atan2f(m_vDirection.x, m_vDirection.z) - D3DX_PI;

	D3DXMatrixRotationY(&matR, fAngle);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	matWorld = matR * matT;
	
	D3DXVECTOR3 vEye = g_pUnitManager->GetCamera()->GetEye();

	D3DXMATRIXA16 matView, matProj;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProjection", &matProj);
	pEffect->SetVector("g_vWorldCameraPos", &D3DXVECTOR4(vEye.x, vEye.y, vEye.z, 1.f));

	UINT uiPasses;
	pEffect->Begin(&uiPasses, NULL);
	for (UINT i = 0; i < uiPasses; ++i)
	{
		pEffect->BeginPass(i);
		for (size_t i = 0; i < m_vecMtl.size(); ++i)
		{
			pEffect->SetTexture("Coin_Tex", m_vecMtl[i]->m_pTexture);
			pEffect->CommitChanges();
			m_pObjMesh->DrawSubset(i);
		}
		pEffect->EndPass();
	}
	pEffect->End();

	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//for (size_t i = 0; i < m_vecMtl.size(); ++i)
	//{
	//	g_pD3DDevice->SetMaterial(&m_vecMtl[i]->m_stMtl);
	//	g_pD3DDevice->SetTexture(0, m_vecMtl[i]->m_pTexture);
	//	m_pObjMesh->DrawSubset(i);
	//}

	//D3DXMatrixIdentity(&matWorld);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//g_pD3DDevice->SetTexture(0, NULL);
	//g_pD3DDevice->SetFVF(D3DFVF_XYZ);

	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	//	m_vecSurface.size(),
	//	&m_vecSurface[0].v1,
	//	sizeof(D3DXVECTOR3));


	//for (size_t i = 0; i < m_vecSurfaceMtl.size(); ++i)
	//{
	//	g_pD3DDevice->SetMaterial(&m_vecSurfaceMtl[i]->m_stMtl);
	//	g_pD3DDevice->SetTexture(0, m_vecSurfaceMtl[i]->m_pTexture);
	//	m_pSurfaceMesh->DrawSubset(i);
	//}
	//m_pRootOctree->Render();

	//D3DXMatrixRotationY(&matR, fAngle + D3DX_PI);
	//matWorld = matR * matT;
	//SphereRender(m_stFrustumSphere);
}
