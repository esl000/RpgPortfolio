#include "stdafx.h"

/*
#include "cStore.h"


#include "cItem.h"
#include "cUIObject.h"

cStore::cStore()
{
}


cStore::~cStore()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (m_rcSlot[i][j])
			{
				SAFE_RELEASE(m_rcSlot[i][j]);
			}
		}
	}
}

void cStore::Setup()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (m_rcSlot[i][j])
			{
				m_rcSlot[i][j] = NULL;
			}
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		cItem* pItem = new cItem;
		pItem->SetName("테스트아이템");
		cItem::eItemType eITemType = StoreType(i);
		pItem->SetItemType(eITemType);
		pItem->SetImageView(new cUIImageView);
		string szStore = StoreImage(i);
		pItem->GetImageView()->SetTexture(szStore);
		pItem->GetImageView()->SetScale(D3DXVECTOR3(0.63f, 0.63f, 1.f));
		AddStore(pItem);
	}
}

void cStore::Update()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (m_rcSlot[i][j])
			{
				if (m_rcSlot[i][j])
					m_rcSlot[i][j]->Update();
			}
		}
	}
}

void cStore::Render(LPD3DXSPRITE pSprite)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (m_rcSlot[i][j])
			{
				if (m_rcSlot[i][j])
					m_rcSlot[i][j]->Render(pSprite);
			}
		}
	}
}

cItem* cStore::GetStore(int y, int x)
{
	return m_rcSlot[y][x];
}


void cStore::AddStore(cItem* pItem)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (!m_rcSlot[i][j])
			{
				m_rcSlot[i][j] = pItem;
				return;
			}
		}
	}
}

void cStore::AddStore(cItem* pItem, int y, int x)
{
	m_rcSlot[y][x] = pItem;
}

cItem* cStore::GetStoreItem(int y, int x)
{
	//lstrcpy((LPSTR)m_pTempItem, (LPSTR)m_rcSlot[y][x]);
	//memcpy(m_rcDest[y][x], m_rcSlot[y][x], sizeof(m_rcSlot[y][x]) / sizeof(m_rcSlot[0]));
	//memcpy(m_rcDest[y][x], m_rcSlot[y][x], 5 * sizeof(cItem));
	//memcpy(m_rcDest[y][x], m_rcSlot[y][x], 5 * sizeof(m_rcSlot));
	
	//cItem* pItem = new cItem;
	//*pItem = *(m_rcSlot[y][x]);

	//cItem *pItem = m_rcSlot[y][x];
	//m_rcSlot[y][x] = NULL;
	//cItem *pTemp = new cItem;
	////memcpy(pTemp, pItem, pItem);
	//*pTemp = *pItem;

	//return pItem;

	cItem* pItem = m_rcSlot[y][x];
	return pItem;
}

void cStore::GetTestStore(int y, int x)
{
	m_rcSlot[y][x];
}

cItem* cStore::RemoveItem(int y, int x)
{
	cItem* pItem = m_rcSlot[y][x];
	m_rcSlot[y][x] = NULL;
	return pItem;
}


string cStore::StoreImage(int nData)
{
	string szData;
	switch (nData)
	{
	case 0:
		szData = string("./UI/(10)Item/helm01.png");
		break;
	case 1:
		szData = string("./UI/(10)Item/shoulder01.png");
		break;
	case 2:
		szData = string("./UI/(10)Item/helm01.png");
		break;
	case 3:
		szData = string("./UI/(10)Item/sword01.png");
		break;
	case 4:
		szData = string("./UI/(10)Item/Shield01.png");
		break;
	}
	return szData;
}

//스킬 테스트
cItem::eItemType cStore::StoreType(int nData)
{
	cItem::eItemType eItemType;
	switch (nData)
	{
	case 0:
		eItemType = cItem::E_HELMET;
		break;
	case 1:
		eItemType = cItem::E_ARMOR1;
		break;
	case 2:
		eItemType = cItem::E_ARMOR2;
		break;
	case 3:
		eItemType = cItem::E_SWORD;
		break;
	case 4:
		eItemType = cItem::E_SHIELD;
		break;
	}
	return eItemType;
}
*/