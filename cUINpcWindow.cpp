#include "stdafx.h"
#include "cUINpcWindow.h"
#include "cUIQuest.h"
#include "cUITextView.h"
#include "cUIImageView.h"
#include "cUnitCustomNpc.h"
#include "cCustomQuest.h"
#include "cUImanager.h"
#include "cUIButton.h"
#include "cUnitCustomNpc.h"
#include "cUnitPlayer.h"

cUINpcWindow::cUINpcWindow()
	: m_pUiImageView(NULL)
	, m_pUiTextView(NULL)
	, m_pNpc(NULL)
{
	m_eUItype = E_MESSAGE;
}


cUINpcWindow::~cUINpcWindow()
{
}

void cUINpcWindow::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	m_pUiImageView = new cUIImageView;
	m_pUiImageView->SetTexture(string("./UI/(8)Quest/npcWindow.png"));
	m_pUiImageView->SetPosition(D3DXVECTOR3(0, 100, 0));
	AddChild(m_pUiImageView);

	m_pUiTextView = new cUITextView;
	m_pUiTextView->SetFontType(cFontManager::E_QUEST);
	m_pUiTextView->SetText(m_pNpc->GetLore());
	m_pUiTextView->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(30, 90, 0));
	m_pUiTextView->SetSize(ST_SIZEF(295, 200));
	m_pUiTextView->SetTextColor(D3DCOLOR_XRGB(0, 0, 0));
	AddChild(m_pUiTextView);

	cUIButton* pButton = new cUIButton;
	pButton->SetButtonImage("./UI/(7)Button/Xbutton_up.png",
		"./UI/(7)Button/Xbutton_over.png",
		"./UI/(7)Button/Xbutton_down.png");
	pButton->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(332, 22, 0));
	pButton->SetTag(2);
	pButton->SetDelegate(this);
	AddChild(pButton);

	pButton = new cUIButton;
	pButton->SetButtonImage("./UI/(7)Button/QuestButton_up_end.png",
		"./UI/(7)Button/QuestButton_over_end.png",
		"./UI/(7)Button/QuestButton_down_end.png");
	pButton->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(24, 420, 0));
	pButton->SetTag(2);
	pButton->SetDelegate(this);
	AddChild(pButton);

	if (m_pNpc->GetPQuest() != NULL && !g_pUnitManager->GetPlayer()->GetCompleteQuest(m_pNpc->GetPQuest()->GetName()))
	{
		pButton = new cUIButton;
		pButton->SetButtonImage("./UI/(7)Button/LineButton_up.png",
			"./UI/(7)Button/LineButton_over.png",
			"./UI/(7)Button/LineButton_down.png");
		pButton->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(24, 300 , 0));
		pButton->SetTag(3);
		pButton->SetDelegate(this);
		AddChild(pButton);

		m_pUiTextView = new cUITextView;
		m_pUiTextView->SetFontType(cFontManager::E_QUEST);
		m_pUiTextView->SetText(m_pNpc->GetPQuest()->GetName());
		m_pUiTextView->SetPosition( D3DXVECTOR3(10, 5, 0));
		m_pUiTextView->SetSize(ST_SIZEF(295, 200));
		m_pUiTextView->SetTextColor(D3DCOLOR_XRGB(0, 0, 0));
		pButton->AddChild(m_pUiTextView);
	}
	//퀘스트 있는대로 버튼에 집어넣기

}

void cUINpcWindow::Update()
{
	cUIObject::Update();
}

void cUINpcWindow::Render(LPD3DXSPRITE pSprite)
{
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	cUIObject::Render(m_pSprite);
}

void cUINpcWindow::OnClick(cUIButton* pButton)
{
	if (pButton->GetTag() == 2 )
	{
		m_pUIDelegate->OnUIFinished(this);
		return;
	}
	else if (pButton->GetTag() == 3)
	{
		cUIQuest* pQuest = new cUIQuest;
		pQuest->SetQuest(m_pNpc->GetPQuest());
		pQuest->SetUp();
		
		g_pUImanager->RegisterUI(pQuest);
		m_pUIDelegate->OnUIFinished(this);
		return;
	}
	//클릭시 이창 끄고 퀘스트창ㅇ열기
}
