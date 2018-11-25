#include "StdAfx.h"
#include "cUITextView.h"


cUITextView::cUITextView(void)
	: m_eFontType(cFontManager::E_DEFAULT)
	, m_dwDT(DT_LEFT | DT_TOP | DT_WORDBREAK)
	, m_dwColor(D3DCOLOR_XRGB(255, 255, 255))
{
}

cUITextView::~cUITextView(void)
{
}

void cUITextView::Render(LPD3DXSPRITE pSprite)
{
	LPD3DXFONT pFont = g_pFontManager->GetFont(m_eFontType);

	RECT rc;
	SetRect(&rc
		, int(m_matWorld._41)
		, int(m_matWorld._42)
		, int(m_matWorld._41 + m_stSize.fWidth)
		, int(m_matWorld._42 + m_stSize.fHeight) );

	pFont->DrawTextA(NULL,
		m_sText.c_str(),
		m_sText.length(),
		&rc,
		m_dwDT,
		m_dwColor);

	cUIObject::Render(pSprite);
}
