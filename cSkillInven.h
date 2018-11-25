#pragma once
#include "cUIObject.h"
#include "cSkillAd.h"

class cSkillAd; 

class cSkillInven :
	public cUIObject
{		
private:
	cSkillAd*			m_pSkillInven[SKILLINVEN];
public:
	cSkillInven();
	virtual ~cSkillInven();
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	cSkillAd* GetSkill(int x);
	cSkillAd* GetSkill(cSkillAd::eSkillType eType);
	void AddSkill(cSkillAd* pSkill);
	void AddSkill(cSkillAd* pSkill, int x);
	cSkillAd::eSkillType SkillType(int nData);
	string SkillImage(int nData);
};


