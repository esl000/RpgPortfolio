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
	cMessageBox::Setup("MessageBox/MessageBox.png", "����Ʈ ���󼣶�.");
	AddButton(D3DXVECTOR3(490, 3, 0), E_EXIT, "MessageBox/exit_button.png");
	AddButton(D3DXVECTOR3(30, 200, 0), E_OK, "MessageBox/button.png", "����");
	AddButton(D3DXVECTOR3(350, 200, 0), E_NO, "MessageBox/button.png", "����");
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
		FatalAppExit(0, "��");
	}
	else if (pButton->GetButtonType() == E_OK)
	{
		m_sLore = string("����Ʈ ���󼣶�.") + string("\n���� �Ͽ���.");
	}
	else if (pButton->GetButtonType() == E_NO)
	{
		m_sLore = string("����Ʈ ���󼣶�.") + string("\n�ź� �Ͽ���.");
	}
}

