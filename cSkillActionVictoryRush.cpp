#include "stdafx.h"
#include "cSkillActionVictoryRush.h"
#include "cEffectHit.h"
#include "cEffectFont.h"

cSkillActionVictoryRush::cSkillActionVictoryRush()
		: m_pOwnerMesh(NULL)
		, m_pTarget(NULL)
		, m_pEffect(NULL)
		, m_bIsHit(true)
		, m_dwVictoryRushAnim(0)
		, m_bSoundCheck(false)
{
}


cSkillActionVictoryRush::~cSkillActionVictoryRush()
{
}

void cSkillActionVictoryRush::Start()
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
		m_pEffect->SetFaceColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		m_pEffect->SetColorChangeTime(0.1f);
		m_pEffect->Setup();
		g_pEffectManager->RegisterEffect(m_pEffect);
	}
}

void cSkillActionVictoryRush::Update()
{
	// 전투 풀린후 20초안에 때리기 시간 체크가 필요함. 일단 몬스터 2마리 이상이여야 실험가능
	if (!m_pOwner || !m_pOwner->GetTarget() || !m_pTarget)
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}
	m_pTarget = m_pOwner->GetTarget();

	if (m_pOwner->GetAnimChange() && m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwVictoryRushAnim)
		m_pOwnerMesh->SetAnimationIndex(m_dwVictoryRushAnim);

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
			//cout << "승격!!!" << endl;
			m_pTarget->Damage(m_pOwner->GetCurrentDamage());
			// 캐스팅 시전 방해 기술인데... 캐스팅 스킬이 아직없어서, 데미지와 애니메이션 수정해야됨
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
			pFont->SetDamage(m_pOwner->GetCurrentDamage());
			pFont->SetFontState(cEffectFont::E_SKILL);
			pFont->Setup();
			g_pEffectManager->RegisterEffect(pFont);
		}
	}

	if (dPos / dPeriod > 0.95f)
	{
		if (!m_bIsHit)
		{
			m_bSoundCheck = false;
			m_pDelegate->OnUnitActionFinish(this);
			return;
		}
	}
}
