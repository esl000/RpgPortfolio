#include "stdafx.h"
#include "cPlayerActionAttack.h"
#include "cEffectHit.h"
#include "cEffectFont.h"

cPlayerActionAttack::cPlayerActionAttack()
		: m_pOwnerMesh(NULL)
		, m_pTarget(NULL)
		, m_bReload(true)
		, m_dwAttackAnim(0)
		, m_bSoundCheck(false)
{
}


cPlayerActionAttack::~cPlayerActionAttack()
{
}

void cPlayerActionAttack::Start()
{
	if (m_pOwner)
	{
		m_pOwnerMesh = m_pOwner->GetMesh();
		m_pTarget = m_pOwner->GetTarget();
		if (m_pTarget->GetName() == "데스윙")
			m_pOwner->SetAttackRange(10.0f);
		else
			m_pOwner->SetAttackRange(3.4f);
	}
}

void cPlayerActionAttack::Update()
{
	if (!m_pOwner || !m_pOwner->GetTarget() || !m_pTarget)
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}

	m_pTarget = m_pOwner->GetTarget();
	if (m_pTarget->GetName() == "데스윙")
		m_pOwner->SetAttackRange(10.0f);
	else
		m_pOwner->SetAttackRange(3.4f);

	if (D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) > m_pOwner->GetAttackRange())
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}

	if (!IsFocusSight(m_pOwner->GetPosition(), m_pTarget->GetPosition(), m_pOwner->GetDirection()))
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}

	//////////////////////////////////////////////////////////////////////
	if (m_pOwner->GetAnimChange() && m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwAttackAnim)
		m_pOwnerMesh->SetAnimationIndex(m_dwAttackAnim);

	////////////////////////////////////////////////////////////////////////
	// 플레이어는 필요없음......
	//D3DXVECTOR3 vDirection = m_pTarget->GetPosition() - m_pOwner->GetPosition();
	//D3DXVec3Normalize(&vDirection, &vDirection);
	//m_pOwner->SetDirection(vDirection);
	///////////////////////////////////////////////////////////////////////////

	/////////////이해 잘안됨..........
	double dPos, dPeriod;
	dPos = m_pOwnerMesh->GetAnimPosition();
	dPeriod = m_pOwnerMesh->GetAnimPeriod();
	dPos = dPos - dPeriod * (int)(dPos / dPeriod);

	if (!m_bSoundCheck && dPos / dPeriod > 0.3 && dPos / dPeriod < 0.4)
	{
		g_pSoundManager->play("OrcWeaponSwings", 1.0f);
		g_pSoundManager->play("OrcAttack", 1.0f);
		g_pSoundManager->play("OrcTargetHit", 1.0f);
		m_bSoundCheck = true;
	}

	if (dPos / dPeriod > 0.6) 
	{
		if (m_bReload)
		{
			m_bReload = false;
			m_bSoundCheck = false;
			cout << "damage!!" << endl;

			if (m_pOwner->GetMaxMp() - 5.0f > m_pOwner->GetCurrentMp())
			{
				m_pOwner->SetCurrentMp(m_pOwner->GetCurrentMp() + 5.0f);
			}
			else
			{
				m_pOwner->SetCurrentMp(100.0f);
			}
			
			m_pTarget->Damage(m_pOwner->GetCurrentDamage());

			cEffectHit* pEffect = new cEffectHit;
			pEffect->SetPosition(m_pTarget->GetPosition());
			pEffect->SetDirection(m_pTarget->GetDirection());
			pEffect->SetEffectUnit(m_pTarget);
			pEffect->SetMaxTime(0.2f);
			pEffect->Setup();
			g_pEffectManager->RegisterEffect(pEffect);
					
			cEffectFont* pFont = new cEffectFont;
			pFont->SetPosition(m_pTarget->GetPosition());
			pFont->SetDirection(m_pTarget->GetDirection());
			pFont->SetEffectUnit(m_pTarget);
			pFont->SetDamage(m_pOwner->GetCurrentDamage());
			pFont->SetFontState(cEffectFont::E_BASIC);
			pFont->Setup();
			g_pEffectManager->RegisterEffect(pFont);
		}
	}
	else if (dPos / dPeriod < 0.6)
		m_bReload = true;
}
