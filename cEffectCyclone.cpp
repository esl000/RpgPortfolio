#include "stdafx.h"
#include "cEffectCyclone.h"


cEffectCyclone::cEffectCyclone()
	:m_vOrgTargetPos(0.0f, 0.0f, 0.0f)
{
}


cEffectCyclone::~cEffectCyclone()
{
	SAFE_DELETE(m_pMesh);
}

void cEffectCyclone::Setup()
{
	if (m_pMesh && m_pUnit)
	{
		m_vOrgTargetPos = m_pUnit->GetTarget()->GetPosition();
	}
}

void cEffectCyclone::Update()
{	
	D3DXVECTOR3 vDir = m_vPosition - m_vOrgTargetPos;
	D3DXVec3Normalize(&vDir, &vDir);
	m_pMesh->SetDirection(vDir);

	m_vPosition = m_vPosition - 11.0f * vDir * g_pTimeManager->GetElapsedTime();
	m_pMesh->SetPosition(m_vPosition);

	m_fCurrentTime += g_pTimeManager->GetElapsedTime();
	if (m_fCurrentTime > m_fMaxTime)
	{
		//m_pUnit->SetCurrentDamage(m_pUnit->GetOrigDamage());
		m_pDelegate->OnEffectFinish(this);
		return;
	}
}

void cEffectCyclone::Render()
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
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	if (m_pMesh)
		m_pMesh->UpdateAndRender();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
