#include "stdafx.h"
#include "cLight.h"


cLight::cLight()
	: m_pAction(NULL)
	, m_nIndex(0)
{
}


cLight::~cLight()
{
	SAFE_RELEASE(m_pAction);
}

void cLight::Setup()
{
	ZeroMemory(&m_lLight, sizeof(D3DLIGHT9));
	m_lLight.Type = D3DLIGHT_DIRECTIONAL;
	m_lLight.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f) * 0.8f;
	m_lLight.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f) * 0.8f;
	m_lLight.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f) * 0.8f;
	m_lLight.Direction = D3DXVECTOR3(0.f, 1.f, 1.f);
}

void cLight::Update()
{
	g_pD3DDevice->SetLight(m_nIndex, &m_lLight);
	g_pD3DDevice->LightEnable(m_nIndex, true);
}
