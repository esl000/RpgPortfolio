#include "stdafx.h"
#include "cActionBaseAi.h"
#include "cActionAttack.h"
#include "cActionMove.h"
#include "cActionStand.h"


cActionBaseAi::cActionBaseAi()
	: m_pCurrentAction(NULL)
	, m_pTarget(NULL)
	, m_vOrgPos(0, 0, 0)
	, m_vOrgDir(0, 0, 0)
	, m_dwWalkAnim(2)
	, m_dwAttackAnim(3)
	, m_eCurrentAct(E_STAND)
	, m_isDeffense(false)
{
}


cActionBaseAi::~cActionBaseAi()
{
	SAFE_RELEASE(m_pCurrentAction);
}

void cActionBaseAi::Start()
{
	cActionStand* pAction = new cActionStand;
	pAction->SetOwner(m_pOwner);
	pAction->SetDelegate(this);
	pAction->Start();
	m_pTarget = m_pOwner->GetTarget();
	m_pCurrentAction = pAction;
}

void cActionBaseAi::Update()
{
	if (m_isDeffense)
		DefenseAi();
	else
		BaseAi();

	if (m_pCurrentAction)
		m_pCurrentAction->Update();
}

void cActionBaseAi::BaseAi()
{
	if (D3DXVec3Length(&(m_pOwner->GetPosition() - m_vOrgPos)) < 150.f)
	{
		if (IsFocusSight(m_pOwner->GetPosition(), m_pTarget->GetPosition(), m_pOwner->GetDirection())
			&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < 10.f /*(m_pOwner->GetLevel() - m_pTarget->GetLevel())*/)
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

	if (m_eCurrentAct == E_TARGETMOVE)
		((cActionMove*)m_pCurrentAction)->SetDest(m_pTarget->GetPosition());

}

void cActionBaseAi::DefenseAi()
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
		m_isDeffense = false;
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

	if (m_eCurrentAct == E_TARGETMOVE)
		((cActionMove*)m_pCurrentAction)->SetDest(m_pTarget->GetPosition());
}

void cActionBaseAi::OnUnitActionFinish(iUnitAction* pAction)
{
	if (m_eCurrentAct == E_POSMOVE)
	{
		m_isDeffense = false;
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
