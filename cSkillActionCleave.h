#pragma once

#include "iUnitAction.h"

class cSkillActionCleave : public iUnitAction
{
protected:
	cSkinnedMesh*		m_pOwnerMesh;
	cUnit*				m_pTarget;
	bool				m_bReload;
	bool				m_bSoundCheck;
	bool				m_bIsEffect;
	SYNTHESIZE(DWORD, m_dwAttackAnim, AttackAnim);
	SYNTHESIZE(float, m_fActionExitTime, ActionExitTime);

public:
	cSkillActionCleave();
	virtual ~cSkillActionCleave();

	virtual void Start() override;
	virtual void Update() override;
};

