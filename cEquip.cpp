#include "stdafx.h"
#include "cEquip.h"
#include "cItem.h"
#include "cUnitPlayer.h"
#include "cInvenTory.h"


cEquip::cEquip()
{
}


cEquip::~cEquip()
{
	for (int i = 0; i < cItem::E_NONE; ++i)
	{
		SAFE_RELEASE(m_aItem[i])
	}
}

void cEquip::SetUp()
{
	for (int i = 0; i < cItem::E_NONE; ++i)
	{
		m_aItem[i] = NULL;
	}
}

void cEquip::Update()
{
	for (int i = 0; i < cItem::E_NONE; ++i)
	{
		if (m_aItem[i])
			m_aItem[i]->Update();
	}
}

void cEquip::Render(LPD3DXSPRITE pSprite)
{
	for (int i = 0; i < cItem::E_NONE; ++i)
	{
		if (m_aItem[i])
			m_aItem[i]->Render(pSprite);
	}
}

void cEquip::SetEquip(int nType, cItem* pItem)
{
	if (m_aItem[nType])
		g_pUnitManager->GetPlayer()->GetInventory()->AddItem(m_aItem[nType]);
	m_aItem[nType] = pItem;
}

cItem* cEquip::GetItem(int nType)
{
	return m_aItem[nType];
}

cItem* cEquip::RemoveEquip(int nType)
{
	cItem* pItem = m_aItem[nType];
	m_aItem[nType] = NULL;
	return pItem;
}