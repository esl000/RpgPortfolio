#include "stdafx.h"
#include "cPlayerBattleAction.h"
#include "cUnitPlayer.h"
#include "cPlayerActionStand.h"
#include "cPlayerActionFrontMove.h"
#include "cPlayerActionBackMove.h"
#include "cPlayerActionAttack.h"
#include "cSkillActionCharge.h"
#include "cSkillActionBladeStorm.h"
#include "cSkillActionExecute.h"
#include "cSkillActionHamstring.h"
#include "cSkillActionMortalStrike.h"
#include "cSkillActionPummel.h"
#include "cSkillActionThunderClap.h"
#include "cSkillActionVictoryRush.h"
#include "cSkillActionWhirlWind.h"
#include "cSkillInven.h"
#include "cSkillAd.h"

cPlayerBattleAction::cPlayerBattleAction()
	: m_pCurrentAction(NULL)
	, m_eCurrentAction(E_STAND)
	, m_pTarget(NULL)
	, m_pPlayer(NULL)
{
	for (int i = 0; i < 12; i++)
	{
		m_bSkillOn[i] = true;
		m_nCoolTime[i] = 100;
	}
}


cPlayerBattleAction::~cPlayerBattleAction()
{
	SAFE_RELEASE(m_pCurrentAction);
}

void cPlayerBattleAction::Start()
{
	if (m_pOwner)
	{
		m_pPlayer = (cUnitPlayer*)m_pOwner;
		m_pTarget = m_pOwner->GetTarget();

		m_eCurrentAction = E_STAND;
		cPlayerActionStand* pAction = new cPlayerActionStand;
		pAction->SetOwner(m_pOwner);
		pAction->SetDelegate(this);
		pAction->SetStandAnim(105);
		m_pCurrentAction = pAction;
		pAction->Start();
	}
}

void cPlayerBattleAction::Update()
{
	bool isTargetAlive = false;
	for each(auto p in *g_pUnitManager->GetSetUnits())
	{
		if (p == m_pTarget)
		{
			isTargetAlive = true;
			break;
		}
	}

	if (!isTargetAlive)
	{
		m_pPlayer->SetTarget(NULL);
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}

	for (int i = 0; i < 12; ++i)
	{
		if (!m_bSkillOn[i])
		{
			if (m_nCoolTime[i] > 0)
			{
				m_nCoolTime[i]--;
			}			
			else
			{
				m_nCoolTime[i] = 100;
				m_bSkillOn[i] = true;
			}
		}
		else
			continue;
	}

	if (!m_pPlayer)
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}

	m_pTarget = m_pPlayer->GetTarget();

	if (m_pTarget && IsFocusSight(m_pOwner->GetPosition(), m_pTarget->GetPosition(), m_pOwner->GetDirection())
		&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < m_pOwner->GetAttackRange()
		&& m_eCurrentAction != E_SKILL && m_eCurrentAction != E_POSMOVE)
	{
		if (m_eCurrentAction != E_ATTACK)
		{
			m_eCurrentAction = E_ATTACK;
			SAFE_RELEASE(m_pCurrentAction);
			cPlayerActionAttack* pAction = new cPlayerActionAttack;
			pAction->SetOwner(m_pOwner);
			pAction->SetDelegate(this);
			m_pCurrentAction = pAction;
			pAction->Start();
			pAction->SetAttackAnim(4);
		}
	}

	if (m_pTarget)
	{
		if (GetKeyState(m_pPlayer->GetSkillInven()->GetSkill(cSkillAd::E_SKILL1)->GetKey()) & 0x8000 && m_bSkillOn[0]
			&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) > 10.0f
			&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < 25.0f)
		{
			m_bSkillOn[0] = false;
			if (m_eCurrentAction != E_SKILL)
			{
				m_eCurrentAction = E_SKILL;
				SAFE_RELEASE(m_pCurrentAction);
				cSkillActionCharge* pAction = new cSkillActionCharge;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				m_pCurrentAction = pAction;
				pAction->Start();
				pAction->SetRushAnim(2);
				if (m_pPlayer->GetCurrentMp() < 86)			
					m_pPlayer->SetCurrentMp(m_pPlayer->GetCurrentMp() + 15.0f);				
				else
					m_pPlayer->SetCurrentMp(m_pPlayer->GetCurrentMp() + (100 - m_pPlayer->GetCurrentMp()));
			}
		}
		else if (GetKeyState(m_pPlayer->GetSkillInven()->GetSkill(cSkillAd::E_SKILL2)->GetKey()) & 0x8000 && m_bSkillOn[1] && m_pPlayer->GetCurrentMp() > 25.0f)
		{
			m_bSkillOn[1] = false;
			if (m_eCurrentAction != E_SKILL)
			{
				m_eCurrentAction = E_SKILL;
				SAFE_RELEASE(m_pCurrentAction);
				cSkillActionBladeStorm* pAction = new cSkillActionBladeStorm;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				m_pCurrentAction = pAction;
				pAction->Start();
				pAction->SetStormAnim(120);
				m_pPlayer->SetCurrentMp(m_pPlayer->GetCurrentMp() - 25.0f);
			}
		}
		else if (GetKeyState(m_pPlayer->GetSkillInven()->GetSkill(cSkillAd::E_SKILL3)->GetKey()) & 0x8000 && m_bSkillOn[2]
			&& m_pTarget->GetCurrentHp() / m_pTarget->GetMaxHp() < 0.25f
			&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < m_pPlayer->GetAttackRange()
			&& m_pPlayer->GetCurrentMp() > 15.0f)
		{
			m_bSkillOn[2] = false;
			if (m_eCurrentAction != E_SKILL)
			{
				m_eCurrentAction = E_SKILL;
				SAFE_RELEASE(m_pCurrentAction);
				cSkillActionExecute* pAction = new cSkillActionExecute;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				m_pCurrentAction = pAction;
				pAction->Start();
				pAction->SetExecutAnim(40);
				m_pPlayer->SetCurrentMp(m_pPlayer->GetCurrentMp() - 15.0f);
			}
		}
		else if (GetKeyState(m_pPlayer->GetSkillInven()->GetSkill(cSkillAd::E_SKILL4)->GetKey()) & 0x8000 && m_bSkillOn[3]
			&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < m_pPlayer->GetAttackRange()
			&& m_pPlayer->GetCurrentMp() > 10.0f)
		{
			m_bSkillOn[3] = false;
			if (m_eCurrentAction != E_SKILL)
			{
				m_eCurrentAction = E_SKILL;
				SAFE_RELEASE(m_pCurrentAction);
				cSkillActionHamstring* pAction = new cSkillActionHamstring;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				m_pCurrentAction = pAction;
				pAction->Start();
				pAction->SetHamstringAnim(40);
				m_pPlayer->SetCurrentMp(m_pPlayer->GetCurrentMp() - 10.0f);
			}
		}
		else if (GetKeyState(m_pPlayer->GetSkillInven()->GetSkill(cSkillAd::E_SKILL5)->GetKey()) & 0x8000 && m_bSkillOn[4]
			&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < m_pPlayer->GetAttackRange()
			&& m_pPlayer->GetCurrentMp() > 30.0f)
		{
			m_bSkillOn[4] = false;
			if (m_eCurrentAction != E_SKILL)
			{
				m_eCurrentAction = E_SKILL;
				SAFE_RELEASE(m_pCurrentAction);
				cSkillActionMortalStrike* pAction = new cSkillActionMortalStrike;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				m_pCurrentAction = pAction;
				pAction->Start();
				pAction->SetMortalStrikeAnim(40);
				m_pPlayer->SetCurrentMp(m_pPlayer->GetCurrentMp() - 30.0f);
			}
		}
		else if (GetKeyState(m_pPlayer->GetSkillInven()->GetSkill(cSkillAd::E_SKILL6)->GetKey()) & 0x8000 && m_bSkillOn[5]
			&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < m_pPlayer->GetAttackRange()
			&& m_pPlayer->GetCurrentMp() > 10.0f)
		{
			m_bSkillOn[5] = false;
			if (m_eCurrentAction != E_SKILL)
			{
				m_eCurrentAction = E_SKILL;
				SAFE_RELEASE(m_pCurrentAction);
				cSkillActionPummel* pAction = new cSkillActionPummel;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				m_pCurrentAction = pAction;
				pAction->Start();
				pAction->SetPummelAnim(18);
				m_pPlayer->SetCurrentMp(m_pPlayer->GetCurrentMp() - 10.0f);
			}
		}
		else if (GetKeyState(m_pPlayer->GetSkillInven()->GetSkill(cSkillAd::E_SKILL7)->GetKey()) & 0x8000 && m_bSkillOn[6]
			&& m_pPlayer->GetCurrentMp() > 20.0f)
		{
			m_bSkillOn[6] = false;
			if (m_eCurrentAction != E_SKILL)
			{
				m_eCurrentAction = E_SKILL;
				SAFE_RELEASE(m_pCurrentAction);
				cSkillActionThunderClap* pAction = new cSkillActionThunderClap;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				m_pCurrentAction = pAction;
				pAction->Start();
				pAction->SetThunderClapAnim(135);
				m_pPlayer->SetCurrentMp(m_pPlayer->GetCurrentMp() - 20.0f);
			}
		}
		else if (GetKeyState(m_pPlayer->GetSkillInven()->GetSkill(cSkillAd::E_SKILL8)->GetKey()) & 0x8000 && m_bSkillOn[7]
			&& D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < m_pPlayer->GetAttackRange()
			&& m_pPlayer->GetCurrentMp() > 10.0f)
		{
			m_bSkillOn[7] = false;
			if (m_eCurrentAction != E_SKILL)
			{
				m_eCurrentAction = E_SKILL;
				SAFE_RELEASE(m_pCurrentAction);
				cSkillActionVictoryRush* pAction = new cSkillActionVictoryRush;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				m_pCurrentAction = pAction;
				pAction->Start();
				pAction->SetVictoryRushAnim(40);
				m_pPlayer->SetCurrentMp(m_pPlayer->GetCurrentMp() - 10.0f);
			}
		}
		else if (GetKeyState(m_pPlayer->GetSkillInven()->GetSkill(cSkillAd::E_SKILL9)->GetKey()) & 0x8000 && m_bSkillOn[8]
			&& m_pPlayer->GetCurrentMp() > 25.0f)
		{
			m_bSkillOn[8] = false;
			if (m_eCurrentAction != E_SKILL)
			{
				m_eCurrentAction = E_SKILL;
				SAFE_RELEASE(m_pCurrentAction);
				cSkillActionWhirlWind* pAction = new cSkillActionWhirlWind;
				pAction->SetOwner(m_pOwner);
				pAction->SetDelegate(this);
				m_pCurrentAction = pAction;
				pAction->Start();
				pAction->SetWhirlWindAnim(120);
				m_pPlayer->SetCurrentMp(m_pPlayer->GetCurrentMp() - 25.0f);
			}
		}
	}

	if (GetKeyState('A') & 0x8000)
	{
		if (m_eCurrentAction != E_SKILL)
		{
			float fAngle = atan2f(m_pOwner->GetDirection().x, m_pOwner->GetDirection().z) - D3DX_PI;
			fAngle -= 0.1f;
			D3DXMATRIXA16 matR, matT;
			D3DXMatrixRotationY(&matR, fAngle);

			D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
			D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
			D3DXVec3Normalize(&vDirection, &vDirection);
			m_pOwner->SetDirection(vDirection);
		}
	}
	else if (GetKeyState('D') & 0x8000)
	{
		if (m_eCurrentAction != E_SKILL)
		{
			float fAngle = atan2f(m_pOwner->GetDirection().x, m_pOwner->GetDirection().z) - D3DX_PI;
			fAngle += 0.1f;
			D3DXMATRIXA16 matR, matT;
			D3DXMatrixRotationY(&matR, fAngle);

			D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
			D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
			D3DXVec3Normalize(&vDirection, &vDirection);
			m_pOwner->SetDirection(vDirection);
		}
	}


	if (GetKeyState('W') & 0x8000)
	{
		if (m_eCurrentAction != E_FRONTMOVE && m_eCurrentAction != E_SKILL)
		{
			m_eCurrentAction = E_FRONTMOVE;
			SAFE_RELEASE(m_pCurrentAction);
			cPlayerActionFrontMove* pAction = new cPlayerActionFrontMove;
			pAction->SetOwner(m_pOwner);
			pAction->SetDelegate(this);
			pAction->SetWalkAnim(2);
			m_pCurrentAction = pAction;
			pAction->Start();
		}
	}
	else if (GetKeyState('S') & 0x8000)
	{
		if (m_eCurrentAction != E_BACKMOVE && m_eCurrentAction != E_SKILL)
		{
			m_eCurrentAction = E_BACKMOVE;
			SAFE_RELEASE(m_pCurrentAction);
			cPlayerActionBackMove* pAction = new cPlayerActionBackMove;
			pAction->SetOwner(m_pOwner);
			pAction->SetDelegate(this);
			pAction->SetWalkAnim(16);
			m_pCurrentAction = pAction;
			pAction->Start();
		}
	}
	else
	{
		if (m_eCurrentAction == E_FRONTMOVE || m_eCurrentAction == E_BACKMOVE)
		{
			m_eCurrentAction = E_NONE;
			SAFE_RELEASE(m_pCurrentAction);
		}
	}

	if (!m_pCurrentAction)
		m_eCurrentAction = E_NONE;


	if (m_eCurrentAction == E_NONE)
	{
		m_eCurrentAction = E_STAND;
		SAFE_RELEASE(m_pCurrentAction);
		cPlayerActionStand* pAction = new cPlayerActionStand;
		pAction->SetOwner(m_pOwner);
		pAction->SetDelegate(this);
		m_pCurrentAction = pAction;
		pAction->Start();
		pAction->SetStandAnim(105);
	}

	if (m_pCurrentAction)
		m_pCurrentAction->Update();
}

void cPlayerBattleAction::OnUnitActionFinish(iUnitAction* pAction)
{
	m_eCurrentAction = E_NONE;
	SAFE_RELEASE(m_pCurrentAction);
}

void cPlayerBattleAction::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_TAB:
			for each(auto p in *g_pUnitManager->GetSetUnits())
			{
				if (p->GetUnitType() == cUnit::E_MONSTER)
				{
					if (p != m_pPlayer->GetTarget())
					{
						if (IsFocusSight(m_pOwner->GetPosition(), p->GetPosition(), m_pOwner->GetDirection())
							&& D3DXVec3Length(&(m_pOwner->GetPosition() - p->GetPosition())) < 10.f)
						{
							m_pPlayer->SetTarget(p);
							m_pTarget = p;
							break;
						}
					}
				}
			}
			break;
		}
		break;
	}
}
