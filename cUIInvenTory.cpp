#include "StdAfx.h"
#include "cUIInvenTory.h"

#include "cUIObject.h"
#include "cUIImageView.h"
#include "cUIButton.h"
#include "cUnitPlayer.h"
#include "cEquip.h"
#include "cItem.h"
#include "cUIStatus.h"
#include "cUITextView.h"
#include "cUImanager.h"


cUIInvenTory::cUIInvenTory()
	: m_bInvenToryMax(false)
	, m_bClick(false)
	, m_bCheck(false)
	, m_bExit(false)
	, m_bButton(false)
	, m_bDrag(false)
	, m_bCollision(false)
	, m_pInventory(false)
	, m_bWindowSound(false)
	, m_bButtonSound(false)
{
	m_eUItype = E_INVENTORY;
}



cUIInvenTory::~cUIInvenTory()
{
	g_pSoundManager->play("BagClose", 1.0f);
}

void cUIInvenTory::Setup()
{
	g_pSoundManager->play("BagOpen", 1.0f);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pUIInvenTory = new cUIImageView;
	m_pUIInvenTory->SetTexture(string("./UI/(4)Interface/Interface_6.png"));
	m_pUIInvenTory->SetPosition(D3DXVECTOR3(((rc.right / 2) + 350), ((rc.bottom / 2) - 80), 0));
	AddChild(m_pUIInvenTory);

	cUIButton* pUIExit = new cUIButton;
	pUIExit->SetButtonImage("./UI/(4)Interface/Interface_10.png",
		"./UI/(4)Interface/Interface_11.png",
		"./UI/(4)Interface/Interface_12.png");
	pUIExit->SetPosition(D3DXVECTOR3(m_pUIInvenTory->GetPosition().x + 164, m_pUIInvenTory->GetPosition().y + 8, 0));
	pUIExit->SetTag(0);
	pUIExit->SetDelegate(this);
	AddChild(pUIExit);

	//폰트 초기화
	InvenFont();


	int iInvenTory_X = 0;
	int iInvenTory_Y = 0;
	for (int i = 0; i < ITEM_Y; ++i)
	{
		for (int j = 0; j < ITEM_X; ++j)
		{
			if (i == 0)
			{
				iInvenTory_X = (j * 42);
			}
			else
			{
				iInvenTory_X = (j * 42);
				iInvenTory_Y = i * 41;
			}

			m_vPos.x = (m_pUIInvenTory->GetPosition().x + 14) + iInvenTory_X;
			m_vPos.y = (m_pUIInvenTory->GetPosition().y + 48) + iInvenTory_Y;

			SetRect(&m_aPickRect[i][j],
				int(((m_matWorld._41 + m_vPos.x))),
				int((m_matWorld._42 + m_vPos.y)),
				int((m_matWorld._41 + m_vPos.x + 38)),
				int((m_matWorld._42 + m_vPos.y + 35)));
		}
	}
}

void cUIInvenTory::Update()
{
	m_pInventory->Update();
	InvenToryDrag();
	for (int i = 0; i < ITEM_Y; ++i)
	{
		for (int j = 0; j < ITEM_X; ++j)
		{
			if (m_pInventory->GetItem(i, j)
				&& !(m_pCurrentItem && i == m_dwCurrentIndex[0] && j == m_dwCurrentIndex[1]))
			{
				m_pInventory->GetItem(i, j)->GetImageView()->SetPosition(
					D3DXVECTOR3(m_aPickRect[i][j].left, m_aPickRect[i][j].top, 0));
			}
		}
	}
	cUIObject::Update();
}

void cUIInvenTory::Render(LPD3DXSPRITE pSprite)
{
	cUIObject::Render(m_pSprite);
	m_pInventory->Render(m_pSprite);
	InvenDisplay();
}


void cUIInvenTory::InvenToryDrag()
{
	if ((GetKeyState(VK_RBUTTON) & 0x8000))
	{
		if (!m_bDrag)
		{
			for (int i = 0; i < ITEM_Y; ++i)
			{
				for (int j = 0; j < ITEM_X; ++j)
				{
					if (m_pInventory->GetItem(i, j) && PtInRect(&m_aPickRect[i][j], g_ptMouse))
					{

						m_bDrag = true;
						//Index - Save
						m_dwCurrentIndex[0] = i;
						m_dwCurrentIndex[1] = j;
						//InvenTory - Get
						m_pCurrentItem = m_pInventory->GetItem(i, j);
						return;
					}
				}
			}
		}
	}
	else
	{
		if (m_bDrag)
		{
			m_bDrag = false;
			for (int i = 0; i < ITEM_Y; ++i)
			{
				for (int j = 0; j < ITEM_X; ++j)
				{
					if (PtInRect(&m_aPickRect[i][j], g_ptMouse))
					{
						if (i == m_dwCurrentIndex[0] && j == m_dwCurrentIndex[1])
						{
							//스테이터스 창이면 장착
							cItem* pItem = m_pInventory->RemoveItem(i, j);
							g_pUnitManager->GetPlayer()->GetEquip()->SetEquip(pItem->GetItemType(), pItem);

						}
						else
						{
							cItem* pItem = m_pInventory->GetItem(i, j);

							m_pInventory->AddItem(m_pCurrentItem, i, j);

							if (m_pCurrentItem)
								m_pCurrentItem->GetImageView()->SetPosition(D3DXVECTOR3(m_aPickRect[i][j].left, m_aPickRect[i][j].top, 0));

							m_pInventory->AddItem(pItem, m_dwCurrentIndex[0], m_dwCurrentIndex[1]);

							if (pItem)
								pItem->GetImageView()->SetPosition(
								D3DXVECTOR3(m_aPickRect[m_dwCurrentIndex[0]][m_dwCurrentIndex[1]].left, m_aPickRect[m_dwCurrentIndex[0]][m_dwCurrentIndex[1]].top, 0));
						}
						m_pCurrentItem = NULL;
						return;
					}
				}
			}

			if (m_pCurrentItem)
			{
				//인벤 밖에 있으면 그냥 삭제(실제 게임에서도 삭제함)
				m_pCurrentItem->GetImageView()->SetPosition(
					D3DXVECTOR3(m_aPickRect[m_dwCurrentIndex[0]][m_dwCurrentIndex[1]].left, m_aPickRect[m_dwCurrentIndex[0]][m_dwCurrentIndex[1]].top, 0));
			}

			m_dwCurrentIndex[0] = 0;
			m_dwCurrentIndex[1] = 0;
			m_pCurrentItem = NULL;
		}
	}

	if (m_bDrag)
	{
		if (m_pCurrentItem)
			m_pCurrentItem->GetImageView()->SetPosition(D3DXVECTOR3(g_ptMouse.x, g_ptMouse.y, 0));
	}
}

void cUIInvenTory::OnClick(cUIButton* pButton)
{
	if (pButton->GetTag() == 0)
	{
		m_bExit = true;
		m_pUIDelegate->OnUIFinished(this);
	}
}

void cUIInvenTory::InvenFont()
{
	//폰트 초기화
	D3DXFONT_DESC fd;

	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 8;
	fd.Width = 8;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	AddFontResource("umberto.ttf");
	strcpy_s(fd.FaceName, "umberto");
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
}

void cUIInvenTory::InvenDisplay()
{
	RECT rc;

	//UITextView
	sprintf_s(m_szFont, "%2.f", g_pUnitManager->GetPlayer()->GetCurrentMoney());
	SetRect(&rc, m_pUIInvenTory->GetPosition().x + 100, m_pUIInvenTory->GetPosition().y + 10, 101, 101);
	m_pFont->DrawTextA(NULL,
		m_szFont,
		strlen(m_szFont),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));

}



void cUIInvenTory::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//switch (message)
	//{
	//case WM_KEYDOWN:
	//	switch (wParam)
	//	{
	//	case 'B':
	//		g_pSoundManager->play("BagClose", 1.0f);
	//		m_pUIDelegate->OnUIFinished(this);
	//		break;
	//	}
	//	break;
	//}
}




