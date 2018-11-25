#include "stdafx.h"
#include "cEffectLightningNova.h"

cEffectLightningNova::cEffectLightningNova()
{
}


cEffectLightningNova::~cEffectLightningNova()
{
	SAFE_DELETE(m_pMesh);
}

void cEffectLightningNova::Setup()
{	
}

void cEffectLightningNova::Update()
{
	double dPos, dPeriod;
	dPos = m_pMesh->GetAnimPosition();
	dPeriod = m_pMesh->GetAnimPeriod();
	dPos = dPos - dPeriod * (int)(dPos / dPeriod);

	if (dPos / dPeriod > 0.9)
	{
		m_pMesh->SetSpeed(0.f);
	}

	m_fCurrentTime += g_pTimeManager->GetElapsedTime();
	if (m_fCurrentTime > m_fMaxTime)
	{
		m_pDelegate->OnEffectFinish(this);
		return;
	}
}

void cEffectLightningNova::Render()
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
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	if (m_pMesh)
		m_pMesh->UpdateAndRender();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	
}
