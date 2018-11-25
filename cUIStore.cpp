#include "stdafx.h"
#include "cUIStore.h"

#include "cUIImageView.h"
#include "cUIButton.h"
#include "cUnitManager.h"

#include "cStore.h"
#include "cUnitPlayer.h"
#include "cItem.h"
#include "cUIInvenTory.h"
#include "cStore.h"

cUIStore::cUIStore()
	: m_pSprite(NULL)
{
}

cUIStore::~cUIStore()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			SAFE_RELEASE(m_aItem[i][j]);
		}
	}
}

void cUIStore::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	
	cUIImageView* pImageStore = new cUIImageView;
	pImageStore->SetTexture("./UI/(4)Interface/Interface_16.png");
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	pImageStore->SetPosition(D3DXVECTOR3((rc.right / 2) , (rc.left / 2), 0));
	AddChild(pImageStore);

	cUIButton* pUIExit = new cUIButton;
	pUIExit->SetButtonImage("./UI/(4)Interface/Interface_10.png", "./UI/(4)Interface/Interface_11.png", "./UI/(4)Interface/Interface_12.png");
	pUIExit->SetPosition(D3DXVECTOR3(pImageStore->GetPosition().x + 300, pImageStore->GetPosition().y + 10, 0));
	pUIExit->SetTag(0);
	pUIExit->SetDelegate(this);
	AddChild(pUIExit);

	//m_pStore = new cStore;
	//m_pStore->Setup();

	int iInvenTory_X = 0;
	int iInvenTory_Y = 0;
	D3DXVECTOR3 vPos;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (i == 0)
			{
				iInvenTory_X = (j * 154);
			}
			else
			{
				iInvenTory_X = (j * 154);
				iInvenTory_Y = i * 48;
			}

			vPos.x = (pImageStore->GetPosition().x + 16) + iInvenTory_X;
			vPos.y = (pImageStore->GetPosition().y + 75) + iInvenTory_Y;

			SetRect(&m_rcStore[i][j],
				int(((m_matWorld._41 + vPos.x))),
				int((m_matWorld._42 + vPos.y)),
				int((m_matWorld._41 + vPos.x + 38)),
				int((m_matWorld._42 + vPos.y + 35)));
		}
	}

	m_aItem[0][0] = g_pItemDatabase->GetItem("5머리");
	m_aItem[0][0]->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
	m_aItem[0][0]->Setup();

	m_aItem[0][1] = g_pItemDatabase->GetItem("3머리");
	m_aItem[0][1]->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
	m_aItem[0][1]->Setup();

	m_aItem[1][0] = g_pItemDatabase->GetItem("4어깨");
	m_aItem[1][0]->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
	m_aItem[1][0]->Setup();

	m_aItem[1][1] = g_pItemDatabase->GetItem("3어깨");
	m_aItem[1][1]->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
	m_aItem[1][1]->Setup();

	m_aItem[2][0] = g_pItemDatabase->GetItem("4방패");
	m_aItem[2][0]->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
	m_aItem[2][0]->Setup();

	m_aItem[2][1] = g_pItemDatabase->GetItem("3방패");
	m_aItem[2][1]->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
	m_aItem[2][1]->Setup();

	m_aItem[3][0] = g_pItemDatabase->GetItem("5검");
	m_aItem[3][0]->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
	m_aItem[3][0]->Setup();

	m_aItem[3][1] = g_pItemDatabase->GetItem("4검");
	m_aItem[3][1]->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
	m_aItem[3][1]->Setup();

	m_aItem[4][0] = g_pItemDatabase->GetItem("3검");
	m_aItem[4][0]->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f)); 
	m_aItem[4][0]->Setup();
			
	m_aItem[4][1] = g_pItemDatabase->GetItem("2검");
	m_aItem[4][1]->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
	m_aItem[4][1]->Setup();
}

void cUIStore::Update()
{
	PickStore();

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (m_aItem[i][j])
			{
				m_aItem[i][j]->GetImageView()->SetPosition(D3DXVECTOR3(m_rcStore[i][j].left, m_rcStore[i][j].top, 0));
				m_aItem[i][j]->Update();
			}
		}
	}
	cUIObject::Update();
}

void cUIStore::Render(LPD3DXSPRITE pSprite)
{
	cUIObject::Render(m_pSprite);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (m_aItem[i][j])
			{
				m_aItem[i][j]->Render(m_pSprite);
			}
		}
	}
}

void cUIStore::OnClick(cUIButton* pButton)
{
	if (pButton->GetTag() == 0)
	{

	}
}

void cUIStore::PickStore()
{
	//Test
	if ((GetKeyState(VK_RBUTTON) & 0x8000))
	{
		if (!m_bDrag)
		{
			for (int i = 0; i < 5; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					if (PtInRect(&m_rcStore[i][j], g_ptMouse))
					{
						m_bDrag = true;

						if (m_aItem[i][j])
						{
							//Store_Input
							cItem* pItem = g_pItemDatabase->GetItem(m_aItem[i][j]->GetName());
							pItem->Setup();
							g_pUnitManager->GetPlayer()->SetCurrentMoney(g_pUnitManager->GetPlayer()->GetCurrentMoney() - m_aItem[i][j]->GetGold());
							g_pUnitManager->GetPlayer()->GetInventory()->AddItem(pItem);
							return;
						}
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
