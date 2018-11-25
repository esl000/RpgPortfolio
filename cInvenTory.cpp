#include "stdafx.h"
#include "cInvenTory.h"
#include "cUIObject.h"

cInvenTory::cInvenTory()
{
}


cInvenTory::~cInvenTory()
{
	for (int i = 0; i < ITEM_Y; ++i)
	{
		for (int j = 0; j < ITEM_X; ++j)
		{
			SAFE_RELEASE(m_rcSlot[i][j]);
		}
	}
}

void cInvenTory::Setup()
{
	for (int i = 0; i < ITEM_Y; ++i)
	{
		for (int j = 0; j < ITEM_X; ++j)
		{
			m_rcSlot[i][j] = NULL;
		}
	}

	for (int i = 0; i < 1; ++i)
	{
			}
}

void cInvenTory::Update()
{
	for (int i = 0; i < ITEM_Y; ++i)
	{
		for (int j = 0; j < ITEM_X; ++j)
		{
			if (m_rcSlot[i][j])
				m_rcSlot[i][j]->Update();
		}
	}
}

void cInvenTory::Render(LPD3DXSPRITE pSprite)
{
	for (int i = 0; i < ITEM_Y; ++i)
	{
		for (int j = 0; j < ITEM_X; ++j)
		{
			if (m_rcSlot[i][j])
				m_rcSlot[i][j]->Render(pSprite);
		}
	}
}

cItem* cInvenTory::GetItem(int y, int x)
{
	return m_rcSlot[y][x];
}

void cInvenTory::AddItem(cItem* pItem)
{
	for (int i = 0; i < ITEM_Y; ++i)
	{
		for (int j = 0; j < ITEM_X; ++j)
		{
			if (!m_rcSlot[i][j])
			{
				m_rcSlot[i][j] = pItem;
				return;
			}
		}
	}
}

void cInvenTory::AddItem(cItem* pItem, int y, int x)
{
	//SAFE_RELEASE(m_rcSlot[y][x]);
	m_rcSlot[y][x] = pItem;
}

cItem* cInvenTory::RemoveItem(int y, int x)
{
	cItem* pItem = m_rcSlot[y][x];
	m_rcSlot[y][x] = NULL;
	return pItem;
}