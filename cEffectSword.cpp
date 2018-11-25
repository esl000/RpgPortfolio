#include "stdafx.h"
#include "cEffectSword.h"
#include "cAllocateHierarchy.h"
#include "cSkinnedMesh.h"


cEffectSword::cEffectSword()
		:m_pFindMesh(NULL)
		, m_vecVertex(NULL)
		, m_pOwnerMesh(NULL)
		, m_vecTriangle(NULL)
		, m_fColorChangeTime(0.0f)
		, m_cFaceColor(0.0f, 0.0f, 0.0f, 0.0f)
{
}


cEffectSword::~cEffectSword()
{
	m_vecVertex.clear();

	for each(auto p in m_vecTriangle)
	{
		SAFE_DELETE(p);
	}
	m_vecTriangle.clear();
}

void cEffectSword::Setup()
{
	//검매쉬 통짜로 미리 받는다 쓰는곳에서 그 받은 매쉬로 검의 윗부분 본을 찾는다
	ST_BONE* pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)m_pOwnerMesh->GetRootFrame(), "Ref_Weapon_Right");
	if (pFind->pEquips)
	{
		m_pFindMesh = pFind->pEquips->GetRootFrame();
	}

	m_vPrevPos[0] = D3DXVECTOR3(6, 0, 0);
	m_vPrevPos[1] = D3DXVECTOR3(2, 0, 0);
	
	D3DXVec3TransformCoord(&m_vPrevPos[0], &m_vPrevPos[0], &((ST_BONE*)m_pFindMesh)->CombinedTransformationMatrix);
	D3DXVec3TransformCoord(&m_vPrevPos[1], &m_vPrevPos[1], &((ST_BONE*)m_pFindMesh)->CombinedTransformationMatrix);
}

void cEffectSword::Update()
{
	D3DXVECTOR3 vCurrentPos[2];

	vCurrentPos[0] = D3DXVECTOR3(6, 0, 0);
	vCurrentPos[1] = D3DXVECTOR3(2, 0, 0);

	D3DXVec3TransformCoord(&vCurrentPos[0], &vCurrentPos[0], &((ST_BONE*)m_pFindMesh)->CombinedTransformationMatrix);
	D3DXVec3TransformCoord(&vCurrentPos[1], &vCurrentPos[1], &((ST_BONE*)m_pFindMesh)->CombinedTransformationMatrix);
		
	ST_PC_VERTEX v;

	//앞
	v.c = m_cFaceColor;
	v.p = vCurrentPos[1]; m_vecVertex.push_back(v);
	v.p = vCurrentPos[0]; m_vecVertex.push_back(v);
	v.p = m_vPrevPos[0]; m_vecVertex.push_back(v);

	////뒤
	v.p = vCurrentPos[1]; m_vecVertex.push_back(v);
	v.p = m_vPrevPos[0]; m_vecVertex.push_back(v);
	v.p = vCurrentPos[0]; m_vecVertex.push_back(v);

	cEffectTriangle* tri1 = new cEffectTriangle;
	tri1->Setup(m_vecVertex);
	tri1->SetRedSize(m_cFaceColor.r);
	tri1->SetGreenSize(m_cFaceColor.g);
	tri1->SetBlueSize(m_cFaceColor.b);
	tri1->SetAlphaSize(m_cFaceColor.a);
	tri1->SetColorChangeTime(m_fColorChangeTime);
	m_vecTriangle.push_back(tri1);
	m_vecVertex.clear();

	//앞
	v.c = m_cFaceColor;
	v.p = vCurrentPos[1]; m_vecVertex.push_back(v);
	v.p = m_vPrevPos[0]; m_vecVertex.push_back(v);
	v.p = m_vPrevPos[1]; m_vecVertex.push_back(v);
	
	////뒤
	v.p = m_vPrevPos[1]; m_vecVertex.push_back(v);
	v.p = m_vPrevPos[0]; m_vecVertex.push_back(v);
	v.p = vCurrentPos[1]; m_vecVertex.push_back(v);

	cEffectTriangle* tri2 = new cEffectTriangle;
	tri2->Setup(m_vecVertex);
	tri2->SetRedSize(m_cFaceColor.r);
	tri2->SetGreenSize(m_cFaceColor.g);
	tri2->SetBlueSize(m_cFaceColor.b);
	tri2->SetAlphaSize(m_cFaceColor.a);
	tri2->SetColorChangeTime(m_fColorChangeTime);
	m_vecTriangle.push_back(tri2);
	m_vecVertex.clear();

	m_vPrevPos[0] = vCurrentPos[0];
	m_vPrevPos[1] = vCurrentPos[1];

	m_fCurrentTime += g_pTimeManager->GetElapsedTime();
	
	for each(auto p in m_vecTriangle)
	{
		p->Update();
	}

	if (m_fCurrentTime > m_fMaxTime)
	{
		m_pDelegate->OnEffectFinish(this);
		return;
	}
}

void cEffectSword::Render()
{
	// 알파블랜딩 방식 결정.
	// 어떻게 색을 조합할지
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 텍스쳐 알파 옵션 설정
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	D3DXMATRIXA16 matWorld;	
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);	
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	
	for each(auto p in m_vecTriangle)
	{
		p->Render();
	}


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
