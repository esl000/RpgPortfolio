#include "StdAfx.h"
#include "cFrustum.h"


cFrustum::cFrustum(void)
{
}


cFrustum::~cFrustum(void)
{
}

void cFrustum::Setup()
{
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1,  0));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1,  1,  0));
	m_vecProjVertex.push_back(D3DXVECTOR3( 1,  1,  0));
	m_vecProjVertex.push_back(D3DXVECTOR3( 1, -1,  0));

	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1,  1));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1,  1,  1));
	m_vecProjVertex.push_back(D3DXVECTOR3( 1,  1,  1));
	m_vecProjVertex.push_back(D3DXVECTOR3( 1, -1,  1));

	m_vecPlane.resize(6);
}

void cFrustum::Update()
{
	std::vector<D3DXVECTOR3> vecWorldVeretx(m_vecProjVertex.size());

	D3DXMATRIXA16 matProj, matView;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	for (size_t i = 0; i < vecWorldVeretx.size(); ++i)
	{
		D3DXVec3Unproject(
			&vecWorldVeretx[i],
			&m_vecProjVertex[i],
			NULL,
			&matProj,
			&matView,
			NULL);
	}

	int nCnt = 0;
	// Àü
	D3DXPlaneFromPoints(&m_vecPlane[nCnt++],
		&vecWorldVeretx[0],
		&vecWorldVeretx[1],
		&vecWorldVeretx[2]); 
	// µÞ
	D3DXPlaneFromPoints(&m_vecPlane[nCnt++],
		&vecWorldVeretx[6],
		&vecWorldVeretx[5],
		&vecWorldVeretx[4]);
	// »ó
	D3DXPlaneFromPoints(&m_vecPlane[nCnt++],
		&vecWorldVeretx[1],
		&vecWorldVeretx[5],
		&vecWorldVeretx[6]);
	//ÇÏ
	D3DXPlaneFromPoints(&m_vecPlane[nCnt++],
		&vecWorldVeretx[0],
		&vecWorldVeretx[3],
		&vecWorldVeretx[7]);
	//ÁÂ
	D3DXPlaneFromPoints(&m_vecPlane[nCnt++],
		&vecWorldVeretx[5],
		&vecWorldVeretx[1],
		&vecWorldVeretx[0]);
	//¿ì
	D3DXPlaneFromPoints(&m_vecPlane[nCnt++],
		&vecWorldVeretx[2],
		&vecWorldVeretx[6],
		&vecWorldVeretx[7]);
}

bool cFrustum::IsIn( ST_SPHERE* pSphere )
{
	for each(D3DXPLANE p in m_vecPlane)
	{
		if(D3DXPlaneDotCoord(&p, &pSphere->vCenter) > pSphere->fRadius)
			return false;
	}
	return true;
}

