#include "stdafx.h"
#include "cCustomQuest.h"
#include "cInvenTory.h"
#include "cUnitPlayer.h"


cCustomQuest::cCustomQuest()
	: m_sQuestKind("")
	, m_dwLevel(0)
	, m_sPrevQuest("")
	, m_sName("")
	, m_sLore("")
	, m_sTarget("")
	, m_nTargetDeath(0)
	, m_sTakeitem("")
	, m_nTakeitemAmount(0)
	, m_nExp(0)
	, m_nMoney(0)
	, m_sGiveitems("")
	, m_pDelegate(NULL)
	, m_bQuestEnd(false)
{
}


cCustomQuest::~cCustomQuest()
{
}

void cCustomQuest::Update()
{
	if (!(m_nTargetDeath == m_nCurrentTargetDeath) && CheckItem(g_pUnitManager->GetPlayer()->GetInventory()))
	{
		m_nCurrentTargetDeath += g_pMessageManager->FindMessage(cMessageManager::eMessageType::E_MONSTERDIE, m_sTarget);
	}
	
	if (!m_bQuestEnd && m_nTargetDeath == m_nCurrentTargetDeath)
	{
		m_bQuestEnd = true;
	}
}

//업데이트 만들어서 업데이트마다 메세지 찾아와서 카운트 -- 해주기
//	, m_nTargetDeath(0)
//g_pMessageManager->get 맞아요

bool cCustomQuest::CheckItem(cInvenTory* pInventory)
{
	int nItemAmount = m_nTakeitemAmount;

	for (int i = 0; i < ITEM_Y; ++i)
	{
		for (int j = 0; j < ITEM_X; ++j)
		{
			if (pInventory->GetItem(i, j) &&
				pInventory->GetItem(i, j)->GetName() == m_sTakeitem)
			{
				--nItemAmount;
			}
		}
	}

	if (nItemAmount <= 0)
		return true;

	return false;
}

void cCustomQuest::TakeItem(cInvenTory* pInventory)
{
	int nItemAmount = m_nTakeitemAmount;

	for (int i = 0; i < ITEM_Y; ++i)
	{
		for (int j = 0; j < ITEM_X; ++j)
		{
			if (pInventory->GetItem(i, j) &&
				pInventory->GetItem(i, j)->GetName() == m_sTakeitem)
			{
				--nItemAmount;
				pInventory->RemoveItem(i, j)->Release();

				if (nItemAmount == 0)
					return;
			}
		}
	}

}

bool cCustomQuest::CheckFinish()
{
	if (m_bQuestEnd && CheckItem(g_pUnitManager->GetPlayer()->GetInventory()))
	{
		TakeItem(g_pUnitManager->GetPlayer()->GetInventory());
		return true;
	}
	return false;
}
