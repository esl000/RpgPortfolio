#include "stdafx.h"
#include "cActionAttack.h"
#include "cEffectFont.h"

cActionAttack::cActionAttack()
	: m_pOwnerMesh(NULL)
	, m_pTarget(NULL)
	, m_bReload(true)
	, m_dwAttackAnim(0)
	, m_bSoundCheck(false)
{
}


cActionAttack::~cActionAttack()
{
}


void cActionAttack::Start()
{
	if (m_pOwner)
	{
		m_pOwnerMesh = m_pOwner->GetMesh();
		m_pTarget = m_pOwner->GetTarget();
	}
}

void cActionAttack::Update()
{
	if (!m_pOwner || !m_pOwner->GetTarget() || !m_pTarget)
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}
	m_pTarget = m_pOwner->GetTarget();
	if (D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) > m_pOwner->GetAttackRange())
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}

	if (m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwAttackAnim)
		m_pOwnerMesh->SetAnimationIndex(m_dwAttackAnim);

	D3DXVECTOR3 vDirection = m_pTarget->GetPosition() - m_pOwner->GetPosition();
	D3DXVec3Normalize(&vDirection, &vDirection);
	m_pOwner->SetDirection(vDirection);

	double dPos, dPeriod;
	dPos = m_pOwnerMesh->GetAnimPosition();
	dPeriod = m_pOwnerMesh->GetAnimPeriod();
	dPos = dPos - dPeriod * (int)(dPos / dPeriod);

	if (!m_bSoundCheck && dPos / dPeriod > 0.3 && dPos / dPeriod < 0.4)
	{
		g_pSoundManager->play("OrcDamage", 1.0f);
		m_bSoundCheck = true;
	}

	if (dPos / dPeriod > 0.6)
	{
		if (m_bReload)
		{
			m_bReload = false;
			m_bSoundCheck = false;
			m_pTarget->Damage(m_pOwner->GetCurrentDamage());

			cEffectFont* pFont = new cEffectFont;
			pFont->SetPosition(m_pTarget->GetPosition());
			pFont->SetDirection(m_pTarget->GetDirection());
			pFont->SetEffectUnit(m_pTarget);
			pFont->SetDamage(m_pOwner->GetCurrentDamage());
			pFont->SetFontState(cEffectFont::E_BASIC);
			pFont->Setup();
			g_pEffectManager->RegisterEffect(pFont);

			if (m_pTarget->GetMaxMp() - 5.0f > m_pTarget->GetCurrentMp())
			{
				m_pTarget->SetCurrentMp(m_pTarget->GetCurrentMp() + 5.0f);
			}
			else
			{
				m_pTarget->SetCurrentMp(100.0f);
			}
		}
	}
	else
		m_bReload = true;

}