#pragma once

//ав╟щ
#include "iUnitAction.h"
#include "cEffectSword.h"

class cSkillActionMortalStrike : public iUnitAction
{
protected:
	cSkinnedMesh*	m_pOwnerMesh;
	cUnit*			m_pTarget;
	cEffectSword*	m_pEffect;
	bool			m_bIsHit;
	bool			m_bSoundCheck;
	SYNTHESIZE(DWORD, m_dwMortalStrikeAnim, MortalStrikeAnim);
public:
	cSkillActionMortalStrike();
	virtual ~cSkillActionMortalStrike();

	virtual void Start();
	virtual void Update();
};

