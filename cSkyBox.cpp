#include "stdafx.h"
#include "cSkyBox.h"
#include "cUnitPlayer.h"


cSkyBox::cSkyBox()
	: m_pPlayer(NULL)
	, m_pMesh(NULL)
{
}


cSkyBox::~cSkyBox()
{
	SAFE_DELETE(m_pMesh);
}

void cSkyBox::Setup()
{
	m_pMesh = new cSkinnedMesh("skybox", "bladesedgeskybox.X");
	m_pMesh->SetStandSpeedSet(false);
	D3DXVECTOR3 vPosition = D3DXVECTOR3(m_pPlayer->GetPosition().x, -150, m_pPlayer->GetPosition().z);
	m_pMesh->SetPosition(vPosition);
	//m_pMesh->SetDirection(m_pPlayer->GetDirection());
}

void cSkyBox::Update()
{
	D3DXVECTOR3 vPosition = D3DXVECTOR3(m_pPlayer->GetPosition().x, -150, m_pPlayer->GetPosition().z);
	m_pMesh->SetPosition(vPosition);
	//m_pMesh->SetDirection(m_pPlayer->GetDirection());
}

void cSkyBox::Render()
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
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	if (m_pMesh)
		m_pMesh->UpdateAndRender();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
