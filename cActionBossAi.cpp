#include "stdafx.h"
#include "cActionBossAi.h"
#include "cActionStand.h"
#include "cActionAttack.h"
#include "cActionMove.h"
#include "cActionSleep.h"
#include "cSkillActionCleave.h"
#include "cSkillActionCyclone.h"

cActionBossAi::cActionBossAi()
			: m_pCurrentAction(NULL)
			, m_pTarget(NULL)
			, m_vOrgPos(0, 0, 0)
			, m_vOrgDir(0, 0, 0)
			, m_dwWalkAnim(2)
			, m_dwAttackAnim(3)
			, m_eCurrentAct(E_STAND)
			, m_isDefense(false)
			, m_isSleep(true)			
{
	for (int i = 0; i < 1; ++i)
	{
		m_nSkillCurrentTime[i] = 0;
	}
	m_nSkillFireTime[0] = 5.0f;
	m_nSkillFireTime[1] = 10.0f;
}


cActionBossAi::~cActionBossAi()
{
	SAFE_RELEASE(m_pCurrentAction);
}

void cActionBossAi::Start()
{
	cActionSleep* pAction = new cActionSleep;
	pAction->SetOwner(m_pOwner);
	pAction->SetDelegate(this);
	pAction->Start();
	m_pTarget = m_pOwner->GetTarget();
	m_pCurrentAction = pAction;
}

void cActionBossAi::Update()
{
	if (m_isSleep)
		SleepAi();
	else
	{
		for (int i = 0; i < 2; ++i)
		{
			m_nSkillCurrentTime[i] += g_pTimeManager->GetElapsedTime();
		}
	
		if (m_isDefense)		
			DefenceAi();
		else
			BaseAi();

		if (m_eCurrentAct != E_SKILL && m_nSkillCurrentTime[0] > m_nSkillFireTime[0])
		{
			m_nSkillCurrentTime[0] = 0.0f;
			m_eCurrentAct = E_SKILL;
			SAFE_RELEASE(m_pCurrentAction);
			cSkillActionCleave* pAction = new cSkillActionCleave;
			pAction->SetOwner(m_pOwner);
			pAction->SetDelegate(this);
			pAction->SetAttackAnim(5);			
			pAction->Start();
			m_pCurrentAction = pAction;
		}
		else if (m_eCurrentAct != E_SKILL && m_nSkillCurrentTime[1] > m_nSkillFireTime[1])
		{
			m_nSkillCurrentTime[1] = 0.0f;
			m_eCurrentAct = E_SKILL;
			SAFE_RELEASE(m_pCurrentAction);
			cSkillActionCyclone* pAction = new cSkillActionCyclone;
			pAction->SetOwner(m_pOwner);
			pAction->SetDelegate(this);
			pAction->SetAttackAnim(6);
			pAction->Start();
			m_pCurrentAction = pAction;
		}
	}

	if (m_eCurrentAct == E_STAND)
	{
		m_fCurrentTime += g_pTimeManager->GetElapsedTime();
		if (m_fCurrentTime > 30.0f)
		{
			m_isDefense = false;
			m_isSleep = true;
		}
	}
	else	
		m_fCurrentTime = 0.0f;	

	if (m_pCurrentAction)
		m_pCurrentAction->Update();
}

void cActionBossAi::SleepAi()
{
	if (IsFocusSight(m_pOwner->GetPosition(), m_pTarget->GetPosition(), m_pOwner->GetDirection())
		&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < 65.f /*(m_pOwner->GetLevel() - m_pTarget->GetLevel())*/)
	{
		if (m_eCurrentAct != E_STAND)
		{
			m_isSleep = false;
			m_eCurrentAct = E_STAND;
			SAFE_RELEASE(m_pCurrentAction);
			cActionStand* pAction = new cActionStand;
			pAction->SetOwner(m_pOwner);
			pAction->SetDelegate(this);
			pAction->Start();
			m_pCurrentAction = pAction;
		}
	}
	else
	{
		if (m_eCurrentAct != E_SLEEP)
		{
			m_eCurrentAct = E_SLEEP;
			SAFE_RELEASE(m_pCurrentAction);
			cActionSleep* pAction = new cActionSleep;
			pAction->SetOwner(m_pOwner);
			pAction->SetDelegate(this);
			pAction->Start();
			m_pCurrentAction = pAction;
		}
	}
}

void cActionBossAi::BaseAi()
{
	if (m_eCurrentAct != E_SKILL)
	{
		if (D3DXVec3Length(&(m_pOwner->GetPosition() - m_vOrgPos)) < 150.f)
		{
			if (IsFocusSight(m_pOwner->GetPosition(), m_pTarget->GetPosition(), m_pOwner->GetDirection())
				&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < 50.f /*(m_pOwner->GetLevel() - m_pTarget->GetLevel())*/)
			{
				if (D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) <= m_pOwner->GetAttackRange())
				{
					if (m_eCurrentAct != E_ATTACK)
					{
						m_eCurrentAct = E_ATTACK;
						SAFE_RELEASE(m_pCurrentAction);
						cActionAttack* pAction = new cActionAttack;
						pAction->SetOwner(m_pOwner);
						pAction->SetDelegate(this);
						pAction->SetAttackAnim(m_dwAttackAnim);
						pAction->Start();
						m_pCurrentAction = pAction;
					}
				}
				else
				{
					if (m_eCurrentAct != E_TARGETMOVE)
					{
						m_eCurrentAct = E_TARGETMOVE;
						SAFE_RELEASE(m_pCurrentAction);
						cActionMove* pAction = new cActionMove;
						pAction->SetOwner(m_pOwner);
						pAction->SetDelegate(this);
						pAction->SetDest(m_pTarget->GetPosition());
						pAction->SetWalkAnim(m_dwWalkAnim);
						pAction->Start();
						m_pCurrentAction = pAction;
					}
				}
			}
			else
			{
				if (m_eCurrentAct != E_POSMOVE && m_eCurrentAct != E_STAND)
				{
					m_eCurrentAct = E_STAND;
					SAFE_RELEASE(m_pCurrentAction);
					cActionStand* pAction = new cActionStand;
					pAction->SetOwner(m_pOwner);
					pAction->SetDelegate(this);
					pAction->Start();
					m_pCurrentAction = pAction;
				}
			}
		}
		else
		{
			if (m_eCurrentAct != E_POSMOVE)
			{
				m_eCurrentAct = E_POSMOVE;
				SAFE_RELEASE(m_pCurrentAction);
				cActionMove* pAction = new cActionMove;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				pAction->SetWalkAnim(m_dwWalkAnim);
				pAction->SetDest(m_vOrgPos);
				pAction->SetInitDir(m_vOrgDir);
				pAction->Start();
				m_pCurrentAction = pAction;
			}
		}
	}
	

	if (m_eCurrentAct == E_TARGETMOVE)
		((cActionMove*)m_pCurrentAction)->SetDest(m_pTarget->GetPosition());
}

void cActionBossAi::DefenceAi()
{
	if (m_eCurrentAct != E_SKILL)
	{
		if (D3DXVec3Length(&(m_pOwner->GetPosition() - m_vOrgPos)) < 150.f)
		{
			if (D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) <= m_pOwner->GetAttackRange())
			{
				if (m_eCurrentAct != E_ATTACK)
				{
					m_eCurrentAct = E_ATTACK;
					SAFE_RELEASE(m_pCurrentAction);
					cActionAttack* pAction = new cActionAttack;
					pAction->SetOwner(m_pOwner);
					pAction->SetDelegate(this);
					pAction->SetAttackAnim(m_dwAttackAnim);
					pAction->Start();
					m_pCurrentAction = pAction;
				}
			}
			else
			{
				if (m_eCurrentAct != E_TARGETMOVE)
				{
					m_eCurrentAct = E_TARGETMOVE;
					SAFE_RELEASE(m_pCurrentAction);
					cActionMove* pAction = new cActionMove;
					pAction->SetOwner(m_pOwner);
					pAction->SetDelegate(this);
					pAction->SetDest(m_pTarget->GetPosition());
					pAction->SetWalkAnim(m_dwWalkAnim);
					pAction->Start();
					m_pCurrentAction = pAction;
				}
			}
		}
		else
		{
			m_isDefense = false;
			if (m_eCurrentAct != E_POSMOVE)
			{
				m_eCurrentAct = E_POSMOVE;
				SAFE_RELEASE(m_pCurrentAction);
				cActionMove* pAction = new cActionMove;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				pAction->SetWalkAnim(m_dwWalkAnim);
				pAction->SetDest(m_vOrgPos);
				pAction->SetInitDir(m_vOrgDir);
				pAction->Start();
				m_pCurrentAction = pAction;
			}
		}
	}

	if (m_eCurrentAct == E_TARGETMOVE)
		((cActionMove*)m_pCurrentAction)->SetDest(m_pTarget->GetPosition());
}

void cActionBossAi::OnUnitActionFinish(iUnitAction* pAction)
{
	if (m_eCurrentAct == E_POSMOVE)
	{
		m_isDefense = false;
		m_eCurrentAct = E_STAND;
		SAFE_RELEASE(m_pCurrentAction);
		cActionStand* pAction = new cActionStand;
		pAction->SetOwner(m_pOwner);
		pAction->SetDelegate(this);
		pAction->Start();
		m_pCurrentAction = pAction;
	}
	else
	{
		m_eCurrentAct = E_NONE;
		SAFE_RELEASE(m_pCurrentAction);
	}
}
