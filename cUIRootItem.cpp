#include "stdafx.h"
#include "cUIRootItem.h"
#include "cUIImageView.h"
#include "cItem.h"
#include "cRootItem.h"
#include "cUIRootItem.h"
#include "cUnitPlayer.h"
#include "cUnitManager.h"
#include "cInvenTory.h"
#include "cUIButton.h"
#include "cButton.h"

cUIRootItem::cUIRootItem()
	: m_pUIImageView(false)
	, m_bDrag(false)
	, m_pRootItem(false)
{
}


cUIRootItem::~cUIRootItem()
{
}

void cUIRootItem::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_pUIImageView = new cUIImageView;
	m_pUIImageView->SetTexture("./UI/(4)Interface/Interface_13.png");
	m_pUIImageView->SetPosition(D3DXVECTOR3((3 * rc.right / 4) , (rc.left / 2) + 250, 0));
	AddChild(m_pUIImageView);

	cUIButton* pExitButton = new cUIButton;
	pExitButton->SetButtonImage("./UI/(4)Interface/Interface_10.png",
		"./UI/(4)Interface/Interface_11.png",
		"./UI/(4)Interface/Interface_12.png");
	pExitButton->SetPosition(D3DXVECTOR3(m_pUIImageView->GetPosition().x + 160, m_pUIImageView->GetPosition().y + 12, 0));
	pExitButton->SetTag(0);
	pExitButton->SetDelegate(this);
	AddChild(pExitButton);

	//Box
	RootBox();
}

void cUIRootItem::Update()
{
	PickItem();

	for (int i = 0; i < 4; ++i)
	{
		if (m_pRootItem->GetItem(i))
		{
			m_pRootItem->GetItem(i)->GetImageView()->SetPosition(D3DXVECTOR3(m_rc[i].left, m_rc[i].top, 0));
		}
	}
	m_pRootItem->Update();
	cUIObject::Update();
}

void cUIRootItem::Render(LPD3DXSPRITE pSprite)
{
	cUIObject::Render(m_pSprite);
	m_pRootItem->Render(m_pSprite);
}


void cUIRootItem::RootBox()
{
	//Test
	SetRect(&m_rc[0], m_pUIImageView->GetPosition().x + 16, m_pUIImageView->GetPosition().y + 75, m_pUIImageView->GetPosition().x + 16 + 50, m_pUIImageView->GetPosition().y + 75 + 50);
	SetRect(&m_rc[1], m_pUIImageView->GetPosition().x + 16, m_pUIImageView->GetPosition().y + 116, m_pUIImageView->GetPosition().x + 16 + 50, m_pUIImageView->GetPosition().y + 116 + 50);
	SetRect(&m_rc[2], m_pUIImageView->GetPosition().x + 16, m_pUIImageView->GetPosition().y + 157, m_pUIImageView->GetPosition().x + 16 + 50, m_pUIImageView->GetPosition().y + 157 + 50);
	SetRect(&m_rc[3], m_pUIImageView->GetPosition().x + 16, m_pUIImageView->GetPosition().y + 198, m_pUIImageView->GetPosition().x + 16 + 50, m_pUIImageView->GetPosition().y + 198 + 50);

	for (int i = 0; i < 4; ++i)
	{
		if (m_pRootItem->GetItem(i))
		{
			m_pRootItem->GetItem(i)->GetImageView()->SetPosition(D3DXVECTOR3(m_rc[i].left, m_rc[i].top, 0));
		}
	}
}

void cUIRootItem::PickItem()
{
	//Test
	cItem* pItem = NULL;
	if ((GetKeyState(VK_RBUTTON) & 0x8000))
	{
		if (!m_bDrag)
		{
			for (int i = 0; i < 4; ++i)
			{
				if (PtInRect(&m_rc[i], g_ptMouse))
				{
					m_bDrag = true;

					cItem* pItem = m_pRootItem->RemoveItem(i);
					if (pItem)
					{
						g_pUnitManager->GetPlayer()->GetInventory()->AddItem(pItem);
						return;
					}
				}
			}
		}
	}
	else
	{
		m_bDrag = false;
	}
}

void cUIRootItem::OnClick(cUIButton* pButton)
{
	if (pButton->GetTag() == 0)
	{
		m_pUIDelegate->OnUIFinished(this);
		return;
	}
}

