#include "StdAfx.h"
#include "cUIStatus.h"

#include "cUIObject.h"
#include "cUIButton.h"
#include "cUIImageView.h"
#include "cDeviceManager.h"
#include "cUnitPlayer.h"
#include "cUIStatus.h"
#include "cUIInvenTory.h"
#include "cEquip.h"
#include "cItem.h"

#include "cAllocateHierarchy.h"

cUIStatus::cUIStatus(void)
	: m_pUIImageView(NULL)
	, m_pEquip(NULL)
	, m_vPos(0, 0, 0)
	, m_pFont(NULL)
	, m_bDrag(false)

{
	m_eUItype = E_STATUS;
}


cUIStatus::~cUIStatus()
{
	g_pSoundManager->play("CharacterWindowClose", 1.0f);
}

void cUIStatus::Setup()
{
	g_pSoundManager->play("CharacterWindowOpen", 1.0f);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	m_pUIImageView = new cUIImageView;
	m_pUIImageView->SetTexture(string("./UI/(4)Interface/Interface_7.png"));
	m_pUIImageView->SetPosition(D3DXVECTOR3(180, 140, 0));
	AddChild(m_pUIImageView);

	cUIButton* pUIExit = new cUIButton;
	pUIExit->SetButtonImage("./UI/(4)Interface/Interface_10.png",
		"./UI/(4)Interface/Interface_11.png",
		"./UI/(4)Interface/Interface_12.png");
	pUIExit->SetPosition(D3DXVECTOR3(m_pUIImageView->GetPosition().x + 322, m_pUIImageView->GetPosition().y + 12, 0));
	pUIExit->SetTag(0);
	pUIExit->SetDelegate(this);
	AddChild(pUIExit);

	StatusFont();

	m_vPos = m_pUIImageView->GetPosition();
	SetRect(&m_aRect[0], m_vPos.x + 10, m_vPos.y + 71, m_vPos.x + 10 + 33, m_vPos.y + 71 + 33);
	SetRect(&m_aRect[1], m_vPos.x + 10, m_vPos.y + 154, m_vPos.x + 10 + 33, m_vPos.y + 154 + 33);
	SetRect(&m_aRect[2], m_vPos.x + 10, m_vPos.y + 196, m_vPos.x + 10 + 33, m_vPos.y + 196 + 33);
	SetRect(&m_aRect[3], m_vPos.x + 110, m_vPos.y + 380, m_vPos.x + 118 + 33, m_vPos.y + 386 + 33);
	SetRect(&m_aRect[4], m_vPos.x + 156, m_vPos.y + 380, m_vPos.x + 160 + 33, m_vPos.y + 386 + 33);

	for (int i = 0; i < cItem::E_NONE; ++i)
	{
		if (m_pEquip->GetItem(i))
			m_pEquip->GetItem(i)->GetImageView()->SetPosition(D3DXVECTOR3(m_aRect[i].left, m_aRect[i].top, 0));
	}
}

void cUIStatus::Update()
{
	KeyCheck();
	StatusDrag();
	cUIObject::Update();

	for (int i = 0; i < cItem::E_NONE; ++i)
	{
		if (m_pEquip->GetItem(i))
			m_pEquip->GetItem(i)->GetImageView()->SetPosition(D3DXVECTOR3(m_aRect[i].left, m_aRect[i].top, 0));
	}
	m_pEquip->Update();
}

void cUIStatus::StatusDrag()
{
	if ((GetKeyState(VK_RBUTTON) & 0x8000))
	{
		if (!m_bDrag)
		{
			for (int i = 0; i < cItem::E_NONE; ++i)
			{
				if (m_pEquip->GetItem(i) && PtInRect(&m_aRect[i], g_ptMouse))
				{
					m_bDrag = true;
					//인벤토리에
					//장비템 넣어주기
					cItem* pItem = m_pEquip->RemoveEquip(i);
					if (pItem)
					{
						g_pUnitManager->GetPlayer()->GetInventory()->AddItem(pItem);	
						//if (i == cItem::E_HELMET)
						//{
						//	ST_BONE* pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)g_pUnitManager->GetPlayer()->GetMesh()->GetRootFrame(), "Ref_Hardpoint_09");
						//	g_pUnitManager->GetPlayer()->SetCurrentDefence(g_pUnitManager->GetPlayer()->GetCurrentDefence() - pItem->GetDefence());
						//	pFind->pEquips = NULL;
						//}
						//else if (i == cItem::E_ARMOR1)
						//{
						//	ST_BONE* pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)g_pUnitManager->GetPlayer()->GetMesh()->GetRootFrame(), "Ref_Hardpoint_04");
						//	g_pUnitManager->GetPlayer()->SetCurrentDefence(g_pUnitManager->GetPlayer()->GetCurrentDefence() - pItem->GetDefence());
						//	pFind->pEquips = NULL;

						//	pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)g_pUnitManager->GetPlayer()->GetMesh()->GetRootFrame(), "Ref_Hardpoint_03");
						//	g_pUnitManager->GetPlayer()->SetCurrentDefence(g_pUnitManager->GetPlayer()->GetCurrentDefence() - pItem->GetDefence());
						//	pFind->pEquips = NULL;
						//}
						//else if (i == cItem::E_SWORD)
						//{
						//	ST_BONE* pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)g_pUnitManager->GetPlayer()->GetMesh()->GetRootFrame(), "Ref_Weapon_Right");
						//	g_pUnitManager->GetPlayer()->SetCurrentDamage(g_pUnitManager->GetPlayer()->GetCurrentDamage() - pItem->GetDamage());
						//	pFind->pEquips = NULL;
						//}	
						//else if (i == cItem::E_SHIELD)
						//{
						//	ST_BONE* pFind = (ST_BONE*)D3DXFrameFind((D3DXFRAME*)g_pUnitManager->GetPlayer()->GetMesh()->GetRootFrame(), "Ref_Hardpoint");
						//	g_pUnitManager->GetPlayer()->SetCurrentDefence(g_pUnitManager->GetPlayer()->GetCurrentDefence() - pItem->GetDefence());
						//	pFind->pEquips = NULL;
						//}	

						//int nType = pItem->GetItemType();
						//StatusCalc(nType);
						//return;
					}
					return;
				}
			}
		}
	}
	else
	{
		if (m_bDrag)
		{
			m_bDrag = false;
		}
	}
}

void cUIStatus::Render(LPD3DXSPRITE pSprite)
{
	cUIObject::Render(m_pSprite);
	m_pEquip->Render(m_pSprite);

	StatusDisplay();
}

void cUIStatus::KeyCheck()
{
	//if (GetKeyState('C') & 0x8000)
	//{
	//	g_pSoundManager->play("CharacterWindowClose", 1.0f);
	//	m_pUIDelegate->OnUIFinished(this);
	//	return;
	//}
}

void cUIStatus::StatusFont()
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

void cUIStatus::StatusDisplay()
{
	RECT rc;

	//현재데미지
	sprintf_s(m_szFont, "%2.f", g_pUnitManager->GetPlayer()->GetCurrentDamage());
	SetRect(&rc, m_pUIImageView->GetPosition().x + 121, m_pUIImageView->GetPosition().y + 293, 101, 101);
	m_pFont->DrawTextA(NULL,
		m_szFont,
		strlen(m_szFont),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));

	//현재HP
	sprintf_s(m_szFont, "%2.f", g_pUnitManager->GetPlayer()->GetCurrentHp());
	SetRect(&rc, m_pUIImageView->GetPosition().x + 121, m_pUIImageView->GetPosition().y + 319, 101, 101);
	m_pFont->DrawTextA(NULL,
		m_szFont,
		strlen(m_szFont),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));

	//최대HP
	//sprintf_s(m_szFont, "%2.f", g_pUnitManager->GetPlayer()->GetMaxHp());
	////SetRect(&rc, 228, 350, 101, 101);
	//SetRect(&rc, m_pUIImageView->GetPosition().x + 243, m_pUIImageView->GetPosition().y + 319, 101, 101);
	//m_pFont->DrawTextA(NULL,
	//	m_szFont,
	//	strlen(m_szFont),
	//	&rc,
	//	DT_LEFT | DT_TOP | DT_NOCLIP,
	//	D3DCOLOR_XRGB(255, 255, 0));

	//현재MP
	sprintf_s(m_szFont, "%2.f", g_pUnitManager->GetPlayer()->GetCurrentMp());
	SetRect(&rc, m_pUIImageView->GetPosition().x + 121, m_pUIImageView->GetPosition().y + 332, 101, 101);
	m_pFont->DrawTextA(NULL,
		m_szFont,
		strlen(m_szFont),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));

	//최대MP
	//sprintf_s(m_szFont, "%2.f", g_pUnitManager->GetPlayer()->GetMaxMp());
	//SetRect(&rc, m_pUIImageView->GetPosition().x + 243, m_pUIImageView->GetPosition().y + 33, 101, 101);
	//m_pFont->DrawTextA(NULL,
	//	m_szFont,
	//	strlen(m_szFont),
	//	&rc,
	//	DT_LEFT | DT_TOP | DT_NOCLIP,
	//	D3DCOLOR_XRGB(255, 255, 0));

	//방어력
	sprintf_s(m_szFont, "%2.f", g_pUnitManager->GetPlayer()->GetCurrentDefence());
	SetRect(&rc, m_pUIImageView->GetPosition().x + 121, m_pUIImageView->GetPosition().y + 358, 101, 101);
	m_pFont->DrawTextA(NULL,
		m_szFont,
		strlen(m_szFont),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));
}

void cUIStatus::OnClick(cUIButton* pButton)
{
	if (pButton->GetTag() == 0)
	{
		m_pUIDelegate->OnUIFinished(this);
		return;
	}
}


void cUIStatus::StatusCalc(int nType)
{
	switch (nType)
	{
	case cItem::E_HELMET:
		break;
	case cItem::E_ARMOR1:
		break;
	case cItem::E_ARMOR2:
		break;
	case cItem::E_SWORD:
		break;
	case cItem::E_SHIELD:
		break;
	}
}

void cUIStatus::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case 'C':
			break;
	}
	

}