#include "stdafx.h"
#include "cSkillAd.h"

#include "cUIImageView.h"

cSkillAd::cSkillAd()
	: m_sName("")
	, m_nKey(48)
	, m_eSkillType(E_NONE)
	, m_pImageView(NULL)
{
}


cSkillAd::~cSkillAd()
{
	SAFE_RELEASE(m_pImageView);
}

void cSkillAd::Setup()
{
	m_pImageView = new cUIImageView;
}

void cSkillAd::Update()
{
	if (m_pImageView)
		m_pImageView->Update();
}

void cSkillAd::Render(LPD3DXSPRITE pSprite)
{
	if (m_pImageView)
		m_pImageView->Render(pSprite);
}
