#include "stdafx.h"
#include "cPlayerAction.h"
#include "cUnitPlayer.h"
#include "cPlayerNormalAction.h"
#include "cPlayerBattleAction.h"
#include "cUnitCustomNpc.h"
#include "cPlayerActionPosMove.h"



cPlayerAction::cPlayerAction()
	: m_pPlayer(NULL)
	, m_pCurrentAction(NULL)
	, m_eCurrentAction(E_NORMAL)
	, m_isClick(false)
{
}


cPlayerAction::~cPlayerAction()
{
	SAFE_RELEASE(m_pCurrentAction);
}

void cPlayerAction::Start()
{
	if (m_pOwner)
	{
		cPlayerNormalAction* pAction = new cPlayerNormalAction;
		pAction->SetOwner(m_pOwner);
		pAction->SetDelegate(this);
		m_pCurrentAction = pAction;
		pAction->Start();
		m_pPlayer = (cUnitPlayer*)m_pOwner;
	}

}

void cPlayerAction::Update()
{
	if (!m_pPlayer)
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}

	Picking();

	if (GetKeyState('T') & 0x8000)
	{
		if (m_eCurrentAction != E_BATTLE)
		{
			for each(auto p in *g_pUnitManager->GetSetUnits())
			{
				if (p->GetUnitType() == cUnit::E_MONSTER)
				{
					if (IsFocusSight(m_pOwner->GetPosition(), p->GetPosition(), m_pOwner->GetDirection())
						&& D3DXVec3Length(&(m_pOwner->GetPosition() - p->GetPosition())) < 15.f)
					{
						m_eCurrentAction = E_BATTLE;
						cPlayerBattleAction* pAction = new cPlayerBattleAction;
						pAction->SetOwner(m_pOwner);
						pAction->SetDelegate(this);
						m_pPlayer->SetTarget(p);
						m_pCurrentAction = pAction;
						pAction->Start();
						break;
					}
				}
			}
		}
	}

	if (m_pPlayer->GetTarget())
	{
		if (m_pPlayer->GetTarget()->GetName() == "µ¥½ºÀ®")
			m_pPlayer->SetAttackRange(10.0f);
		else
			m_pPlayer->SetAttackRange(3.4f);
	}	

	if (!m_pCurrentAction && m_eCurrentAction == E_BATTLE)
	{
		m_eCurrentAction = E_NORMAL;
		cPlayerNormalAction* pAction = new cPlayerNormalAction;
		pAction->SetOwner(m_pOwner);
		pAction->SetDelegate(this);
		m_pCurrentAction = pAction;
		pAction->Start();
	}

	if (m_pCurrentAction)
		m_pCurrentAction->Update();
}

void cPlayerAction::Picking()
{
	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		if (!m_isClick)
		{
			if (!g_pPicking->GetUse(cPicking::E_RIGHCLICK))
				return;

			cUnit* pTarget = NULL;
			D3DXVECTOR3 vDest;

			if (g_pPicking->PickingObjects(vDest, &pTarget, cPicking::E_LEFTCLICK))
			{
				if (pTarget != NULL)
				{
					if (pTarget->GetUnitType() == cUnit::E_NPC)
					{
						cUnitCustomNpc* pNpc = (cUnitCustomNpc*)pTarget;
						pNpc->OpenMessage();
						return;
					}
					else if (pTarget->GetUnitType() == cUnit::E_MONSTER)
					{
						if (m_eCurrentAction == E_BATTLE)
						{
							m_pOwner->SetTarget(pTarget);
							cPlayerBattleAction* pAction = (cPlayerBattleAction*)m_pCurrentAction;

							cPlayerActionPosMove* pAct = new cPlayerActionPosMove;
							pAct->SetOwner(m_pOwner);
							pAct->SetDelegate(pAction);
							pAct->SetWalkAnim(2);
							pAct->SetDest(vDest);

							iUnitAction* pTemp = pAction->GetCurrentAction();
							SAFE_RELEASE(pTemp);

							pAction->SetCurrentAction(pAct);
							pAction->SetCurrentActionType(cPlayerBattleAction::E_POSMOVE);
							pAct->Start();
						}
						else if (m_eCurrentAction == E_NORMAL)
						{
							m_eCurrentAction = E_BATTLE;
							SAFE_RELEASE(m_pCurrentAction);
							cPlayerBattleAction* pAction = new cPlayerBattleAction;
							pAction->SetOwner(m_pOwner);
							pAction->SetDelegate(this);
							m_pPlayer->SetTarget(pTarget);
							m_pCurrentAction = pAction;
							pAction->Start();

							cPlayerActionPosMove* pAct = new cPlayerActionPosMove;
							pAct->SetOwner(m_pOwner);
							pAct->SetDelegate(pAction);
							pAct->SetWalkAnim(2);
							pAct->SetDest(vDest);

							iUnitAction* pTemp = pAction->GetCurrentAction();
							SAFE_RELEASE(pTemp);

							pAction->SetCurrentAction(pAct);
							pAction->SetCurrentActionType(cPlayerBattleAction::E_POSMOVE);
							pAct->Start();

							return;
						}
					}
					else
					{
						if (m_eCurrentAction == E_BATTLE)
						{
							cPlayerBattleAction* pAction = (cPlayerBattleAction*)m_pCurrentAction;

							cPlayerActionPosMove* pAct = new cPlayerActionPosMove;
							pAct->SetOwner(m_pOwner);
							pAct->SetDelegate(pAction);
							pAct->SetWalkAnim(2);
							pAct->SetDest(vDest);

							iUnitAction* pTemp = pAction->GetCurrentAction();
							SAFE_RELEASE(pTemp);

							pAction->SetCurrentAction(pAct);
							pAction->SetCurrentActionType(cPlayerBattleAction::E_POSMOVE);
							pAct->Start();
						}
						else if (m_eCurrentAction == E_NORMAL)
						{
							cPlayerNormalAction* pAction = (cPlayerNormalAction*)m_pCurrentAction;

							cPlayerActionPosMove* pAct = new cPlayerActionPosMove;
							pAct->SetOwner(m_pOwner);
							pAct->SetDelegate(pAction);
							pAct->SetWalkAnim(2);
							pAct->SetDest(vDest);

							iUnitAction* pTemp = pAction->GetCurrentAction();
							SAFE_RELEASE(pTemp);

							pAction->SetCurrentAction(pAct);
							pAction->SetCurrentActionType(cPlayerNormalAction::E_POSMOVE);
							pAct->Start();
						}
					}
				}
				else
				{
					if (m_eCurrentAction == E_BATTLE)
					{
						cPlayerBattleAction* pAction = (cPlayerBattleAction*)m_pCurrentAction;

						cPlayerActionPosMove* pAct = new cPlayerActionPosMove;
						pAct->SetOwner(m_pOwner);
						pAct->SetDelegate(pAction);
						pAct->SetWalkAnim(2);
						pAct->SetDest(vDest);

						iUnitAction* pTemp = pAction->GetCurrentAction();
						SAFE_RELEASE(pTemp);

						pAction->SetCurrentAction(pAct);
						pAction->SetCurrentActionType(cPlayerBattleAction::E_POSMOVE);
						pAct->Start();
					}
					else if (m_eCurrentAction == E_NORMAL)
					{
						cPlayerNormalAction* pAction = (cPlayerNormalAction*)m_pCurrentAction;

						cPlayerActionPosMove* pAct = new cPlayerActionPosMove;
						pAct->SetOwner(m_pOwner);
						pAct->SetDelegate(pAction);
						pAct->SetWalkAnim(2);
						pAct->SetDest(vDest);

						iUnitAction* pTemp = pAction->GetCurrentAction();
						SAFE_RELEASE(pTemp);

						pAction->SetCurrentAction(pAct);
						pAction->SetCurrentActionType(cPlayerNormalAction::E_POSMOVE);
						pAct->Start();
					}
				}
			}


			
		}
		m_isClick = true;
	}
	else
	{
		m_isClick = false;
	}
}

void cPlayerAction::OnUnitActionFinish(iUnitAction* pAction)
{
	SAFE_RELEASE(m_pCurrentAction);
}

void cPlayerAction::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrentAction)
		m_pCurrentAction->WndProc(hWnd, message, wParam, lParam);

}
