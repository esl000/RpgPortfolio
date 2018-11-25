#include "stdafx.h"
#include "cUIPlayerBar.h"

#include "cUIImageView.h"
#include "cUnitPlayer.h"
#include "cItem.h"
#include "cUITextView.h"

cUIPlayerBar::cUIPlayerBar()
	: m_bTest(false)
	, m_fGauge(0.f)
	, m_vPos(D3DXVECTOR3(0, 0, 0))
{
}


cUIPlayerBar::~cUIPlayerBar()
{
}

void cUIPlayerBar::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//Hp(Small)
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pInterface[0] = new cUIImageView;
	m_pInterface[0]->SetTexture(string("./UI/(4)Interface/Interface_3.png"));
	m_pInterface[0]->SetScale(D3DXVECTOR3(1.0f, 1.f, 1.f));
	m_pInterface[0]->SetPosition(D3DXVECTOR3((rc.right / 2) - 609, (rc.bottom / 2) - 303, 0));
	AddChild(m_pInterface[0]);

	//Fury(Small)
	m_pInterface[1] = new cUIImageView;
	m_pInterface[1]->SetTexture(string("./UI/(4)Interface/Interface_4.png"));
	m_pInterface[1]->SetScale(D3DXVECTOR3(0.0f, 1.f, 1.f));
	m_pInterface[1]->SetPosition(D3DXVECTOR3((rc.right / 2) - 609, (rc.bottom / 2) - 292, 0));
	AddChild(m_pInterface[1]);

	//Empty
	m_pInterface[2] = new cUIImageView;
	m_pInterface[2]->SetTexture(string("./UI/(4)Interface/Interface_5.png"));
	m_pInterface[2]->SetPosition(D3DXVECTOR3((rc.right / 2) - 707, (rc.bottom / 2) - 362, 0));
	AddChild(m_pInterface[2]);

	FontData();
}

void cUIPlayerBar::Update()
{
	if (m_pInterface[0])
	{
		m_fGauge = (g_pUnitManager->GetPlayer()->GetCurrentHp()) / g_pUnitManager->GetPlayer()->GetMaxHp();
		m_pInterface[0]->SetScale(D3DXVECTOR3(m_fGauge, 1.f, 1.f));
	}
	
	if (m_pInterface[1])
	{
		m_fGauge = (g_pUnitManager->GetPlayer()->GetCurrentMp()) / g_pUnitManager->GetPlayer()->GetMaxMp();
		m_pInterface[1]->SetScale(D3DXVECTOR3(m_fGauge, 1.f, 1.f));
	}
	cUIObject::Update();
}

void cUIPlayerBar::Render(LPD3DXSPRITE pSprite)
{
	cUIObject::Render(m_pSprite);
}

void cUIPlayerBar::FontData()
{
	cUITextView* pTextView = new cUITextView;
	pTextView->SetText(g_pUnitManager->GetPlayer()->GetName());
	pTextView->SetFontType(cFontManager::E_NAME);
	pTextView->SetPosition(D3DXVECTOR3(m_pInterface[2]->GetPosition().x + 103, m_pInterface[2]->GetPosition().y + 47, 0));
	pTextView->SetSize(ST_SIZEF(120, 250));
	pTextView->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));
	AddChild(pTextView);

}
