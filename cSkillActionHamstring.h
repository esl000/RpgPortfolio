#pragma once

//이동속도 감소
#include "iUnitAction.h"
#include "cEffectSword.h"

class cSkillActionHamstring : public iUnitAction
{
protected:
	cSkinnedMesh*	m_pOwnerMesh;
	cEffectSword*		m_pEffect;
	cUnit*			m_pTarget;
	bool			m_bIsHit;
	bool			m_bSoundCheck;
	SYNTHESIZE(DWORD, m_dwHamstringAnim, HamstringAnim);
public:
	cSkillActionHamstring();
	virtual ~cSkillActionHamstring();

	virtual void Start();
	virtual void Update();
};

