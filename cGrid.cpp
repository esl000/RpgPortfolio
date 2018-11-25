#include "StdAfx.h"
#include "cGrid.h"
#include "cPyramid.h"

cGrid::cGrid(void)
	: m_pVertexBuffer(NULL)
{
}


cGrid::~cGrid(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
}

void cGrid::Setup( int nHalf, float fInterval )
{
	// 바닥 버텍스 생성
	float fMax = nHalf * fInterval;
	float fMin = -fMax;

	ST_PC_VERTEX v;

	for (int i = 1; i <= nHalf; ++i)
	{
		if(i % 5 == 0)
		{
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		}
		else
		{
			v.c = D3DCOLOR_XRGB(140, 140, 140);
		}
		v.p = D3DXVECTOR3(fMin, 0.f, fInterval * i); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0.f, fInterval * i); m_vecVertex.push_back(v);
		
		v.p = D3DXVECTOR3(fMin, 0.f, -fInterval * i); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0.f, -fInterval * i); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fInterval * i, 0.f, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fInterval * i, 0.f, fMax); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-fInterval * i, 0.f, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-fInterval * i, 0.f, fMax); m_vecVertex.push_back(v);
	}

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0.f, 0.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0.f, 0.f); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0.f, fMin, 0.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.f, fMax, 0.f); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0.f, 0.f, fMin); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.f, 0.f, fMax); m_vecVertex.push_back(v);

	D3DXMATRIXA16 matS, matR, mat;
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);

	cPyramid* pPyramid = NULL;
	D3DMATERIAL9* pMaterial;

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	mat = matS * matR;
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0 ,0), mat);

	pMaterial = new D3DMATERIAL9;
	pMaterial->Ambient = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pMaterial->Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	pMaterial->Specular = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	pMaterial->Power = 1.f;
	pMaterial->Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	pPyramid->SetMaterial(pMaterial);

	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	mat = matS * matR;
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), mat);

	pMaterial = new D3DMATERIAL9;
	pMaterial->Ambient = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	pMaterial->Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	pMaterial->Specular = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	pMaterial->Power = 1.f;
	pMaterial->Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	pPyramid->SetMaterial(pMaterial);

	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	mat = matS * matR;
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), mat);

	pMaterial = new D3DMATERIAL9;
	pMaterial->Ambient = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);
	pMaterial->Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	pMaterial->Specular = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);
	pMaterial->Power = 1.f;
	pMaterial->Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	pPyramid->SetMaterial(pMaterial);

	m_vecPyramid.push_back(pPyramid);

	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PC_VERTEX),
		0,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		0);
	ST_PC_VERTEX*			aVertex;
	m_pVertexBuffer->Lock(
		0, 0, (void**)&aVertex, 0);

	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		aVertex[i] = m_vecVertex[i];
	}

	m_pVertexBuffer->Unlock();
}

void cGrid::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetStreamSource(0, m_pVertexBuffer,
		0, sizeof(ST_PC_VERTEX));

	g_pD3DDevice->DrawPrimitive(D3DPT_LINELIST,
		0, m_vecVertex.size() / 2);

	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
	//	m_vecVertex.size() / 2,
	//	&m_vecVertex[0],
	//	sizeof(ST_PC_VERTEX));


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	for each(auto p in m_vecPyramid)
	{
		p->Render();
	}

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
}
