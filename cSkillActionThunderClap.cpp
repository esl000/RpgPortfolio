#include "stdafx.h"
#include "cSkillActionThunderClap.h"
#include "cEffectLightningNova.h"
#include "cEffectLightning.h"
#include "cEffectFont.h"

cSkillActionThunderClap::cSkillActionThunderClap()
		: m_pOwnerMesh(NULL)
		, m_pTarget(NULL)
		, m_bIsHit(true)
		, m_bIsEffect(false)
		, m_dwThunderClapAnim(0)
{
}


cSkillActionThunderClap::~cSkillActionThunderClap()
{
}

void cSkillActionThunderClap::Start()
{
	if (m_pOwner)
	{
		m_pOwnerMesh = m_pOwner->GetMesh();
		m_pTarget = m_pOwner->GetTarget();
	}
}

void cSkillActionThunderClap::Update()
{
	// ÀÌÆÑÆ® ¶§¹®¿¡ °í¹ÎÁß...	//ºí·¹ÀÌµå ½ºÅèÇÏ°í ¹Ù±î¾ßµÊ. ÀÌ°Ô ÇÑ¹æÀÌ°í ºí·¹ÀÌµå½ºÅèÀÌ ¹ð¹ð µµ´Â°Å
	if (m_pOwner->GetAnimChange() && m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwThunderClapAnim)
		m_pOwnerMesh->SetAnimationIndex(m_dwThunderClapAnim);

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
		D3DXVECTOR3 vPos = m_pOwner->GetPosition() + m_pOwner->GetCurrentSpeed() * g_pTimeManager->GetElapsedTime() * 	m_pOwner->GetDirection();
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

	vector<cUnit*> vecDamage;

	if (dPos / dPeriod > 0.6f)
	{
		if (m_bIsHit)
		{
			for each(auto p in *g_pUnitManager->GetSetUnits())
			{
				if (p->GetUnitType() == cUnit::E_MONSTER)
				{
					if (p->GetName() != "µ¥½ºÀ®" &&
						D3DXVec3Length(&(m_pOwner->GetPosition() - p->GetPosition())) < 5.0f)
					{
						vecDamage.push_back(p);
					}
					else if (p->GetName() == "µ¥½ºÀ®" &&
						D3DXVec3Length(&(m_pOwner->GetPosition() - p->GetPosition())) < 10.0f)
					{
						vecDamage.push_back(p);
					}
				}
			}
			m_bIsHit = false;
		}
	}

	if (!m_bIsEffect)
	{
		cEffectLightningNova* pEffect = new cEffectLightningNova;
		pEffect->SetPosition(m_pOwner->GetPosition());
		pEffect->SetDirection(m_pOwner->GetDirection());

		cSkinnedMesh* pMesh = new cSkinnedMesh("effect/LightningNova", "LightningNova.X");
		pMesh->SetPosition(m_pOwner->GetPosition());
		pMesh->SetDirection(m_pOwner->GetDirection());

		pEffect->SetMesh(pMesh);
		pEffect->SetMaxTime(0.5f);
		pEffect->Setup();
		g_pEffectManager->RegisterEffect(pEffect);
		m_bIsEffect = true;
		g_pSoundManager->play("ThunderClap", 1.0f);
	}

	while (vecDamage.size() != 0)
	{
		cEffectLightning* pEffect = new cEffectLightning;
		pEffect->SetPosition(vecDamage.back()->GetPosition());
		pEffect->SetDirection(vecDamage.back()->GetDirection());
		pEffect->SetEffectUnit(vecDamage.back());

		cSkinnedMesh* pMesh = new cSkinnedMesh("effect/Shock", "Shock.X");
		pMesh->SetPosition(vecDamage.back()->GetPosition());
		pMesh->SetDirection(vecDamage.back()->GetDirection());

		pEffect->SetMesh(pMesh);
		pEffect->SetMaxTime(2.0f);
		pEffect->Setup();
		g_pEffectManager->RegisterEffect(pEffect);
		
		cEffectFont* pFont = new cEffectFont;
		pFont->SetPosition(vecDamage.back()->GetPosition());
		pFont->SetDirection(vecDamage.back()->GetDirection());
		pFont->SetEffectUnit(vecDamage.back());
		pFont->SetDamage(m_pOwner->GetCurrentDamage() * 1.5f);
		pFont->SetFontState(cEffectFont::E_SKILL);
		pFont->Setup();
		g_pEffectManager->RegisterEffect(pFont);

		vecDamage.back()->Damage(m_pOwner->GetCurrentDamage() * 1.5f);
		vecDamage.pop_back();
		//cout << "ÃµµÕº­¶ô!!!" << endl;
	}

	if (vecDamage.size() == 0 && dPos / dPeriod > 0.9f)
	{
		if (!m_bIsHit)
		{
			m_pDelegate->OnUnitActionFinish(this);
			return;
		}
	}
}
