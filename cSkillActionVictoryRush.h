#pragma once

//���丮����. ��... ������ ������ 20�ʾȿ� ���ݽ�ų ����Ҽ� ����.
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

