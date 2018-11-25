#include "stdafx.h"
#include "cMessageQuest.h"

cMessageQuest::cMessageQuest()
{
}


cMessageQuest::~cMessageQuest()
{
}


void cMessageQuest::Setup()
{
	m_vLocalFont = D3DXVECTOR3(30, 40, 0);
	cMessageBox::Setup("MessageBox/MessageBox.png", "Äù½ºÆ® ¼£¶ó¼£¶ó.");
	AddButton(D3DXVECTOR3(490, 3, 0), E_EXIT, "MessageBox/exit_button.png");
	AddButton(D3DXVECTOR3(30, 200, 0), E_OK, "MessageBox/button.png", "¼ö¶ô");
	AddButton(D3DXVECTOR3(350, 200, 0), E_NO, "MessageBox/button.png", "°ÅÀý");
}

void cMessageQuest::Update()
{
	cMessageBox::Update();
}

void cMessageQuest::Render()
{
	cMessageBox::Render();
}

void cMessageQuest::onButtonSelect(cButton* pButton)
{
	if (pButton->GetButtonType() == E_EXIT)
	{
		FatalAppExit(0, "³¡");
	}
	else if (pButton->GetButtonType() == E_OK)
	{
		m_sLore = string("Äù½ºÆ® ¼£¶ó¼£¶ó.") + string("\n¼ö¶ô ÇÏ¿´À½.");
	}
	else if (pButton->GetButtonType() == E_NO)
	{
		m_sLore = string("Äù½ºÆ® ¼£¶ó¼£¶ó.") + string("\n°ÅºÎ ÇÏ¿´À½.");
	}
}

