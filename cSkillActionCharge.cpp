#include "stdafx.h"
#include "cSkillActionCharge.h"
#include "cEffectFont.h"

cSkillActionCharge::cSkillActionCharge()
		:m_pOwnerMesh(NULL)
		, m_pEffect(NULL)
		, m_pTarget(NULL)
		, m_dwRushAnim(0)
{
}


cSkillActionCharge::~cSkillActionCharge()
{
}

void cSkillActionCharge::Start()
{
	if (m_pOwner)
	{
		m_pOwnerMesh = m_pOwner->GetMesh();
		m_pTarget = m_pOwner->GetTarget();
		g_pSoundManager->play("ShockWave", 1.0f);

		m_pEffect = new cEffectTrajectory;
		m_pEffect->SetOwnerMesh(m_pOwnerMesh);
		m_pEffect->SetMaxTime(2.0f);
	
		m_pEffect->SetPosition(m_pOwner->GetPosition());
		m_pEffect->SetDirection(m_pOwner->GetDirection());
		m_pEffect->SetFaceColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pEffect->SetColorChangeTime(0.1f);
		m_pEffect->SetPosition(m_pOwner->GetPosition());
		m_pEffect->SetDirection(m_pOwner->GetDirection());
		m_pEffect->Setup();
		g_pEffectManager->RegisterEffect(m_pEffect);
	}
}

void cSkillActionCharge::Update()
{
	if (!m_pOwner || !m_pOwner->GetTarget() || !m_pTarget)
	{
		m_pDelegate->OnUnitActionFinish(this);
		return;
	}
	m_pTarget = m_pOwner->GetTarget();

	/////////////////////////////////////////////////////////////////////////////////
	//�� ������ Ű������ üũ...
	//���� �ּһ�Ÿ����� ������ �������
	//if (D3DXVec3Length(&(m_pOwner->GetPosition() - m_pTarget->GetPosition())) < 10.0f)
	//{
	//	m_pDelegate->OnUnitActionFinish(this);
	//	return;
	//}

	//////////////////////////////////////////////
	//���������� �ƴ��� ����üũ�� �ʿ���...
	//////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	
	if (m_pOwner->GetAnimChange() && m_pOwnerMesh && m_pOwnerMesh->GetCurrentAni() != m_dwRushAnim)
		m_pOwnerMesh->SetAnimationIndex(m_dwRushAnim);
	
	//��ǥ������ ����. �ſ���� �̰� ������ ����
	D3DXVECTOR3 vDirection = m_pTarget->GetPosition() - m_pOwner->GetPosition();
	D3DXVec3Normalize(&vDirection, &vDirection);
	m_pOwner->SetDirection(vDirection);

	D3DXVECTOR3 vPos = m_pOwner->GetPosition() + m_pOwner->GetCurrentSpeed() * 5.0f * g_pTimeManager->GetElapsedTime() * m_pOwner->GetDirection();
	D3DXVECTOR3 vDest;

	ST_SPHERE stSphere(vPos, m_pOwner->GetFrustumSphere().fRadius);

	if (g_pIntersectManager->IntersectEntitys(stSphere))
		return;

	if (g_pIntersectManager->IntersectInBuilding(m_pOwner->GetFrustumSphere(), vPos, vDest))
	{
		vPos = vDest;
	}
	
	//���ݻ�Ÿ��� �����ʿ�
	if (m_pTarget->GetName() != "������" && 
		D3DXVec3Length(&(m_pTarget->GetPosition() - m_pOwner->GetPosition())) < 3.5f)
	{
		//�� action ���Ͼ׼� �߰� �ʿ���.
		//cout << "����" << endl;
		cEffectFont* pFont = new cEffectFont;
		pFont->SetPosition(m_pTarget->GetPosition());
		pFont->SetDirection(m_pTarget->GetDirection());
		pFont->SetEffectUnit(m_pTarget);
		pFont->SetDamage(m_pOwner->GetCurrentDamage());
		pFont->SetFontState(cEffectFont::E_SKILL);
		pFont->Setup();
		g_pEffectManager->RegisterEffect(pFont);

		m_pTarget->Damage(m_pOwner->GetCurrentDamage());
		m_pDelegate->OnUnitActionFinish(this);

		return;		
	}
	else if (m_pTarget->GetName() == "������" &&
		D3DXVec3Length(&(m_pTarget->GetPosition() - m_pOwner->GetPosition())) < 9.5f)
	{
		//�� action ���Ͼ׼� �߰� �ʿ���.
		//cout << "����" << endl;
		cEffectFont* pFont = new cEffectFont;
		pFont->SetPosition(m_pTarget->GetPosition());
		pFont->SetDirection(m_pTarget->GetDirection());
		pFont->SetEffectUnit(m_pTarget);
		pFont->SetDamage(m_pOwner->GetCurrentDamage());
		pFont->SetFontState(cEffectFont::E_SKILL);
		pFont->Setup();
		g_pEffectManager->RegisterEffect(pFont);

		m_pTarget->Damage(m_pOwner->GetCurrentDamage());
		m_pDelegate->OnUnitActionFinish(this);

		return;
	}
	else
	{
		m_pOwner->SetPosition(vPos);
		m_pEffect->SetPosition(m_pOwner->GetPosition());
		m_pEffect->SetDirection(m_pOwner->GetDirection());
	}
}
