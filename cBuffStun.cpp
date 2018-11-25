#include "stdafx.h"
#include "cBuffStun.h"


cBuffStun::cBuffStun()
	: m_pAction(NULL)
	, m_pOwnerMesh(NULL)
	, m_dwStunAnim(0)
	, m_fStunTime(0)
	//, m_fOrgSpeed(0)
{
}


cBuffStun::~cBuffStun()
{
	SAFE_RELEASE(m_pAction);
}

void cBuffStun::Start()
{
	m_pOwnerMesh = m_pOwner->GetMesh();
	m_pAction = m_pOwner->GetUnitAction();
	m_pOwner->SetUnitAction(NULL);
	//m_fOrgSpeed = m_pOwner->GetSpeed();
	//m_pOwner->SetSpeed(0.1);
}

void cBuffStun::Update()
{
	if (m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwStunAnim)
		m_pOwnerMesh->SetAnimationIndex(m_dwStunAnim);

	m_fPassedTime == g_pTimeManager->GetElapsedTime();

	if (m_fPassedTime >= m_fStunTime)
	{
		//m_pOwner->SetSpeed(m_fOrgSpeed);
		m_pOwner->SetUnitAction(m_pAction);
		m_pDelegate->OnBuffFinished(this);
		return;
	}
}
