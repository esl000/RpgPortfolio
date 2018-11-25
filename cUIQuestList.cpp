#include "stdafx.h"
#include "cUIQuestList.h"
#include "cUITextView.h"
#include "cUIImageView.h"
#include "cUnitCustomNpc.h"
#include "cCustomQuest.h"
#include "cUImanager.h"
#include "cUIButton.h"
#include "cQuestList.h"




cUIQuestList::cUIQuestList()
	: m_pUiImageView(NULL)
	, m_pUiTextView(NULL)
	, m_pList(NULL)
	, m_pCurrentQuest(NULL)
{
	m_eUItype = E_QUEST;
}


cUIQuestList::~cUIQuestList()
{
}

void cUIQuestList::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	D3DXMatrixIdentity(&m_matWorld);


	m_pUiImageView = new cUIImageView;
	m_pUiImageView->SetTexture(string("./UI/(8)Quest/questList.png"));
	m_pUiImageView->SetPosition(D3DXVECTOR3(0, 100, 0));
	//m_pUiImageView->SetPosition(D3DXVECTOR3(0, 0, 0));
	AddChild(m_pUiImageView);

	m_pUiTextView = new cUITextView;
	m_pUiTextView->SetFontType(cFontManager::E_QUEST);
	m_pUiTextView->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(355, 80, 0));
	//m_pUiTextView->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_pUiTextView->SetSize(ST_SIZEF(260, 300));
	AddChild(m_pUiTextView);

	int i = 0;
	for each(auto p in m_pList->m_mapQuest)
	{
		m_vecQuestName.push_back(p.second->GetName());
		cUIButton* pButton = new cUIButton;
		pButton->SetButtonImage("./UI/(7)Button/LineButton_up.png",
			"./UI/(7)Button/LineButton_over.png",
			"./UI/(7)Button/LineButton_down.png");
		pButton->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(25, 80 + (20 * i), 0));
		pButton->SetTag(3 + i);
		pButton->SetDelegate(this);
		AddChild(pButton);

		cUITextView* pText = new cUITextView;
		pText->SetFontType(cFontManager::E_QUEST);
		pText->SetText(p.second->GetName());
		pText->SetPosition(D3DXVECTOR3(10, 0, 0));
		pText->SetSize(ST_SIZEF(285, 15));
		pText->SetTextColor(D3DCOLOR_XRGB(255, 255, 255));
		pButton->AddChild(pText);

		++i;
	}

	cUIButton* pButton = new cUIButton;
	pButton->SetButtonImage("./UI/(7)Button/Xbutton_up.png",
		"./UI/(7)Button/Xbutton_over.png",
		"./UI/(7)Button/Xbutton_down.png");
	pButton->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(657, 16, 0));
	pButton->SetTag(2);
	pButton->SetDelegate(this);
	AddChild(pButton);
}

void cUIQuestList::Update()
{
	//if (m_pQuest != NULL)
	//{
	//	m_pUiTextViewName->SetText(m_pQuest->GetName());
	//	m_pUiTextView->SetText(m_pQuest->GetLore());
	//}
	//else
	//{
	//	m_pUiTextViewName->SetText("");
	//	m_pUiTextView->SetText("");
	//}

	
	cUIObject::Update();
}

void cUIQuestList::Render(LPD3DXSPRITE pSprite)
{
	cUIObject::Render(m_pSprite);
}

void cUIQuestList::OnClick(cUIButton* pButton)
{
	if (pButton->GetTag() > 2)
	{
		m_pCurrentQuest = m_pList->m_mapQuest[m_vecQuestName[pButton->GetTag() - 3]];
		m_pUiTextView->SetText(m_pCurrentQuest->GetLore());
		
		m_pUiTextViewSecond = new cUITextView;
		string sFrontTargetDeath = to_string(m_pCurrentQuest->GetCurrentTargetDeath());
		string sBackTargetDeath = to_string(m_pCurrentQuest->GetTargetDeath());
		string sQuestTargetDeath = sFrontTargetDeath + " / " + sBackTargetDeath;
		m_pUiTextViewSecond->SetText(sQuestTargetDeath);
		m_pUiTextViewSecond->SetFontType(cFontManager::E_QUEST);
		m_pUiTextViewSecond->SetPosition(m_pUiImageView->GetPosition() + D3DXVECTOR3(355, 250, 0));
		m_pUiTextViewSecond->SetSize(ST_SIZEF(260, 300));
		AddChild(m_pUiTextViewSecond);
	}
	else
	{
		m_pUIDelegate->OnUIFinished(this);
		return;
	}
}
