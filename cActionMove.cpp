#include "stdafx.h"
#include "cActionMove.h"


cActionMove::cActionMove()
	: m_pOwnerMesh(NULL)
	, m_vDest(0, 0, 0)
	, m_dwWalkAnim(0)
	, m_vInitDir(0, 0, 0)
{
}


cActionMove::~cActionMove()
{
}

void cActionMove::Start()
{
	if (m_pOwner)
		m_pOwnerMesh = m_pOwner->GetMesh();
}

void cActionMove::Update()
{
	if (m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != 2)
		m_pOwnerMesh->SetAnimationIndex(2);

	D3DXVECTOR3 vDirection = m_vDest - m_pOwner->GetPosition();

	D3DXVec3Normalize(&vDirection, &vDirection);
	m_pOwner->SetDirection(vDirection);
	D3DXVECTOR3 vPos = m_pOwner->GetPosition() + m_pOwner->GetCurrentSpeed() * g_pTimeManager->GetElapsedTime() * vDirection;
	D3DXVECTOR3 vDest;

	//if(g_pTileManager->GetHeight(vDest, vPos))
	//{
	m_pOwner->SetPosition(vPos);
	//}

	if (D3DXVec3Length(&(m_vDest - m_pOwner->GetPosition())) <= m_pOwner->GetCurrentSpeed() * g_pTimeManager->GetElapsedTime() + 0.3f)
	{
		m_pOwner->SetDirection(m_vInitDir);
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}
}
