#include "stdafx.h"
#include "cMessageBox.h"


cMessageBox::cMessageBox()
	: m_pMessage(NULL)
	, m_pSprite(NULL)
	, m_pFont(NULL)
	, m_isClick(false)
	, m_vLocalFont(0, 0, 0)
{
}


cMessageBox::~cMessageBox()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pFont);
	for each(auto p in m_vecButton)
	{
		SAFE_RELEASE(p);
	}
}

void cMessageBox::AddButton(D3DXVECTOR3 vLocalPos, DWORD dIndex, char* szFullPath, char* szLore)
{
	cButton* button = new cButton;
	button->Setup(dIndex, szFullPath, szLore);
	button->SetLocalPos(vLocalPos);
	button->SetButtonSelect(this);
	m_vecButton.push_back(button);
}

void cMessageBox::Setup(char* szFullPath /*= NULL*/, char* szLore /*= NULL*/)
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	if (szFullPath)
	{
		g_pTextureManager->GetSpriteTexture(&m_pMessage, &m_stImageInfo, szFullPath);
	}

	if (szLore)
	{
		m_sLore = szLore;
		D3DXFONT_DESC fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
		fd.Height = 20;
		fd.Width = 10;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		strcpy_s(fd.FaceName, "굴림체"); //글꼴 스타일
		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
	}

	SetRect(&m_stBoundingBox, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
	SetRect(&m_actionBox, 0, 0, m_stImageInfo.Width, 30);
}

void cMessageBox::Update()
{
	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		if (PtInRect(&m_actionBox, g_ptMouse))
		{
			m_isClick = true;
		}
	}

	else if (m_isClick)
	{
		m_isClick = false;
	}

	if (m_isClick)
	{
		float fDeltaX = g_ptMouse.x - m_ptPrev.x;
		float fDeltaY = g_ptMouse.y - m_ptPrev.y;
		m_vPosition.x += fDeltaX;
		m_vPosition.y += fDeltaY;
	}

	SetRect(&m_actionBox, m_vPosition.x, m_vPosition.y, m_vPosition.x + m_stImageInfo.Width, m_vPosition.y + 30);
	for each(auto p in m_vecButton)
	{
		p->SetParentPos(m_vPosition);
		p->Update();
	}

	m_ptPrev = g_ptMouse;
}

void cMessageBox::Render()
{
	m_vPosition.z = 1;
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);

	m_pSprite->Draw(m_pMessage,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&m_vPosition,
		D3DCOLOR_XRGB(255, 255, 255));

	m_pSprite->End();

	if (m_pFont)
	{
		D3DXVECTOR3 vWorldPos = m_vLocalFont + m_vPosition;
		RECT rc;
		SetRect(&rc, vWorldPos.x, vWorldPos.y, vWorldPos.x + 40, vWorldPos.y + 20);
		m_pFont->DrawTextA(NULL,
			m_sLore.c_str(),
			strlen(m_sLore.c_str()),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(160, 160, 160));
	}

	for each(auto p in m_vecButton)
	{
		p->Render();
	}
}

void cMessageBox::onButtonSelect(cButton* pButton)
{

}
