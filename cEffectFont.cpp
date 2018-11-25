#include "stdafx.h"
#include "cEffectFont.h"

cEffectFont::cEffectFont()
		:m_pPont(NULL)
		, m_nDamage(0)	
{
	m_fMaxTime = 2.0f;
}


cEffectFont::~cEffectFont()
{
	SAFE_RELEASE(m_pPont);
}

void cEffectFont::Setup()
{	
	char buff[1024] = { NULL };
	sprintf_s(buff, "%d", m_nDamage);
	string str = buff;
		
	m_pPont = new cDamageText;
	if (m_eFontState == E_BASIC)
	{
		if (m_pUnit->GetUnitType() == cUnit::E_MONSTER)
			m_pPont->Setup(str, cDamageText::E_WHITE);
		else
			m_pPont->Setup(str, cDamageText::E_RED);
	}
	else
	{
		m_pPont->Setup(str, cDamageText::E_YELLOW);
	}
}

void cEffectFont::Update()
{
	D3DXVECTOR3 vec = m_pUnit->GetPosition() + 0.5f * m_pUnit->GetDirection();

	m_pPont->SetPosition(vec);
	m_pPont->Update();

	m_fCurrentTime += g_pTimeManager->GetElapsedTime();
	if (m_fCurrentTime > m_fMaxTime)
	{
		m_pDelegate->OnEffectFinish(this);
		return;
	}
}

void cEffectFont::Render()
{
	m_pPont->Render();
}
