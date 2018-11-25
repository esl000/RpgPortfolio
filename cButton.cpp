#include "stdafx.h"
#include "cButton.h"


cButton::cButton()
	: m_pButton(NULL)
	, m_pButtonSelect(NULL)
	, m_pSprite(NULL)
	, m_isClick(false)
	, m_dButtonType(0)
	, m_eButtonState(E_NONE)
	, m_pFont(NULL)
	, m_vLocalFont(30, 8, 0)
{
	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));
}


cButton::~cButton()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pFont);
}

void cButton::Setup(DWORD dButtonType, char* szFullPath, char* szLore)
{

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	if (szFullPath)
	{
		g_pTextureManager->GetSpriteTexture(&m_pButton, &m_stImageInfo, szFullPath);
	}

	if (szLore)
	{
		m_sButtonLore = szLore;
		D3DXFONT_DESC fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
		fd.Height = 15;
		fd.Width = 8;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		strcpy_s(fd.FaceName, "굴림체"); //글꼴 스타일
		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
	}

	SetRect(&m_stBoundingBox, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
	m_dButtonType = dButtonType;
}

void cButton::Update()
{

	if (PtInRect(&m_stBoundingBox, g_ptMouse))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_eButtonState == E_ACTIVE)
				m_eButtonState = E_PUSH;
		}
		else
		{
			if (m_eButtonState == E_PUSH)
			{
				m_pButtonSelect->onButtonSelect(this);
				m_eButtonState = E_ACTIVE;
			}

			if (m_eButtonState != E_PUSH)
				m_eButtonState = E_ACTIVE;
		}
	}
	else
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_eButtonState != E_PUSH)
				m_eButtonState = E_NONE;
		}
		else
		{
			m_eButtonState = E_NONE;
		}
	}

	m_vPosition = m_vLocalPos + m_vParentPos;
	SetRect(&m_stBoundingBox, m_vPosition.x, m_vPosition.y, m_vPosition.x + m_stImageInfo.Width, m_vPosition.y + m_stImageInfo.Height);
}

D3DCOLOR cButton::GetColor()
{
	switch (m_eButtonState)
	{
	case E_NONE:
		return D3DCOLOR_XRGB(200, 200, 200);
		break;
	case E_ACTIVE:
		return D3DCOLOR_XRGB(255, 255, 255);
		break;
	case E_PUSH:
		return D3DCOLOR_XRGB(140, 140, 140);
		break;
	}
}

void cButton::Render()
{
	m_vPosition.z = 0;
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	//D3DXMATRIXA16 matT;
	//D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, 0);
	//m_pSprite->SetTransform(&matT);
	RECT rc;
	SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);

	m_pSprite->Draw(m_pButton,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&m_vPosition,
		GetColor());

	m_pSprite->End();

	if (m_pFont)
	{
		D3DXVECTOR3 vWorldPos = m_vLocalFont + m_vPosition;

		RECT rc;
		SetRect(&rc, vWorldPos.x, vWorldPos.y, vWorldPos.x + 20, vWorldPos.y + 5);
		m_pFont->DrawTextA(NULL,
			m_sButtonLore.c_str(),
			strlen(m_sButtonLore.c_str()),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255));
	}
}
