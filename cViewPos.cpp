#include "stdafx.h"
#include "cViewPos.h"


cViewPos::cViewPos()
{
}


cViewPos::~cViewPos()
{
}

void cViewPos::Setup()
{

}

void cViewPos::Update()
{
	if (GetKeyState('A') & 0x8000)
	{
		float fAngle = atan2f(m_vDirection.x, m_vDirection.z) - D3DX_PI;
		fAngle -= 0.1f;
		D3DXMATRIXA16 matR, matT;
		D3DXMatrixRotationY(&matR, fAngle);

		D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
		D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
		D3DXVec3Normalize(&vDirection, &vDirection);
		m_vDirection = vDirection;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		float fAngle = atan2f(m_vDirection.x, m_vDirection.z) - D3DX_PI;
		fAngle += 0.1f;
		D3DXMATRIXA16 matR, matT;
		D3DXMatrixRotationY(&matR, fAngle);

		D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
		D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
		D3DXVec3Normalize(&vDirection, &vDirection);
		m_vDirection = vDirection;
	}

	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + 150.f * g_pTimeManager->GetElapsedTime() * m_vDirection;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - 150.f * g_pTimeManager->GetElapsedTime() * m_vDirection;
	}
}

void cViewPos::Render()
{

}

D3DXVECTOR3* cViewPos::GetPos()
{
	return &m_vPosition;
}
