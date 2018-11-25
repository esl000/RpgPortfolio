#pragma once

#include "iUnitAction.h"

class cPlayerActionAttack : public iUnitAction
{
protected:
	cSkinnedMesh*	m_pOwnerMesh;
	cUnit*			m_pTarget;
	bool			m_bReload;
	bool			m_bSoundCheck;
	SYNTHESIZE(DWORD, m_dwAttackAnim, AttackAnim);
public:
	cPlayerActionAttack();
	virtual ~cPlayerActionAttack();

	virtual void Start() override;
	virtual void Update() override;
};

