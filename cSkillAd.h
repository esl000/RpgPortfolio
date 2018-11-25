#pragma once
#include "cUIObject.h"
#include "cUIImageView.h"


class cSkillAd :
	public cUIObject
{
public:
	enum eSkillType
	{
		E_SKILL1,
		E_SKILL2,
		E_SKILL3,
		E_SKILL4,
		E_SKILL5,
		E_SKILL6,
		E_SKILL7,
		E_SKILL8,
		E_SKILL9,
		E_NONE
	};
	SYNTHESIZE(string, m_sName, Name);
	SYNTHESIZE(eSkillType, m_eSkillType, SkillType);
	SYNTHESIZE(cUIImageView*, m_pImageView, ImageView);
	SYNTHESIZE(string, m_sImageName, ImageName);
	SYNTHESIZE(int, m_nKey, Key);

public:
	cSkillAd();
	virtual ~cSkillAd();
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
};

