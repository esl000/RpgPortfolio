#include "stdafx.h"
#include "cRootItem.h"
#include "cItem.h"
#include "cUIImageView.h"
#include "cUImanager.h"
#include "cUnitPlayer.h"

cRootItem::cRootItem()
{
}


cRootItem::~cRootItem()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_pRcRootItem[i])
		{
			SAFE_RELEASE(m_pRcRootItem[i]);
		}
	}
}

void cRootItem::Setup()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_pRcRootItem[i])
		{
			m_pRcRootItem[i] = NULL;
		}
	}

	//InitItem();
}

void cRootItem::Update()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_pRcRootItem[i])
		{
			m_pRcRootItem[i]->Update();
		}
	}
}

void cRootItem::Render(LPD3DXSPRITE pSprite)
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_pRcRootItem[i])
		{
			m_pRcRootItem[i]->Render(pSprite);
		}
	}
}

cItem* cRootItem::GetItem(int y)
{
	return m_pRcRootItem[y];
}

void cRootItem::AddItem(cItem* pItem)
{
	for (int i = 0; i < 4; ++i)
	{
		if (!m_pRcRootItem[i])
		{
			m_pRcRootItem[i] = pItem;
			return;
		}
	}
}

void cRootItem::AddItem(cItem* pItem, int y)
{
	m_pRcRootItem[y] = pItem;
}

void cRootItem::InitItem()
{
	for (int i = 0; i < 4; ++i)
	{
		cItem* pItem = new cItem;
		pItem->SetName("¼­¸®ÇÑ");
		pItem->SetItemType(cItem::E_SWORD);
		pItem->SetImageView(new cUIImageView);
		pItem->GetImageView()->SetTexture("./UI/(10)Item/Item_0.png");
		pItem->GetImageView()->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
		AddItem(pItem);
	}
}

cItem* cRootItem::RemoveItem(int y)
{
	cItem* pItem = m_pRcRootItem[y];
	m_pRcRootItem[y] = NULL;
	return pItem;
}