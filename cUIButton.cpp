#include "StdAfx.h"
#include "cUIButton.h"

#include "cSceneManager.h"
#include "cGameScene.h"
#include "cLoadingScene.h"
#include "cMapToolScene.h"

cUIButton::cUIButton(void)
	: m_eButtonState(E_NORMAL)
	, m_pDelegate(NULL)
	, m_pGameScene(NULL)
	, m_pLoadingScene(NULL)
	, m_pMapToolScene(NULL)
{
}


cUIButton::~cUIButton(void)
{
	//SAFE_RELEASE(m_pGameScene);
	SAFE_RELEASE(m_pLoadingScene);
}

void cUIButton::Update()
{
	cUIObject::Update();

	RECT rc;
	SetRect(&rc,
		int(m_matWorld._41),
		int(m_matWorld._42),
		int(m_matWorld._41 + m_stSize.fWidth),
		int(m_matWorld._42 + m_stSize.fHeight));


	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (PtInRect(&rc, pt))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (g_pPicking->GetUse(cPicking::E_LEFTCLICK))
			{
				g_pPicking->SetUse(cPicking::E_LEFTCLICK);
				if (m_eButtonState == E_MOVER)
				{
					m_eButtonState = E_SELECTED;
				}
			}
		}
		else
		{
			if (m_eButtonState == E_SELECTED)
			{
				if (m_pDelegate)
				{ 
					m_pDelegate->OnClick(this);
					return;
				}
			}

			m_eButtonState = E_MOVER;
		}
	}
	else
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_eButtonState != E_SELECTED)
			{
				m_eButtonState = E_NORMAL;
			}
		}
		else
		{
			m_eButtonState = E_NORMAL;
		}
	}

	
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	SetRect(&rc, 0, 0, (int)m_stSize.fWidth, (int)m_stSize.fHeight);

	pSprite->SetTransform(&m_matWorld);

	pSprite->Draw(m_aTexture[m_eButtonState],
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}

void cUIButton::SetButtonImage(std::string sNor, std::string sOvr, std::string sSel)
{
	D3DXIMAGE_INFO stImageInfo;
	m_aTexture[E_NORMAL] = g_pTextureManager->GetTexture(sNor, &stImageInfo);
	m_aTexture[E_MOVER] = g_pTextureManager->GetTexture(sOvr, &stImageInfo);
	m_aTexture[E_SELECTED] = g_pTextureManager->GetTexture(sSel, &stImageInfo);

	m_stSize.fWidth = float(stImageInfo.Width);
	m_stSize.fHeight = float(stImageInfo.Height);
}

