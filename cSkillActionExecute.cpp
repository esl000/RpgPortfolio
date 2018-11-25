#include "stdafx.h"
#include "cSkillActionExecute.h"
#include "cEffectHit.h"
#include "cEffectFont.h"

cSkillActionExecute::cSkillActionExecute()
		:m_pOwnerMesh(NULL)
		, m_pTarget(NULL)
		, m_pEffect(NULL)
		, m_ExecuteAnim(0)
		, m_bIsHit(true)
		, m_bSoundCheck(false)
{
}


cSkillActionExecute::~cSkillActionExecute()
{
}

void cSkillActionExecute::Start()
{
	if (m_pOwner)
	{
		m_pOwnerMesh = m_pOwner->GetMesh();
		m_pTarget = m_pOwner->GetTarget();

		m_pEffect = new cEffectSword;
		m_pEffect->SetOwnerMesh(m_pOwnerMesh);
		m_pEffect->SetMaxTime(1.0f);

		m_pEffect->SetPosition(m_pOwner->GetPosition());
		m_pEffect->SetDirection(m_pOwner->GetDirection());
		m_pEffect->SetFaceColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_pEffect->SetColorChangeTime(0.1f);
		m_pEffect->Setup();
		g_pEffectManager->RegisterEffect(m_pEffect);
	}
}

void cSkillActionExecute::Update()
{
	if (!m_pOwner || !m_pOwner->GetTarget() || !m_pTarget)
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}
	m_pTarget = m_pOwner->GetTarget();

	if (m_pOwner->GetAnimChange() && m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_ExecuteAnim)
		m_pOwnerMesh->SetAnimationIndex(m_ExecuteAnim);

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
		D3DXVECTOR3 vPos = m_pOwner->GetPosition() + m_pOwner->GetCurrentSpeed() * g_pTimeManager->GetElapsedTime() * m_pOwner->GetDirection();
		D3DXVECTOR3 vDest;

		ST_SPHERE stSphere(vPos, m_pOwner->GetFrustumSphere().fRadius);

		if (g_pIntersectManager->IntersectEntitys(stSphere))
			return;

		if (g_pIntersectManager->IntersectInBuilding(m_pOwner->GetFrustumSphere(), vPos, vDest))
		{
			vPos = vDest;
		}

		//g_pTileManager->GetHeight(vDest, vPos.x, vPos.z);
		m_pOwner->SetPosition(vPos);
	}
	else if (GetKeyState('S') & 0x8000)
	{
		D3DXVECTOR3 vPos = m_pOwner->GetPosition() - (m_pOwner->GetCurrentSpeed() * 0.5f) * g_pTimeManager->GetElapsedTime() * m_pOwner->GetDirection();
		D3DXVECTOR3 vDest;

		ST_SPHERE stSphere(vPos, m_pOwner->GetFrustumSphere().fRadius);

		if (g_pIntersectManager->IntersectEntitys(stSphere))
			return;

		if (g_pIntersectManager->IntersectInBuilding(m_pOwner->GetFrustumSphere(), vPos, vDest))
		{
			vPos = vDest;
		}

		//g_pTileManager->GetHeight(vDest, vPos.x, vPos.z);
		m_pOwner->SetPosition(vPos);
	}

	double dPos, dPeriod;
	dPos = m_pOwnerMesh->GetAnimPosition();
	dPeriod = m_pOwnerMesh->GetAnimPeriod();
	dPos = dPos - dPeriod * (int)(dPos / dPeriod);

	if (!m_bSoundCheck)
	{
		g_pSoundManager->play("OrcWeaponSwings", 1.0f);
		g_pSoundManager->play("OrcTargetHit", 1.0f);
		g_pSoundManager->play("RendTarget", 1.0f);
		m_bSoundCheck = true;
	}

	m_pEffect->SetPosition(m_pOwner->GetPosition());
	m_pEffect->SetDirection(m_pOwner->GetDirection());

	if (dPos / dPeriod > 0.6f)
	{
		if (m_bIsHit)
		{
			//cout << "¸·Å¸!!!" << endl;
			m_pTarget->Damage(m_pOwner->GetCurrentDamage() * 3.f);
			m_bIsHit = false;

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
			pFont->SetDamage(m_pOwner->GetCurrentDamage() * 3.f);
			pFont->SetFontState(cEffectFont::E_SKILL);
			pFont->Setup();
			g_pEffectManager->RegisterEffect(pFont);
		}
	}
	
	if (dPos / dPeriod > 0.95f)
	{
		if (!m_bIsHit)
		{
			m_bSoundCheck = true;
			m_pDelegate->OnUnitActionFinish(this);
			return;
		}
	}

}
