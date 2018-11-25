#include "stdafx.h"
#include "cUnitPlayer.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"
#include "cUIQuestList.h"
#include "cQuestList.h"
#include "cUIInvenTory.h"
#include "cUIStatus.h"
#include "cInvenTory.h"
#include "cEquip.h"
#include "cSkyBox.h"
#include "cRootItem.h"
#include "cUIRootItem.h"
#include "cUIMonsterBar.h"
#include "cUIStore.h"
#include "cSkillInven.h"
#include "cSkillAd.h"


cUnitPlayer::cUnitPlayer()
	: m_pName(NULL)
	, m_bOpenQuestList(false)
	, m_pQuestList(NULL)
	, m_pInventory(NULL)
	, m_pEquip(NULL)
	, m_pSky(NULL)
	, m_pMonsterBar(NULL)
{
	///////////////////////////////////////////////////////////////
	//상위 클래스 변수
	/*SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Direction);
	SYNTHESIZE_ADD_REF(cAction*, m_pAction, Action);
	SYNTHESIZE(iEntityDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(DWORD, m_dEntityType, EntityType);
	SYNTHESIZE(ST_SPHERE, m_stFrustumSphere, FrustumSphere);
	SYNTHESIZE_ADD_REF(iUnitAction*, m_pUnitAction, UnitAction);
	SYNTHESIZE(iUnitDelegate*, m_pUnitDelegate, UnitDelegate);
	SYNTHESIZE(cSkinnedMesh*, m_pMesh, Mesh);
	SYNTHESIZE(cUnit*, m_pTarget, Target);
	SYNTHESIZE(cUnit*, m_pKiller, Killer);
	SYNTHESIZE(float, m_fMaxHp, MaxHp);
	SYNTHESIZE(float, m_fMaxMp, MaxMp);
	SYNTHESIZE(float, m_fCurrentHp, CurrentHp);
	SYNTHESIZE(float, m_fCurrentMp, CurrentMp);
	SYNTHESIZE(float, m_fAttackRange, AttackRange);
	SYNTHESIZE(float, m_fDamage, Damage);
	SYNTHESIZE(float, m_fSpeed, Speed);
	SYNTHESIZE(std::string, m_sName, Name);
	SYNTHESIZE(DWORD, m_dwLevel, Level);*/
	////////////////////////////////////////////////////////////////

	//실험용셋팅 나중엔 파싱으로
	m_vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
	m_vPosition = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_eEntityType = E_PLAYER;
	m_eUnitType = E_CHARACTER;
	m_fMaxHp = 100000;
	m_fMaxMp = 100;
	m_fMaxExp = 100;
	m_fCurrentHp = 100000;
	m_fCurrentMp = 0;
	m_fCurrentExp = 100;
	m_fCurrentMoney = 200000;
	m_fAttackRange = 3.4f;
	m_fOrigDamage = m_fCurrentDamage = 10.0f;
	m_fOrigDefence = m_fCurrentDefence = 5.0f;
	m_fOrigSpeed = m_fCurrentSpeed = 9.0f;
	m_sName = "슈발내가대경이라니";
	m_dwLevel = 1;
	m_dwJumpAnim = 43;
	m_dwFallAnim = 45;
	m_dwFallEndAnim = 44;
}


cUnitPlayer::~cUnitPlayer()
{
	SAFE_RELEASE(m_pName);
	SAFE_RELEASE(m_pUnitAction);
	SAFE_RELEASE(m_pQuestList);
	SAFE_RELEASE(m_pEquip);
	SAFE_RELEASE(m_pSky);
	SAFE_RELEASE(m_pInventory);
	SAFE_RELEASE(m_pMonsterBar);
}


void cUnitPlayer::Setup()
{
	cPlayerAction* pAction = new cPlayerAction;
	pAction->SetOwner(this);
	pAction->SetDelegate(this);
	pAction->Start();
	m_pUnitAction = pAction;

	m_pSkillInven = new cSkillInven;
	m_pSkillInven->Setup();

	m_pMesh = new cSkinnedMesh("Character/orcmale", "orcmale_scale.X");
	m_pMesh->SetPosition(m_vPosition);
	m_pMesh->SetDirection(m_vDirection);
	m_stFrustumSphere = m_pMesh->GetBoundingSphere();

	m_pName = new cText;
	m_pName->Setup(wstring(L"슈발내가대경이라니"));

	//스랄 족장
	m_pQuestList = new cQuestList;
	m_pQuestList->Setup();
	//m_pQuestList->AddQuest(g_pQuestDatabase->GetQuest("스랄 족장"));


	//장비
	m_pEquip= new cEquip;
	m_pEquip->SetUp();
	
	cItem* pItem = g_pItemDatabase->GetItem("1검");
	pItem->Setup();
	m_pEquip->SetEquip(cItem::E_SWORD, pItem);

	pItem = g_pItemDatabase->GetItem("1방패");
	pItem->Setup();
	m_pEquip->SetEquip(cItem::E_SHIELD, pItem);

	pItem = g_pItemDatabase->GetItem("1어깨");
	pItem->Setup();
	m_pEquip->SetEquip(cItem::E_ARMOR1, pItem);

	pItem = g_pItemDatabase->GetItem("1머리");
	pItem->Setup();
	m_pEquip->SetEquip(cItem::E_HELMET, pItem);

	m_pSky = new cSkyBox;
	m_pSky->SetPlayer(this);
	m_pSky->Setup();

	//Test
	m_pMonsterBar = new cUIMonsterBar;
	m_pMonsterBar->Setup();

	m_pInventory = new cInvenTory;
	m_pInventory->Setup();

	//m_pRootItem = new cRootItem;
	//m_pRootItem->Setup();

	//m_pStore = new cStore;
	//m_pStore->Setup();
}



void cUnitPlayer::Update()
{

	ST_BONE* pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)m_pMesh->GetRootFrame(), "Ref_Weapon_Right");

	if (pFind &&
		m_pEquip->GetItem(cItem::E_SWORD) &&
		m_pEquip->GetItem(cItem::E_SWORD)->GetMesh() &&
		pFind->pEquips != m_pEquip->GetItem(cItem::E_SWORD)->GetMesh())
	{
		pFind->pEquips = m_pEquip->GetItem(cItem::E_SWORD)->GetMesh();	
		m_fCurrentDamage = m_fOrigDamage + m_pEquip->GetItem(cItem::E_SWORD)->GetDamage();
	}	

	pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)m_pMesh->GetRootFrame(), "Ref_Hardpoint");

	if (pFind &&
		m_pEquip->GetItem(cItem::E_SHIELD) &&
		m_pEquip->GetItem(cItem::E_SHIELD)->GetMesh() &&
		pFind->pEquips != m_pEquip->GetItem(cItem::E_SHIELD)->GetMesh())
	{
		pFind->pEquips = m_pEquip->GetItem(cItem::E_SHIELD)->GetMesh();		
		m_fCurrentDefence = m_fOrigDefence + m_pEquip->GetItem(cItem::E_SHIELD)->GetDefence();
	}
	
	pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)m_pMesh->GetRootFrame(), "Ref_Hardpoint_04");
 
	if (pFind &&
		m_pEquip->GetItem(cItem::E_ARMOR1) &&
		m_pEquip->GetItem(cItem::E_ARMOR1)->GetMesh() &&
		pFind->pEquips != m_pEquip->GetItem(cItem::E_ARMOR1)->GetMesh())
	{
		pFind->pEquips = m_pEquip->GetItem(cItem::E_ARMOR1)->GetMesh();		
		m_fCurrentDefence = m_fCurrentDefence + m_pEquip->GetItem(cItem::E_ARMOR1)->GetDefence();

		pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)m_pMesh->GetRootFrame(), "Ref_Hardpoint_03");
		pFind->pEquips = m_pEquip->GetItem(cItem::E_ARMOR1)->GetSubMesh();		
		m_fCurrentDefence = m_fCurrentDefence + m_pEquip->GetItem(cItem::E_ARMOR1)->GetDefence();
	}	

	pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)m_pMesh->GetRootFrame(), "Ref_Hardpoint_09");

	if (pFind &&
		m_pEquip->GetItem(cItem::E_HELMET) &&
		m_pEquip->GetItem(cItem::E_HELMET)->GetMesh() &&
		pFind->pEquips != m_pEquip->GetItem(cItem::E_HELMET)->GetMesh())
	{
		pFind->pEquips = m_pEquip->GetItem(cItem::E_HELMET)->GetMesh();		
		m_fCurrentDefence = m_fCurrentDefence + m_pEquip->GetItem(cItem::E_HELMET)->GetDefence();
	}	

	if (m_pQuestList)
	{
		m_pQuestList->Update();
	}

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		Jump();
	}

	cUnit::Update();

	if (m_pTarget)
	{
		m_pMonsterBar->SetOwner(m_pTarget);
		m_pMonsterBar->Update();
	}

	m_pName->SetPosition(m_vPosition);
	m_pName->Update();
	m_pSky->Update();
}

void cUnitPlayer::Render()
{
	if (m_pTarget)
	{
		m_pMonsterBar->Render(NULL);
	}

	if (m_pMesh)
		m_pMesh->UpdateAndRender();
	SphereRender(m_stFrustumSphere);
	m_pName->Render();
	m_pSky->Render();
}

void cUnitPlayer::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pUnitAction)
		m_pUnitAction->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'L':
			OpenQuestList();
			break;
		case 'C':
			OpenStatus();
			break;
		case 'B':
			OpenInvenTory();
			break;
		}
		break;
	}
}

void cUnitPlayer::OnUnitActionFinish(iUnitAction* pAction)
{
	SAFE_RELEASE(m_pUnitAction);
}

void cUnitPlayer::OnBuffFinished(cBuff* pBuff)
{
	SAFE_RELEASE(m_pBuff);
}


D3DXVECTOR3* cUnitPlayer::GetPos()
{
	return &m_vPosition;
}

void cUnitPlayer::Save()
{

}

void cUnitPlayer::Load()
{

}

void cUnitPlayer::OpenQuestList()
{
	cUIQuestList* pUiQuestList = new cUIQuestList;
	pUiQuestList->SetQuestList(m_pQuestList);
	pUiQuestList->Setup();
	g_pUImanager->RegisterUI(pUiQuestList);
}

void cUnitPlayer::OpenInvenTory()
{
	cUIInvenTory* pUIInvenTory = new cUIInvenTory;
	pUIInvenTory->SetpInvenTory(m_pInventory);
	pUIInvenTory->Setup();
	g_pUImanager->RegisterUI(pUIInvenTory);
}
void cUnitPlayer::OpenStatus()
{
	cUIStatus* pUIStatus = new cUIStatus;
	pUIStatus->SetEquip(m_pEquip);
	pUIStatus->Setup();
	g_pUImanager->RegisterUI(pUIStatus);
}

void cUnitPlayer::SetCompleteQuest(cCustomQuest* pQuest)
{
	m_mapCompleteQuest[pQuest->GetName()] = pQuest;
}

cCustomQuest* cUnitPlayer::GetCompleteQuest(string QuestName)
{
	if (m_mapCompleteQuest.find(QuestName) == m_mapCompleteQuest.end())
		return NULL;
	else
		return m_mapCompleteQuest[QuestName];
}