#include "stdafx.h"
#include "cPlayerActionStand.h"


cPlayerActionStand::cPlayerActionStand()
		: m_pOwnerMesh(NULL)
		, m_dwStandAnim(0)
{
}


cPlayerActionStand::~cPlayerActionStand()
{
}

void cPlayerActionStand::Start()
{
	if (m_pOwner)
		m_pOwnerMesh = m_pOwner->GetMesh();
}

void cPlayerActionStand::Update()
{
	if (m_pOwner->GetAnimChange() && m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwStandAnim && m_pOwner->GetGravityState() == cUnit::E_NONE)
		m_pOwnerMesh->SetAnimationIndex(m_dwStandAnim);
}
