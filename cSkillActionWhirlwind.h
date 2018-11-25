#pragma once

//������ �ٱ�ߵ� ���̵� ������ �������°���
#include "iUnitAction.h"
#include "cEffectSword.h"

class cSkillActionWhirlWind : public iUnitAction
{
protected:
	cSkinnedMesh*		m_pOwnerMesh;
	cUnit*				m_pTarget;
	cEffectSword*		m_pEffect;
	float				m_fTwirlCount;
	bool				m_bIsHit;
	bool				m_bShoundCheck;
	D3DXVECTOR3			m_vDir;
	SYNTHESIZE(DWORD, m_dwWhirlWindAnim, WhirlWindAnim);
public:
	cSkillActionWhirlWind();
	virtual ~cSkillActionWhirlWind();

	virtual void Start();
	virtual void Update();
};

