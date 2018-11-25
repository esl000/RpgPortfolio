#include "stdafx.h"
#include "cUIMonsterBar.h"
#include "cUITextView.h"
#include "cUIImageView.h"
#include "cUnit.h"
#include "cUIMainView.h"

cUIMonsterBar::cUIMonsterBar()
	: m_pOwner(NULL)
	, m_pImage(NULL)
	, m_pText(NULL)
{
	m_eUItype = E_HPBAR;
}


cUIMonsterBar::~cUIMonsterBar()
{
}

void cUIMonsterBar::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_pMonsterImage = new cUIImageView;
	m_pMonsterImage->SetTexture("./UI/(4)Interface/Interface_14.png");
	m_pMonsterImage->SetPosition(D3DXVECTOR3((rc.right / 2) - 396, (rc.bottom / 2) - 362, 0));
	AddChild(m_pMonsterImage);

	//36, 63
	m_pImage = new cUIImageView;
	m_pImage->SetTexture("./UI/(4)Interface/Interface_3.png");
	m_pImage->SetScale(D3DXVECTOR3(1.0f, 1.f, 1.f));
	m_pImage->SetPosition(D3DXVECTOR3(m_pMonsterImage->GetPosition().x + 31, m_pMonsterImage->GetPosition().y + 58, 0));
	AddChild(m_pImage);

	m_pText = new cUITextView;
	m_pText->SetFontType(cFontManager::E_NAME);
	m_pText->SetPosition(D3DXVECTOR3(m_pMonsterImage->GetPosition().x + 73, m_pMonsterImage->GetPosition().y + 47, 0));
	m_pText->SetSize(ST_SIZEF(120, 250));
	m_pText->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));
	AddChild(m_pText);
}

void cUIMonsterBar::Update()
{
	float fGauge = m_pOwner->GetCurrentHp() / m_pOwner->GetMaxHp();
	m_pImage->SetScale(D3DXVECTOR3(fGauge, 1.f, 1.f));
	m_pMonsterImage->SetTexture(m_pOwner->GetmonsterName());
	m_pText->SetText(m_pOwner->GetName());

	cUIObject::Update();
}

void cUIMonsterBar::Render(LPD3DXSPRITE pSprite)
{ 
	cUIObject::Render(m_pSprite);
}