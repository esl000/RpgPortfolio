#include "stdafx.h"
#include "cEntityObject.h"


cEntityObject::cEntityObject()
	: m_sName("")
	, m_pBoundingBox(NULL)
	, m_vBoundingBoxCenter(0, 0, 0)
	, m_bCollision(false)
	, m_isBBox(false)
{
}


cEntityObject::~cEntityObject()
{
	SAFE_RELEASE(m_pBoundingBox);
}

void cEntityObject::Setup()
{

	vecOrgBB = m_vecBoudingBox;

	D3DXMATRIXA16 matR, matT, matW;

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	float fAngle = atan2f(m_vDirection.x, m_vDirection.z) - D3DX_PI;
	D3DXMatrixRotationY(&matR, fAngle);


	D3DXVec3TransformCoord(&m_stFrustumSphere.vCenter, &m_stFrustumSphere.vCenter, &matT);

	D3DXVECTOR3 vTrans = m_vPosition + m_vBoundingBoxCenter;
	D3DXMatrixTranslation(&matT, vTrans.x, vTrans.y, vTrans.z);

	matW = matR * matT;

	for (size_t i = 0; i < m_vecBoudingBox.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecBoudingBox[i], &vecOrgBB[i], &matW);
	}
}

void cEntityObject::Update()
{
#ifdef MAPTOOL
	//m_stFrustumSphere.vCenter = m_vPosition;

	D3DXMATRIXA16 matR, matT, matW;

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	float fAngle = atan2f(m_vDirection.x, m_vDirection.z) - D3DX_PI;
	D3DXMatrixRotationY(&matR, fAngle);


	D3DXVec3TransformCoord(&m_stFrustumSphere.vCenter, &m_stFrustumSphere.vCenter, &matT);

	D3DXVECTOR3 vTrans = m_vPosition + m_vBoundingBoxCenter;
	D3DXMatrixTranslation(&matT, vTrans.x, vTrans.y, vTrans.z);

	matW = matR * matT;

	for (size_t i = 0; i < m_vecBoudingBox.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecBoudingBox[i], &vecOrgBB[i], &matW);
	}

#else
#endif


}

void cEntityObject::Render()
{
	SphereRender(m_stFrustumSphere);

	D3DXMATRIXA16 matWorld, matR, matT;

	float fAngle = atan2f(m_vDirection.x, m_vDirection.z) - D3DX_PI;
	D3DXMatrixRotationY(&matR, fAngle);

#ifdef DEBUG_SPHERE
	D3DXVECTOR3 vTrans = m_vPosition + m_vBoundingBoxCenter;

	D3DXMatrixTranslation(&matT, vTrans.x, vTrans.y, vTrans.z);
	m_matBBWorld = matR * matT;
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matBBWorld);
	//g_pD3DDevice->SetTexture(0, NULL);
	//m_pBoundingBox->DrawSubset(0);

	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(D3DFVF_XYZ);

	if (m_bCollision)
	{
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecBoudingBox.size() / 3,
			&m_vecBoudingBox[0],
			sizeof(D3DXVECTOR3));
	}
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#else

#endif
	if (m_isBBox)
		return;
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0.5f);

	LPD3DXEFFECT pEffect = g_pShaderManager->getEffect("objshader.fx");

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
			if (m_pObjMesh)
				m_pObjMesh->DrawSubset(i);
		}
		pEffect->EndPass();
	}
	pEffect->End();

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//for (size_t i = 0; i < m_vecMtl.size(); ++i)
	//{
	//	g_pD3DDevice->SetMaterial(&m_vecMtl[i]->m_stMtl);
	//	g_pD3DDevice->SetTexture(0, m_vecMtl[i]->m_pTexture);
	//	m_pObjMesh->DrawSubset(i);
	//}
}
