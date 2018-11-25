#pragma once

#include "iUnitAction.h"
#include "cEffectSword.h"

class cSkillActionBladeStorm : public iUnitAction
{
protected:
	cSkinnedMesh*		m_pOwnerMesh;
	cEffectSword*		m_pEffect;
	cUnit*				m_pTarget;
	float				m_fTwirlCount;
	bool				m_bIsHit;
	bool				m_bSkillSound;
	D3DXVECTOR3			m_vDir;
	SYNTHESIZE(DWORD, m_dwStormAnim, StormAnim);
public:
	cSkillActionBladeStorm();
	virtual ~cSkillActionBladeStorm();

	virtual void Start();
	virtual void Update();
};

