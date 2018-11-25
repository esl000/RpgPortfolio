#pragma once

#include "iUnitAction.h"
#include "cEffectSword.h"

class cSkillActionExecute : public iUnitAction
{
protected:
	cSkinnedMesh*	m_pOwnerMesh;
	cUnit*			m_pTarget;
	cEffectSword*	m_pEffect;
	bool			m_bIsHit;
	bool			m_bSoundCheck;

	SYNTHESIZE(DWORD, m_ExecuteAnim, ExecutAnim);
public:
	cSkillActionExecute();
	virtual ~cSkillActionExecute();

	virtual void Start();
	virtual void Update();
};

