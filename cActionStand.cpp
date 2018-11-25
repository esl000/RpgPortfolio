#include "stdafx.h"
#include "cActionStand.h"


cActionStand::cActionStand()
	: m_pOwnerMesh(NULL)	
{
}


cActionStand::~cActionStand()
{
}

void cActionStand::Start()
{
	if (m_pOwner)
		m_pOwnerMesh = m_pOwner->GetMesh();
}

void cActionStand::Update()
{
	if (m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != 0)
		m_pOwnerMesh->SetAnimationIndex(0);
}
