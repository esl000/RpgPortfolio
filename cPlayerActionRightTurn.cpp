#include "stdafx.h"
#include "cPlayerActionRightTurn.h"


cPlayerActionRightTurn::cPlayerActionRightTurn()
		:m_pOwnerMesh(NULL)
{
}


cPlayerActionRightTurn::~cPlayerActionRightTurn()
{
}

void cPlayerActionRightTurn::Start()
{
	if (m_pOwner)
		m_pOwnerMesh = m_pOwner->GetMesh();
}

void cPlayerActionRightTurn::Update()
{	
	float fAngle = atan2f(m_pOwner->GetDirection().x, m_pOwner->GetDirection().z) - D3DX_PI;
	fAngle += 0.1f;
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, fAngle);

	D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
	D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
	D3DXVec3Normalize(&vDirection, &vDirection);
	m_pOwner->SetDirection(vDirection);
}
