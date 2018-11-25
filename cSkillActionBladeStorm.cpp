#include "stdafx.h"
#include "cSkillActionBladeStorm.h"
#include "cEffectHit.h"
#include "cEffectFont.h"

cSkillActionBladeStorm::cSkillActionBladeStorm()
		: m_pOwnerMesh(NULL)
		, m_pTarget(NULL)
		, m_pEffect(NULL)
		, m_dwStormAnim(0)
		, m_fTwirlCount(0)
		, m_bIsHit(false)
		, m_vDir(0, 0, -1)
		, m_bSkillSound(false)
{
}


cSkillActionBladeStorm::~cSkillActionBladeStorm()
{
	m_pOwnerMesh->SetReverse(false, 0, 0);
}

void cSkillActionBladeStorm::Start()
{
	if (m_pOwner)
	{
		m_pOwnerMesh = m_pOwner->GetMesh();
		m_pTarget = m_pOwner->GetTarget();
		m_vDir = m_pOwner->GetDirection();

		m_pEffect = new cEffectSword;
		m_pEffect->SetOwnerMesh(m_pOwnerMesh);
		m_pEffect->SetMaxTime(5.0f);
				
		m_pEffect->SetPosition(m_pOwner->GetPosition());
		m_pEffect->SetDirection(m_pOwner->GetDirection());
		m_pEffect->SetFaceColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_pEffect->SetColorChangeTime(0.1f);
		m_pEffect->Setup();
		g_pEffectManager->RegisterEffect(m_pEffect);
	}
}

void cSkillActionBladeStorm::Update()
{
	m_fTwirlCount += g_pTimeManager->GetElapsedTime();

	if (m_pOwner->GetAnimChange() && m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwStormAnim)
	{
		m_pOwnerMesh->SetAnimationIndex(m_dwStormAnim);
		m_pOwnerMesh->SetReverse(true, 0.05, 0.55);
	}

	if (GetKeyState('A') & 0x8000)
	{
		float fAngle = atan2f(m_vDir.x, m_vDir.z) - D3DX_PI;
		fAngle -= 0.1f;
		D3DXMATRIXA16 matR, matT;
		D3DXMatrixRotationY(&matR, fAngle);

		D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
		D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
		D3DXVec3Normalize(&vDirection, &vDirection);
		m_vDir = vDirection;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		float fAngle = atan2f(m_vDir.x, m_vDir.z) - D3DX_PI;
		fAngle += 0.1f;
		D3DXMATRIXA16 matR, matT;
		D3DXMatrixRotationY(&matR, fAngle);

		D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
		D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
		D3DXVec3Normalize(&vDirection, &vDirection);
		m_vDir = vDirection;
	}

	if (GetKeyState('W') & 0x8000)
	{
		D3DXVECTOR3 vPos = m_pOwner->GetPosition() + m_pOwner->GetCurrentSpeed() * g_pTimeManager->GetElapsedTime() * m_vDir;
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
		D3DXVECTOR3 vPos = m_pOwner->GetPosition() - (m_pOwner->GetCurrentSpeed() * 0.5f) * g_pTimeManager->GetElapsedTime() * m_vDir;
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

	if (!m_bSkillSound)
	{
		g_pSoundManager->play("BladeStorm", 1.0f);
		m_bSkillSound = true;
	}

	m_pEffect->SetPosition(m_pOwner->GetPosition());
	m_pEffect->SetDirection(m_pOwner->GetDirection());

	vector<cUnit*> vecDamage;

	if (dPos / dPeriod > 0.6f)
	{		
		if (!m_bIsHit)
		{
			for each(auto p in *g_pUnitManager->GetSetUnits())
			{
				if (p->GetUnitType() == cUnit::E_MONSTER)
				{
					if (p->GetName() != "데스윙" && 
						D3DXVec3Length(&(m_pOwner->GetPosition() - p->GetPosition())) < 5.0f)
					{
						vecDamage.push_back(p);
					}
					else if (p->GetName() == "데스윙" &&
						D3DXVec3Length(&(m_pOwner->GetPosition() - p->GetPosition())) < 10.0f)
					{
						vecDamage.push_back(p);
					}
				}
			}
			m_bIsHit = true;
		}			
	}

	while (vecDamage.size() != 0)
	{
		cEffectHit* pEffect = new cEffectHit;
		pEffect->SetPosition(m_pTarget->GetPosition());
		pEffect->SetDirection(m_pTarget->GetDirection());
		pEffect->SetEffectUnit(m_pTarget);
		pEffect->SetMaxTime(0.2f);
		pEffect->Setup();
		g_pEffectManager->RegisterEffect(pEffect);

		cEffectFont* pFont = new cEffectFont;
		pFont->SetPosition(vecDamage.back()->GetPosition());
		pFont->SetDirection(vecDamage.back()->GetDirection());
		pFont->SetEffectUnit(vecDamage.back());
		pFont->SetDamage(m_pOwner->GetCurrentDamage() * 2.f);
		pFont->SetFontState(cEffectFont::E_SKILL);
		pFont->Setup();
		g_pEffectManager->RegisterEffect(pFont);

		g_pSoundManager->play("OrcTargetHit", 1.0f);
		vecDamage.back()->Damage(m_pOwner->GetCurrentDamage() * 2.f);
		vecDamage.pop_back();
		//cout << "블레이드스톰!!!" << endl;
		m_bIsHit = false;
	}

	//시간 조절필요
	if (m_fTwirlCount > 2.0f)
	{
		m_bIsHit = false;
		m_bSkillSound = false;
		m_pOwnerMesh->SetReverse(false, 0, 0);
		m_pOwner->SetDirection(m_vDir);
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}
}
