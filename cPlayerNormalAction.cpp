#include "stdafx.h"
#include "cPlayerNormalAction.h"
#include "cUnitPlayer.h"
#include "cPlayerActionStand.h"
#include "cPlayerActionFrontMove.h"
#include "cPlayerActionBackMove.h"



cPlayerNormalAction::cPlayerNormalAction()
	: m_pPlayer(NULL)
	, m_pCurrentAction(NULL)
	, m_dwWalkAnim(2)
	, m_vOrgPos(0, 0, 0)
	, m_pTarget(NULL)
	, m_eCurrentAction(E_NONE)
	, m_isAction(false)
{
}


cPlayerNormalAction::~cPlayerNormalAction()
{
	SAFE_RELEASE(m_pCurrentAction);
}

void cPlayerNormalAction::Start()
{
	if (m_pOwner)
	{
		m_eCurrentAction = E_STAND;
		cPlayerActionStand* pAction = new cPlayerActionStand;
		pAction->SetOwner(m_pOwner);
		pAction->SetDelegate(this);
		m_pCurrentAction = pAction;
		pAction->Start();
		m_pPlayer = (cUnitPlayer*)m_pOwner;
	}

}

void cPlayerNormalAction::Update()
{
	m_isAction = false;

	if (!m_pPlayer)
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}

	if (GetKeyState('A') & 0x8000)
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
	else if (GetKeyState('D') & 0x8000)
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


	if (GetKeyState('W') & 0x8000)
	{
		if (m_eCurrentAction != E_FRONTMOVE)
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
		m_isAction = true;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		if (m_eCurrentAction != E_BACKMOVE)
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
		m_isAction = true;
	}


	if (m_isAction == false || m_eCurrentAction == E_NONE)
	{
		if (m_eCurrentAction != E_STAND && m_eCurrentAction != E_POSMOVE)
		{
			m_eCurrentAction = E_STAND;
			SAFE_RELEASE(m_pCurrentAction);
			cPlayerActionStand* pAction = new cPlayerActionStand;
			pAction->SetOwner(m_pOwner);
			pAction->SetDelegate(this);
			m_pCurrentAction = pAction;
			pAction->Start();
			pAction->SetStandAnim(0);
		}
	}

	if (m_pCurrentAction)
		m_pCurrentAction->Update();


}

void cPlayerNormalAction::OnUnitActionFinish(iUnitAction* pAction)
{
	m_eCurrentAction = E_NONE;
	SAFE_RELEASE(m_pCurrentAction);
}

void cPlayerNormalAction::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}


//if (GetKeyState('T') & 0x8000)
//{
//	if (m_eCurrentAction != E_ATTACK)
//	{
//		for each(auto p in *g_pUnitManager->GetSetUnits())
//		{
//			if (IsFocusSight(m_pOwner->GetPosition(), p->GetPosition(), m_pOwner->GetDirection())
//				&& D3DXVec3Length(&(m_pOwner->GetPosition() - p->GetPosition())) < 10.f)
//			{
//				m_eCurrentAction = E_ATTACK;
//				SAFE_RELEASE(m_pCurrentAction);
//
//				cPlayerActionAttack* pAction = new cPlayerActionAttack;
//				m_pOwner->SetTarget(p);
//				pAction->SetOwner(m_pOwner);
//				pAction->SetDelegate(this);
//				pAction->SetAttackAnim(4);
//				m_pCurrentAction = pAction;
//				pAction->Start();
//				m_isAction = true;
//				break;
//			}
//		}
//	}
//}