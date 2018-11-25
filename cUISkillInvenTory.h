#pragma once
#include "cUIObject.h"

#define COUNT2 9

#include "cSkillAd.h"

class cUIImageView;
class cSkillAd;
class cSkillInven;

class cUISkillInvenTory :
	public cUIObject
{
private:
	RECT				m_InvenToryRect;
	POINT				m_ptInvenToryPos;
	POINT				m_ptMouseCenter;

	RECT				m_rcSlot[SKILLINVEN];
	cUIImageView*		m_pInterface[2];
	cUIImageView*		m_pSkill[SKILLINVEN];
	LPD3DXFONT			m_pFont;
	bool				m_bSkillDrag;
	DWORD 				m_aCurrentSkill[1];
	cSkillAd*			m_pCurrentSkill; 

	SYNTHESIZE(cSkillInven*, m_pSkillInven, SkillInven);
	SYNTHESIZE(char, m_sNameData[128], NameData);
	SYNTHESIZE(float, m_fGauge, Gauge);
	SYNTHESIZE(D3DXVECTOR3, m_vPos, vPos);
public:
	cUISkillInvenTory();
	virtual ~cUISkillInvenTory();
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	void InterfaceFont();
	void InterfaceDrag();
};

