#pragma once

//ÃµµÕº­¶ô !!!
#include "iUnitAction.h"

class cSkillActionThunderClap : public iUnitAction
{
protected:
	cSkinnedMesh*	m_pOwnerMesh;
	cUnit*			m_pTarget;
	bool			m_bIsHit;
	bool			m_bIsEffect;
	SYNTHESIZE(DWORD, m_dwThunderClapAnim, ThunderClapAnim);
public:
	cSkillActionThunderClap();
	virtual ~cSkillActionThunderClap();

	virtual void Start();
	virtual void Update();
};

