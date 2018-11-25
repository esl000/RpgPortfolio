#include "stdafx.h"
#include "cDieEffect.h"
#include "cRootItem.h"


cDieEffect::cDieEffect()
	: m_dwDeadAnim(0)
	, m_pRootInv(NULL)
{
	m_eEffectType = E_DIEEFFECT;
}


cDieEffect::~cDieEffect()
{
	SAFE_DELETE(m_pMesh);
	SAFE_RELEASE(m_pRootInv);
}

void cDieEffect::Setup()
{
	if (m_pMesh->GetCurrentAni() != m_dwDeadAnim)
		m_pMesh->SetAnimationIndex(m_dwDeadAnim);
	m_stFrustumSphere = m_pMesh->GetBoundingSphere();
}

void cDieEffect::Update()
{
	if (m_pMesh->GetCurrentAni() != m_dwDeadAnim)
		m_pMesh->SetAnimationIndex(m_dwDeadAnim);

	m_stFrustumSphere.vCenter = m_vPosition;
	double dPos, dPeriod;
	dPos = m_pMesh->GetAnimPosition();
	dPeriod = m_pMesh->GetAnimPeriod();
	dPos = dPos - dPeriod * (int)(dPos / dPeriod);

	if (dPos / dPeriod > 0.9)
	{
		m_pMesh->SetSpeed(0.f);
	}

	m_fCurrentTime += g_pTimeManager->GetElapsedTime();
	if (m_fCurrentTime > m_fMaxTime)
	{
		m_pDelegate->OnEffectFinish(this);
		return;
	}
}

void cDieEffect::Render()
{
	if (m_pMesh)
		m_pMesh->UpdateAndRender();
}
