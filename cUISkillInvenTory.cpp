#include "stdafx.h"
#include "cUISkillInvenTory.h"

#include "cUIImageView.h"
#include "cUnitPlayer.h"
#include "cSkillInven.h"

cUISkillInvenTory::cUISkillInvenTory()
	: m_bSkillDrag(false)
	, m_pSkillInven(false)
{
}


cUISkillInvenTory::~cUISkillInvenTory()
{
	SAFE_RELEASE(m_pSkillInven);
}

void cUISkillInvenTory::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//InterfaceExp(Big)
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pInterface[0] = new cUIImageView;
	m_pInterface[0]->SetTexture(string("./UI/(4)Interface/Interface_0.png"));
	m_pInterface[0]->SetScale(D3DXVECTOR3(0.f, 1.f, 1.f));
	m_pInterface[0]->SetPosition(D3DXVECTOR3((rc.right / 2) - 382, (rc.bottom / 2) + 304, 0));
	AddChild(m_pInterface[0]);

	//Interface(Empty) 
	m_pInterface[1] = new cUIImageView;
	m_pInterface[1]->SetTexture(string("./UI/(4)Interface/Interface_1.png"));
	m_pInterface[1]->SetPosition(D3DXVECTOR3((rc.right / 2) - 490, (rc.bottom / 2) + 252, 0));
	AddChild(m_pInterface[1]);

	//Skill
	m_pSkillInven = g_pUnitManager->GetPlayer()->GetSkillInven();

	int X = 0;
	for (int i = 0; i < SKILLINVEN; ++i)
	{
		if (i < 4)
		{
			X = (46 * i);
		}
		else
		{
			X = ((46 * i) - i);
		}
		m_vPos.x = (m_pInterface[1]->GetPosition().x + 108) + X;
		m_vPos.y = (m_pInterface[1]->GetPosition().y + 68);

		SetRect(&m_rcSlot[i], int(((m_matWorld._41 + m_vPos.x))),
			int((m_matWorld._42 + m_vPos.y)),
			int((m_matWorld._41 + m_vPos.x + 38)),
			int((m_matWorld._42 + m_vPos.y + 35)));
	}
}
void cUISkillInvenTory::Update()
{


	if (m_pInterface[0])
	{
		//m_fGauge = (g_pUnitManager->GetPlayer()->GetCurrentExp()) / g_pUnitManager->GetPlayer()->GetMaxExp();
		//m_pInterface[0]->SetScale(D3DXVECTOR3(m_fGauge, 1.f, 1.f));
	}

	//Test
	m_pSkillInven->Update();
	for (int i = 0; i < SKILLINVEN; ++i)
	{
		if (m_pSkillInven->GetSkill(i)
			&& !(m_pCurrentSkill && i == m_aCurrentSkill[0]))
		{
			m_pSkillInven->GetSkill(i)->GetImageView()->SetPosition(
				D3DXVECTOR3(m_rcSlot[i].left, m_rcSlot[i].top, 0));
		}
	}
	InterfaceDrag();
	cUIObject::Update();
}
void cUISkillInvenTory::Render(LPD3DXSPRITE pSprite)
{
	cUIObject::Render(m_pSprite);
	m_pSkillInven->Render(m_pSprite);
}

void cUISkillInvenTory::InterfaceFont()
{
	D3DXFONT_DESC fd;
	ZeroMemory(m_sNameData, sizeof(m_sNameData));
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 12;
	fd.Width = 10;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	AddFontResource("umberto.ttf");
	strcpy_s(fd.FaceName, "umberto");
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
}

void cUISkillInvenTory::InterfaceDrag()
{

	if ((GetKeyState(VK_RBUTTON) & 0x8000))
	{
		if (!m_bSkillDrag)
		{
			for (int i = 0; i < SKILLINVEN; ++i)
			{
				if (m_pSkillInven->GetSkill(i) && PtInRect(&m_rcSlot[i], g_ptMouse))
				{
					m_bSkillDrag = true;
					m_aCurrentSkill[0] = i;
					m_pCurrentSkill = m_pSkillInven->GetSkill(i);
					return;
				}
			}
		}
	}
	else
	{
		if (m_bSkillDrag)
		{
			m_bSkillDrag = false;

			for (int i = 0; i < SKILLINVEN; ++i)
			{
				if (PtInRect(&m_rcSlot[i], g_ptMouse))
				{
					cSkillAd* pTempSkill = NULL;
					pTempSkill = m_pSkillInven->GetSkill(i);
					m_pSkillInven->AddSkill(m_pCurrentSkill, i);
					m_pSkillInven->AddSkill(pTempSkill, m_aCurrentSkill[0]);
					if (m_pCurrentSkill)
					{
						m_pCurrentSkill->GetImageView()->SetPosition(D3DXVECTOR3(m_rcSlot[i].left, m_rcSlot[i].top, 0));
					}
					if (pTempSkill)
					{
						pTempSkill->GetImageView()->SetPosition(D3DXVECTOR3(m_rcSlot[m_aCurrentSkill[0]].left, m_rcSlot[m_aCurrentSkill[0]].top, 0));
					}
					m_pCurrentSkill = NULL;
					return;
				}

				if (m_pCurrentSkill)
				{
					m_pCurrentSkill->GetImageView()->SetPosition(D3DXVECTOR3(m_rcSlot[m_aCurrentSkill[0]].left, m_rcSlot[m_aCurrentSkill[0]].top, 0));
				}
			}
		}
	}


	if (m_bSkillDrag)
	{
		if (m_pCurrentSkill)
		{
			m_pCurrentSkill->GetImageView()->SetPosition(D3DXVECTOR3(g_ptMouse.x, g_ptMouse.y, 0));
		}
		else
		{
			m_aCurrentSkill[0] = 0;
			m_pCurrentSkill = NULL;
		}
	}
}
