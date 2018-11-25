#pragma once

#include "iUnitAction.h"

class cActionAttack : public iUnitAction
{
protected:
	cSkinnedMesh*		m_pOwnerMesh;
	cUnit*				m_pTarget;
	bool				m_bReload;
	bool				m_bSoundCheck;
	SYNTHESIZE(DWORD, m_dwAttackAnim, AttackAnim);

public:
	cActionAttack();
	virtual ~cActionAttack();

	virtual void Start() override;
	virtual void Update() override;
};

