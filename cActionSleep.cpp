#include "stdafx.h"
#include "cActionSleep.h"


cActionSleep::cActionSleep()
		:m_pOwnerMesh(NULL)
{
}


cActionSleep::~cActionSleep()
{
}

void cActionSleep::Start()
{
	if (m_pOwner)
	{
		m_pOwnerMesh = m_pOwner->GetMesh();
	}		
}

void cActionSleep::Update()
{
	if (m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != 10)
	{
		m_pOwnerMesh->SetAnimationIndex(10);	
	}
}
