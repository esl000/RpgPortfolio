#pragma once

//주문시전차단 자루치기
#include "iUnitAction.h"
#include "cEffectSword.h"

class cSkillActionPummel : public iUnitAction
{
protected:
	cSkinnedMesh*	m_pOwnerMesh;
	cUnit*			m_pTarget;
	cEffectSword*		m_pEffect;
	bool			m_bIsHit;
	bool			m_bSoundCheck;
	SYNTHESIZE(DWORD, m_dwPummelAnim, PummelAnim);
public:
	cSkillActionPummel();
	virtual ~cSkillActionPummel();

	virtual void Start();
	virtual void Update();
};

