#include "StdAfx.h"
#include "cUIIQuest.h"
#include "cUITextView.h"
#include "cUIImageView.h"
#include "cUnitCustomNpc.h"
#include "cCustomQuest.h"
#include "cUImanager.h"
#include "cUIButton.h"
#include "cUnitPlayer.h"
#include "cQuestList.h"
#include "cInvenTory.h"

cUIIQuest::cUIIQuest(void)
	: m_pUiImageView(NULL)
	, m_pUiTextView(NULL) 
	, m_pQuest(NULL)
	, m_bEnd(false)
{
	m_eUItype = E_QUEST;
}


cUIIQuest::~cUIIQuest(void)
{
}

void cUIIQuest::Setup(void)
{
	//열때 퀘스트 아이템 체크 
	if (m_pQuest->CheckFinish())
	{
		m_bEnd = true;
		m_pQuest->SetQuestEnd(true);
	}

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_pUiImageView = new cUIImageView;
	m_pUiImageView->SetTexture(string("./UI/(8)Quest/quest.png"));
	m_pUiImageView->SetPosition(D3DXVECTOR3(rc.right, (rc.bottom / 2) + 100, 0));
	AddChild(m_pUiImageView);

	m_pUiTextView = new cUITextView;
	m_pUiTextView->SetFontType(cFontManager::E_QUEST);	
	m_pUiTextView->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(30, 90, 0));
	m_pUiTextView->SetSize(ST_SIZEF(295, 200));
	m_pUiTextView->SetTextColor(D3DCOLOR_XRGB(0, 0, 0));
	AddChild(m_pUiTextView);

	cUIButton* pButton = new cUIButton;
	pButton->SetButtonImage("./UI/(7)Button/Xbutton_up.png",
		"./UI/(7)Button/Xbutton_over.png",
		"./UI/(7)Button/Xbutton_down.png");
	pButton->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(332, 21, 0));
	pButton->SetTag(2);
	pButton->SetDelegate(this);
	AddChild(pButton);

	pButton = new cUIButton;
	pButton->SetButtonImage("./UI/(7)Button/QuestButton_up_giveup.png",
		"./UI/(7)Button/QuestButton_over_giveup.png",
		"./UI/(7)Button/QuestButton_down_giveup.png");
	pButton->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(266, 417, 0));
	pButton->SetTag(2);
	pButton->SetDelegate(this);
	AddChild(pButton);
}

void cUIIQuest::Update(void)
{
	if (m_bEnd)
	{
		//보상주기 
		cItem* pItem = g_pItemDatabase->GetItem(m_pQuest->GetTakeitem());
		pItem->Setup();
		g_pUnitManager->GetPlayer()->GetInventory()->AddItem(pItem);
		g_pUnitManager->GetPlayer()->GetQuestList()->RemoveQuest(m_pQuest->GetName());
		m_pUIDelegate->OnUIFinished(this);
		return;
	}
	m_pUiTextView->SetText(m_pQuest->GetLore());
	cUIObject::Update();
}

void cUIIQuest::Render(LPD3DXSPRITE pSprite)
{
	cUIObject::Render(m_pSprite);
}


void cUIIQuest::OnClick(cUIButton* pButton)
{
	if (pButton->GetTag() == 2 || pButton->GetTag() == 3)
	{
		m_pUIDelegate->OnUIFinished(this);
	}
}

void cUIIQuest::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case 'L':
		break;
	}

}