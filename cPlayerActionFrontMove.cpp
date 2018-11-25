#include "stdafx.h"
#include "cPlayerActionFrontMove.h"
#include "cEffectTrajectory.h"

cPlayerActionFrontMove::cPlayerActionFrontMove()
		:m_pOwnerMesh(NULL)
		, m_dwWalkAnim(0)
{
}


cPlayerActionFrontMove::~cPlayerActionFrontMove()
{
}

void cPlayerActionFrontMove::Start()
{
	if (m_pOwner)
		m_pOwnerMesh = m_pOwner->GetMesh();
}

void cPlayerActionFrontMove::Update()
{
	if (m_pOwner->GetAnimChange() && m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwWalkAnim && m_pOwner->GetGravityState() == cUnit::E_NONE)
		m_pOwnerMesh->SetAnimationIndex(m_dwWalkAnim);


	D3DXVECTOR3 vPos = m_pOwner->GetPosition() + m_pOwner->GetCurrentSpeed() * g_pTimeManager->GetElapsedTime() * m_pOwner->GetDirection();
	D3DXVECTOR3 vDest;

	ST_SPHERE stSphere(vPos, m_pOwner->GetFrustumSphere().fRadius);

	if (g_pIntersectManager->IntersectEntitys(stSphere, m_pOwner->GetDirection()))
		return;

	//if (g_pTileManager->GetHeight(vDest, vPos))
	//{
	m_pOwner->SetPosition(vPos);
	//}

	//if (g_pIntersectManager->IntersectInBuilding(m_pOwner->GetFrustumSphere(), vPos, vDest))
	//{
	//	vPos = vDest;
	//}

	//g_pTileManager->GetHeight(vDest, vPos.x, vPos.z);
	//m_pOwner->SetPosition(vPos);
}
