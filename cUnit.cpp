#include "stdafx.h"
#include "cUnit.h"


cUnit::cUnit()
	: m_pUnitAction(NULL)
	, m_pUnitDelegate(NULL)
	, m_pTarget(NULL)
	, m_pKiller(NULL)
	, m_pMesh(NULL)
	, m_pBuff(NULL)
	, m_fMaxHp(0)
	, m_fMaxMp(0)
	, m_fCurrentHp(0)
	, m_fCurrentMp(0)
	, m_fAttackRange(0)
	, m_fCurrentDamage(0)
	, m_fOrigDamage(0)
	, m_fCurrentSpeed(0)
	, m_fOrigSpeed(0)
	, m_fCurrentDefence(0)
	, m_fOrigDefence(0)	
	, m_sName("")
	, m_dwLevel(0)
	, m_fGravityPower(0)
	, m_fGravitySpeed(0)
	, m_eGravityState(E_NONE)
	, m_dwJumpAnim(0)
	, m_dwFallAnim(0)
	, m_dwFallEndAnim(0)
	, m_isAnimChange(true)	
{
	m_vDirection = D3DXVECTOR3(0, 0, -1);
}


cUnit::~cUnit()
{
	SAFE_DELETE(m_pMesh);
	SAFE_RELEASE(m_pBuff);
	SAFE_RELEASE(m_pUnitAction);
	SAFE_RELEASE(m_pSphereMesh);
}

void cUnit::Update()
{
	if (m_pBuff)
		m_pBuff->Update();
	if (m_pUnitAction)
		m_pUnitAction->Update();


	Gravity();

	if (m_pMesh)
	{
		m_pMesh->SetPosition(m_vPosition);
		m_pMesh->SetDirection(m_vDirection);
		m_stFrustumSphere = m_pMesh->GetBoundingSphere();
	}
}

void cUnit::Damage(float fDamage)
{
	if (m_fCurrentHp < fDamage)
	{
		Die();
		m_pUnitDelegate->onUnitDelete(this);
		return;
	}
	else
	{
		m_fCurrentHp = m_fCurrentHp - (fDamage - (fDamage / m_fCurrentDefence));
	}
		
}

void cUnit::Jump()
{
	if (m_eGravityState == E_NONE)
	{
		m_eGravityState = E_JUMPSTART;
		m_fGravitySpeed = 0;
		m_fGravityPower = 0.8;
		m_pMesh->SetAnimationIndex(m_dwJumpAnim);
	}
}

void cUnit::Gravity()
{
	if (m_eGravityState == E_NONE || m_eGravityState == E_FALLEND)
	{
		D3DXVECTOR3 vDest;
		if (g_pTileManager->GetHeight(vDest, m_vPosition))
		{
			if (vDest.y + 3 < m_vPosition.y)
			{
				m_pMesh->SetAnimationIndex(m_dwFallAnim);
				m_eGravityState = E_FALL;
				m_fGravityPower = 0;
				m_fGravitySpeed = 0;
			}
			else
				m_vPosition = vDest;
		}
	}
	double dPos, dPeriod;
	dPos = m_pMesh->GetAnimPosition();
	dPeriod = m_pMesh->GetAnimPeriod();
	dPos = dPos - dPeriod * (int)(dPos / dPeriod);

	if (m_eGravityState == E_JUMPSTART)
	{
		if (dPos / dPeriod > 0.9f)
		{
			m_pMesh->SetAnimationIndex(m_dwFallAnim);
			m_eGravityState = E_FALL;
		}
	}

	if (m_eGravityState == E_FALLEND)
	{
		if (dPos / dPeriod > 0.45f)
		{
			m_pMesh->SetAnimationIndex(0);
			m_eGravityState = E_NONE;
		}
	}

	if (m_eGravityState > 0 && m_eGravityState < 4)
	{
		m_fGravityPower -=  3 * g_pTimeManager->GetElapsedTime();
		m_fGravitySpeed = m_fGravityPower;
		m_vPosition.y += m_fGravitySpeed;
		D3DXVECTOR3 vDest;
		if (g_pTileManager->GetHeight(vDest, m_vPosition))
		{
			if (vDest.y + 0.01f > m_vPosition.y)
			{
				m_eGravityState = E_FALLEND;
				m_fGravityPower = 0;
				m_fGravitySpeed = 0;
				m_vPosition = vDest;
				m_pMesh->SetAnimationIndex(m_dwFallEndAnim);
			}
		}
	}
}

void cUnit::Die()
{

}




void cUnit::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pUnitAction)
		m_pUnitAction->WndProc(hWnd, message, wParam, lParam);
}
