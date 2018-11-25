#include "stdafx.h"
#include "cPlayerActionPosMove.h"


cPlayerActionPosMove::cPlayerActionPosMove()
	: m_pOwnerMesh(NULL)
	, m_vDest(0, 0, 0)
	, m_dwWalkAnim(0)
{
}


cPlayerActionPosMove::~cPlayerActionPosMove()
{
}

void cPlayerActionPosMove::Start()
{
	if (m_pOwner)
		m_pOwnerMesh = m_pOwner->GetMesh();
}

void cPlayerActionPosMove::Update()
{
	if (m_pOwner->GetAnimChange() && m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwWalkAnim && m_pOwner->GetGravityState() == cUnit::E_NONE)
		m_pOwnerMesh->SetAnimationIndex(m_dwWalkAnim);


	D3DXVECTOR3 vDirection = m_vDest - m_pOwner->GetPosition();

	D3DXVec3Normalize(&vDirection, &vDirection);
	m_pOwner->SetDirection(vDirection);

	D3DXVECTOR3 vPos = m_pOwner->GetPosition() + m_pOwner->GetCurrentSpeed() * g_pTimeManager->GetElapsedTime() * m_pOwner->GetDirection();
	D3DXVECTOR3 vDest;

	ST_SPHERE stSphere(vPos, m_pOwner->GetFrustumSphere().fRadius);

	if (g_pIntersectManager->IntersectEntitys(stSphere, vDirection))
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}

	m_pOwner->SetPosition(vPos);

	if (D3DXVec3Length(&(m_vDest - m_pOwner->GetPosition())) <= m_pOwner->GetCurrentSpeed() * g_pTimeManager->GetElapsedTime() + 0.3f)
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}
}
