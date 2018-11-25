#pragma once

#include "iUnitAction.h"
#include "cEffectTrajectory.h"

class cSkillActionCharge : public iUnitAction
{
protected:
	cSkinnedMesh*		m_pOwnerMesh;
	cEffectTrajectory*	m_pEffect;
	cUnit*				m_pTarget;
	SYNTHESIZE(DWORD, m_dwRushAnim, RushAnim);
public:
	cSkillActionCharge();
	virtual ~cSkillActionCharge();

	virtual void Start();
	virtual void Update();
};

