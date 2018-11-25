#include "stdafx.h"
#include "cSkillActionCyclone.h"
#include "cEffectCyclone.h"

cSkillActionCyclone::cSkillActionCyclone()
		: m_pOwnerMesh(NULL)
		, m_pTarget(NULL)
		, m_bReload(true)
		, m_dwAttackAnim(0)
		, m_bSoundCheck(false)
		, m_bIsEffect(false)
		, m_fActionExitTime(0.0f)
{
}


cSkillActionCyclone::~cSkillActionCyclone()
{
}

void cSkillActionCyclone::Start()
{
	if (m_pOwner)
	{
		m_pOwnerMesh = m_pOwner->GetMesh();
		m_pTarget = m_pOwner->GetTarget();
	}
}

void cSkillActionCyclone::Update()
{
	if (!m_pOwner || !m_pOwner->GetTarget() || !m_pTarget)
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}
	m_pTarget = m_pOwner->GetTarget();

	if (m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwAttackAnim)
		m_pOwnerMesh->SetAnimationIndex(m_dwAttackAnim);

	double dPos, dPeriod;
	dPos = m_pOwnerMesh->GetAnimPosition();
	dPeriod = m_pOwnerMesh->GetAnimPeriod();
	dPos = dPos - dPeriod * (int)(dPos / dPeriod);

	if (!m_bSoundCheck && dPos / dPeriod > 0.3 && dPos / dPeriod < 0.4)
	{
		g_pSoundManager->play("OrcDamage", 1.0f);
		m_bSoundCheck = true;
	}

	if (!m_bIsEffect)
	{
		for (int i = -1; i < 2; ++i)
		{
			for (int j = 1; j > -2; --j)
			{
				if (i == 0)
					continue;
				if (j == 0)
					continue;

				cEffectCyclone* pEffect = new cEffectCyclone;
				D3DXVECTOR3 vec = m_pTarget->GetPosition();

				vec.x += i * 20;
				vec.z += j * 20;

				pEffect->SetPosition(vec);
				pEffect->SetDirection(m_pOwner->GetDirection());

				cSkinnedMesh* pMesh = new cSkinnedMesh("effect/deathwing/Cyclonefire_state", "Cyclonefire_state.X");
				pMesh->SetPosition(vec);
				pMesh->SetDirection(m_pOwner->GetDirection());

				pEffect->SetMesh(pMesh);
				pEffect->SetMaxTime(10.f);
				pEffect->SetEffectUnit(m_pOwner);
				pEffect->Setup();
				g_pEffectManager->RegisterEffect(pEffect);
			}
		}
		m_bIsEffect = true;
		//g_pSoundManager->play("ThunderClap", 1.0f);
	}

	if (dPos / dPeriod > 0.9)
		m_pDelegate->OnUnitActionFinish(this);
}
