#include "stdafx.h"
#include "cDamageText.h"
#include "cBillBoarding.h"
#include "cUITextView.h"

cDamageText::cDamageText()
	: m_pFont(NULL)
	, m_fPlusY(-30.f)
	, m_sStr("")
	, m_dwColor(0)
		//m_pText(NULL)
{
}


cDamageText::~cDamageText()
{
	SAFE_RELEASE(m_pFont);
}

void cDamageText::Setup(std::string str, eColorState eColor)
{
	m_sStr = str;

	if (eColor == E_WHITE)
		m_dwColor = D3DCOLOR_XRGB(255, 255, 255);
	else if (eColor == E_YELLOW)
		m_dwColor = D3DCOLOR_XRGB(255, 255, 0);
	else if (eColor == E_RED)
		m_dwColor = D3DCOLOR_XRGB(255, 0, 0);

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 50;
	fd.Width = 25;
	//	fd.Weight = FW_MEDIUM;
	fd.Weight = FW_BLACK;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	//strcpy_s(fd.FaceName, "-2002");	//글꼴 스타일
	AddFontResource("K_Damage.ttf");
	strcpy_s(fd.FaceName, "K_Damage");
	//			cout << "얌마" << endl;
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
	//m_pText = new cUITextView;
	//m_pText->SetFontType(cFontManager::E_NAME);
	//m_pText->SetText(str);
	//m_pText->SetPosition(D3DXVECTOR3(10, 0, 0));
	//m_pText->SetSize(ST_SIZEF(30, 30));
	//m_pText->SetTextColor(D3DCOLOR_XRGB(255, 255, 255));	
}

void cDamageText::Update()
{	
	m_fPlusY -= 150.f * g_pTimeManager->GetElapsedTime();
}

void cDamageText::Render()
{	
	D3DXMATRIXA16 mat, matView, matProj, matWorld;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	mat = matView * matProj;

	D3DXVECTOR3 vec = m_vPosition;
	D3DXVec3TransformCoord(&vec, &vec, &mat);

	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	vec.x = (vp.Width / 2.f + 1) * vec.x + vp.Width / 2.f;
	vec.y = (1 - vp.Height / 2.f) * vec.y + vp.Height / 2.f;

	vec.y += m_fPlusY;

	RECT rc;
	SetRect(&rc
		, int(vec.x)
		, int(vec.y)
		, int(vec.x + 1)
		, int(vec.y + 1));

	m_pFont->DrawTextA(NULL,
		m_sStr.c_str(),
		m_sStr.length(),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		m_dwColor);

}
