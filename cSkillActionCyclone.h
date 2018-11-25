#pragma once

#include "iUnitAction.h"

class cSkillActionCyclone : public iUnitAction
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
	cSkillActionCyclone();
	virtual ~cSkillActionCyclone();

	virtual void Start() override;
	virtual void Update() override;
};

