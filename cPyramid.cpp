#include "StdAfx.h"
#include "cPyramid.h"


cPyramid::cPyramid(void)
	: m_mMatial(NULL)
	, m_pVertexBuffer(NULL)
{
}


cPyramid::~cPyramid(void)
{
	SAFE_DELETE(m_mMatial);
	SAFE_RELEASE(m_pVertexBuffer);
}

void cPyramid::Setup(D3DCOLOR c, D3DXMATRIXA16& mat)
{
	m_matWorld = mat;

	ST_PN_VERTEX v;

	D3DXVECTOR3 vNormal;
	D3DXVec3Cross(&vNormal, &D3DXVECTOR3(1, -1, -1), &D3DXVECTOR3(-1, -1, -1));

	v.p = D3DXVECTOR3( 0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,-1,-1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,-1,-1); m_vecVertex.push_back(v);

	D3DXVec3Cross(&vNormal, &D3DXVECTOR3(1, -1, 1), &D3DXVECTOR3(1, -1, -1));

	v.p = D3DXVECTOR3( 0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,-1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,-1,-1); m_vecVertex.push_back(v);

	D3DXVec3Cross(&vNormal, &D3DXVECTOR3(-1, -1, 1), &D3DXVECTOR3(1, -1, 1));

	v.p = D3DXVECTOR3( 0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,-1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,-1, 1); m_vecVertex.push_back(v);

	D3DXVec3Cross(&vNormal, &D3DXVECTOR3(-1, -1, -1), &D3DXVECTOR3(-1, -1, 1));

	v.p = D3DXVECTOR3( 0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,-1,-1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,-1, 1); m_vecVertex.push_back(v);

	D3DXVec3Cross(&vNormal, &D3DXVECTOR3(0, -0, -2), &D3DXVECTOR3(2, 0, -2));

	v.p = D3DXVECTOR3(-1,-1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1,-1,-1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,-1,-1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1,-1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,-1,-1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1,-1, 1); m_vecVertex.push_back(v);
	//EnterCriticalSection(&cs);
	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PN_VERTEX),
		0,
		ST_PN_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		0);
	//LeaveCriticalSection(&cs);
	ST_PN_VERTEX*			aVertex;
	m_pVertexBuffer->Lock(
		0, 0, (void**)&aVertex, 0);

	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		aVertex[i] = m_vecVertex[i];
	}

	m_pVertexBuffer->Unlock();
}

void cPyramid::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);

	if (m_mMatial)
		g_pD3DDevice->SetMaterial(m_mMatial);

	g_pD3DDevice->SetStreamSource(0, m_pVertexBuffer,
		0, sizeof(ST_PN_VERTEX));

	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,
		0, m_vecVertex.size() / 3);


	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	//	m_vecVertex.size() / 3,
	//	&m_vecVertex[0],
	//	sizeof(ST_PN_VERTEX));
}
