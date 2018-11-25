#include "stdafx.h"
#include "cSkillActionWhirlWind.h"
#include "cEffectHit.h"
#include "cEffectFont.h"

cSkillActionWhirlWind::cSkillActionWhirlWind()
		: m_pOwnerMesh(NULL)
		, m_pTarget(NULL)
		, m_pEffect(NULL)
		, m_dwWhirlWindAnim(0)
		, m_fTwirlCount(0)
		, m_bIsHit(false)
		, m_vDir(0, 0, -1)
		, m_bShoundCheck(false)
{
}


cSkillActionWhirlWind::~cSkillActionWhirlWind()
{
	m_pOwnerMesh->SetReverse(false, 0, 0);
}

void cSkillActionWhirlWind::Start()
{
	if (m_pOwner)
	{
		m_pOwnerMesh = m_pOwner->GetMesh();
		m_pTarget = m_pOwner->GetTarget();
		m_vDir = m_pOwner->GetDirection();

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

void cSkillActionWhirlWind::Update()
{
	//ºí·¹ÀÌµå ½ºÅèÇÏ°í ¹Ù±î¾ßµÊ. ÀÌ°Ô ÇÑ¹æÀÌ°í ºí·¹ÀÌµå½ºÅèÀÌ ¹ð¹ð µµ´Â°Å
	m_fTwirlCount += g_pTimeManager->GetElapsedTime();

	if (m_pOwner->GetAnimChange() && m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwWhirlWindAnim)
	{
		m_pOwnerMesh->SetAnimationIndex(m_dwWhirlWindAnim);
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

		//if (g_pIntersectManager->IntersectInBuilding(m_pOwner->GetFrustumSphere(), vPos, vDest))
		//{
		//	vPos = vDest;
		//}

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

		//if (g_pIntersectManager->IntersectInBuilding(m_pOwner->GetFrustumSphere(), vPos, vDest))
		//{
		//	vPos = vDest;
		//}

		//g_pTileManager->GetHeight(vDest, vPos.x, vPos.z);
		m_pOwner->SetPosition(vPos);
	}

	double dPos, dPeriod;
	dPos = m_pOwnerMesh->GetAnimPosition();
	dPeriod = m_pOwnerMesh->GetAnimPeriod();
	dPos = dPos - dPeriod * (int)(dPos / dPeriod);

	if (!m_bShoundCheck & dPos / dPeriod > 0.3f && dPos / dPeriod < 0.4f)
	{
		g_pSoundManager->play("WhirlWind", 1.0f);
		m_bShoundCheck = true;
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
			m_bIsHit = true;
		}
	}
	else if (dPos / dPeriod < 0.2f)
		m_bIsHit = false;

	while (vecDamage.size() != 0)
	{
		cEffectHit* pEffect = new cEffectHit;
		pEffect->SetPosition(vecDamage.back()->GetPosition());
		pEffect->SetDirection(vecDamage.back()->GetDirection());
		pEffect->SetEffectUnit(vecDamage.back());
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
		//cout << "ÈÙÀ©µå!!!" << endl;
	}

	if (m_fTwirlCount > 0.3f)
	{
		m_bShoundCheck = false;
		m_pOwnerMesh->SetReverse(false, 0, 0);
		m_pOwner->SetDirection(m_vDir);
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}
}
