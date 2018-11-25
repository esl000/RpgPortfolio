#pragma once

//빅토리러쉬. 음... 전투중 끝나고 20초안에 공격스킬 사용할수 있음.
#include "iUnitAction.h"
#include "cEffectSword.h"

class cSkillActionVictoryRush : public iUnitAction
{
protected:
	cSkinnedMesh*	m_pOwnerMesh;
	cUnit*			m_pTarget;
	cEffectSword*	m_pEffect;
	bool			m_bIsHit;
	bool			m_bSoundCheck;
	SYNTHESIZE(DWORD, m_dwVictoryRushAnim, VictoryRushAnim);
public:
	cSkillActionVictoryRush();
	virtual ~cSkillActionVictoryRush();

	virtual void Start();
	virtual void Update();
};

