#include "stdafx.h"
#include "cSkillInven.h"

#include "cUIImageView.h"
#include "cSkillAd.h"

cSkillInven::cSkillInven()
{
}

cSkillInven::~cSkillInven()
{
	for (int i = 0; i < SKILLINVEN; ++i)
	{
		SAFE_RELEASE(m_pSkillInven[i]);
	}
}

void cSkillInven::Setup()
{
	for (int i = 0; i < SKILLINVEN; ++i)
	{
		if (m_pSkillInven[i])
		{
			m_pSkillInven[i] = NULL;
		}
	}

	for (int i = 0; i < SKILLINVEN; ++i)
	{
		cSkillAd* pSkill = new cSkillAd;
		//pSkill->SetName("E_SKILL1");
		cSkillAd::eSkillType eSkillType = SkillType(i);
		pSkill->SetSkillType(eSkillType);
		pSkill->SetImageView(new cUIImageView);
		string szData = SkillImage(i);
		pSkill->GetImageView()->SetTexture(szData);
		pSkill->GetImageView()->SetScale(D3DXVECTOR3(0.62f, 0.62f, 1.f));
		pSkill->SetKey(49 + i);
		AddSkill(pSkill);
	}
}

void cSkillInven::Update()
{
	for (int i = 0; i < SKILLINVEN; ++i)
	{
		if (m_pSkillInven[i])
		{
			m_pSkillInven[i]->SetKey(49 + i);
			m_pSkillInven[i]->Update();
		}
	}
}

void cSkillInven::Render(LPD3DXSPRITE pSprite)
{
	for (int i = 0; i < SKILLINVEN; ++i)
	{
		if (m_pSkillInven[i])
		{
			m_pSkillInven[i]->Render(pSprite);
		}
	}
}

cSkillAd* cSkillInven::GetSkill(int x)
{
	return m_pSkillInven[x];
}

cSkillAd* cSkillInven::GetSkill(cSkillAd::eSkillType eType)
{
	for (int i = 0; i < SKILLINVEN; ++i)
	{
		if (m_pSkillInven[i] && m_pSkillInven[i]->GetSkillType() == eType)
		{
			return m_pSkillInven[i];
		}
	}
	return NULL;
}

void cSkillInven::AddSkill(cSkillAd* pSkill)
{
	for (int i = 0; i < SKILLINVEN; ++i)
	{
		if (!m_pSkillInven[i])
		{
			m_pSkillInven[i] = pSkill;
			return;
		}
	}
}

void cSkillInven::AddSkill(cSkillAd* pSkill, int x)
{
	m_pSkillInven[x] = pSkill;
}

//스킬 이미지 테스트
string cSkillInven::SkillImage(int nData)
{
	string szData;
	switch (nData)
	{
	case 0:
		szData = string("./UI/(9)Skill/2.png");
		break;
	case 1:
		szData = string("./UI/(9)Skill/4.png");
		break;
	case 2:
		szData = string("./UI/(9)Skill/5.png");
		break;
	case 3:
		szData = string("./UI/(9)Skill/3.png");
		break;
	case 4:
		szData = string("./UI/(9)Skill/7.png");
		break;
	case 5:
		szData = string("./UI/(9)Skill/8.png");
		break;
	case 6:
		szData = string("./UI/(9)Skill/9.png");
		break;
	case 7:
		szData = string("./UI/(9)Skill/6.png");
		break;
	case 8:
		szData = string("./UI/(9)Skill/1.png");
		break;
	}
	return szData;
}

//스킬 테스트
cSkillAd::eSkillType cSkillInven::SkillType(int nData)
{
	cSkillAd::eSkillType SkillType;
	switch (nData)
	{
	case 0:
		SkillType = cSkillAd::E_SKILL1;
		break;
	case 1:
		SkillType = cSkillAd::E_SKILL2;
		break;
	case 2:
		SkillType = cSkillAd::E_SKILL3;
		break;
	case 3:
		SkillType = cSkillAd::E_SKILL4;
		break;
	case 4:
		SkillType = cSkillAd::E_SKILL5;
		break;
	case 5:
		SkillType = cSkillAd::E_SKILL6;
		break;
	case 6:
		SkillType = cSkillAd::E_SKILL7;
		break;
	case 7:
		SkillType = cSkillAd::E_SKILL8;
		break;
	case 8:
		SkillType = cSkillAd::E_SKILL9;
		break;
	}
	return SkillType;
}