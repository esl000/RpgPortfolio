#include "stdafx.h"
#include "cUnitMonster.h"
#include "cActionBaseAi.h"
#include "cDieEffect.h"
#include "cUIMonsterBar.h"
#include "cRootItem.h"
#include "cItem.h"
#include "cActionBossAi.h"

cUnitMonster::cUnitMonster()
	: m_sFolder("")
	, m_sFile("")
	, m_dwLevel(0)
	, m_nExp(0)
	, m_nMoney(0)	
{
	m_eEntityType = E_UNIT;
	m_eUnitType = E_MONSTER;
}


cUnitMonster::~cUnitMonster()
{
}

void cUnitMonster::Setup()
{
	//스피드 등등 초기화 안해준거 나중에 해준다.

	m_pTarget = (cUnit*)g_pUnitManager->GetPlayer();
	m_fOrigSpeed = m_fCurrentSpeed = 9.f;
	m_fAttackRange = 3.5f;
	m_fCurrentDamage = m_fOrigDamage;
	m_fCurrentDefence = m_fOrigDefence;
	m_pMesh = new cSkinnedMesh(m_sFolder.c_str(), m_sFile.c_str());
	m_pMesh->SetPosition(m_vPosition);
	m_pMesh->SetDirection(m_vDirection);
	m_stFrustumSphere = m_pMesh->GetBoundingSphere();


#ifdef MAPTOOL

#else
	if (m_sName == "데스윙")
	{		
		m_fAttackRange = 15.f;

		cActionBossAi* pAction = new cActionBossAi;
		//나중에 넣어준다.
		pAction->SetWalkAnim(1);
		pAction->SetAttackAnim(3);
		pAction->SetOrgPos(m_vPosition);
		pAction->SetOrgDir(m_vDirection);
		pAction->SetDelegate(this);
		pAction->SetOwner(this);
		pAction->Start();
		D3DXVECTOR3 vDest;
		m_pUnitAction = pAction;
	}
	else
	{
		cActionBaseAi* pAction = new cActionBaseAi;
		//나중에 넣어준다.
		pAction->SetWalkAnim(1);
		pAction->SetAttackAnim(3);
		pAction->SetOrgPos(m_vPosition);
		pAction->SetOrgDir(m_vDirection);
		pAction->SetDelegate(this);
		pAction->SetOwner(this);
		pAction->Start();
		D3DXVECTOR3 vDest;
		m_pUnitAction = pAction;
	}	
	//if (g_pTileManager->GetHeight(vDest, m_vPosition))
	//{
	//	m_vPosition = vDest;
	//}
#endif
}

void cUnitMonster::Update()
{
	if (m_pBuff)
		m_pBuff->Update();
	if (m_pUnitAction)
		m_pUnitAction->Update();

	if (m_pMesh)
	{
		m_pMesh->SetPosition(m_vPosition);
		m_pMesh->SetDirection(m_vDirection);
		m_stFrustumSphere = m_pMesh->GetBoundingSphere();
	}
}

void cUnitMonster::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0.5f);

	if (m_pMesh)
		m_pMesh->UpdateAndRender();

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	SphereRender(m_stFrustumSphere);
}

void cUnitMonster::Damage(float fDamage)
{
	((cActionBaseAi*)m_pUnitAction)->SetDeffense(true);
	cUnit::Damage(fDamage);
}

void cUnitMonster::Die()
{
	cDieEffect* pEffect = new cDieEffect;
	pEffect->SetPosition(m_vPosition);
	pEffect->SetDirection(m_vDirection);
	cSkinnedMesh* pMesh = new cSkinnedMesh(m_sFolder.c_str(), m_sFile.c_str());
	pMesh->SetPosition(m_vPosition);
	pMesh->SetDirection(m_vDirection);

	cRootItem* pInv = new cRootItem;
	pInv->Setup();

	for each (auto s in m_vecItems)
	{
		cItem* pItem = g_pItemDatabase->GetItem(s);
		pItem->Setup();
		pInv->AddItem(pItem);
	}
	pEffect->SetRootInv(pInv);
	pEffect->SetMesh(pMesh);
	pEffect->SetDeadAnim(4);
	pEffect->SetMaxTime(30.f);
	pEffect->Setup();
	g_pEffectManager->RegisterEffect(pEffect);
	ST_MESSAGE stMessage;
	stMessage.dwFlag = cMessageManager::E_MONSTERDIE;
	stMessage.sData = m_sName;
	g_pMessageManager->PushMessage(stMessage);
	return;
}


void cUnitMonster::OnUnitActionFinish(iUnitAction* pAction)
{
	if (m_pMesh)
		m_pMesh->SetAnimationIndex(E_STAND);
	assert(m_pUnitAction == pAction);
	SAFE_RELEASE(m_pUnitAction);
}

