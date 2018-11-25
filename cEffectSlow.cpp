#include "stdafx.h"
#include "cEffectSlow.h"


cEffectSlow::cEffectSlow()
{
}


cEffectSlow::~cEffectSlow()
{
	SAFE_DELETE(m_pMesh);
}

void cEffectSlow::Setup()
{
	m_pMesh = new cSkinnedMesh("effect/Ice_precast_uber_base", "Ice_precast_uber_base.X");
	if (m_pMesh)
	{
		m_pMesh->SetPosition(m_vPosition);
		m_pMesh->SetDirection(m_vDirection);		
	}

	if (m_pUnit)
	{
		m_pUnit->SetCurrentSpeed(m_pUnit->GetOriginSpeed() * 0.5f);	
	}
}

void cEffectSlow::Update()
{
	float fAngle = atan2f(m_pUnit->GetDirection().x, m_pUnit->GetDirection().z) - D3DX_PI;
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, fAngle);

	D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.0f);
	D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
	D3DXVec3Normalize(&vDirection, &vDirection);
	m_pMesh->SetDirection(vDirection);

	D3DXVECTOR3 vec = m_pUnit->GetPosition() + 0.2f * m_pUnit->GetDirection();
	vec.y += 0.1f;

	m_pMesh->SetPosition(vec);

	m_fCurrentTime += g_pTimeManager->GetElapsedTime();
	if (m_fCurrentTime > m_fMaxTime)
	{
		m_pUnit->SetCurrentSpeed(m_pUnit->GetOriginSpeed());
		m_pDelegate->OnEffectFinish(this);
		return;
	}
}

void cEffectSlow::Render()
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
