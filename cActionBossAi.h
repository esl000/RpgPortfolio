#pragma once

#include "iUnitAction.h"

class cActionBossAi : public iUnitAction
	, public iUnitActionDelegate
{
public:
	enum eBossState
	{
		E_NONE = 0,
		E_SLEEP,
		E_STAND,
		E_TARGETMOVE,
		E_POSMOVE,
		E_ATTACK,
		E_SKILL
	};

	SYNTHESIZE(DWORD, m_dwWalkAnim, WalkAnim);
	SYNTHESIZE(DWORD, m_dwAttackAnim, AttackAnim);
	SYNTHESIZE(D3DXVECTOR3, m_vOrgPos, OrgPos);
	SYNTHESIZE(D3DXVECTOR3, m_vOrgDir, OrgDir);

	SYNTHESIZE(bool, m_isDefense, Deffense);
	SYNTHESIZE(bool, m_isSleep, IsSleep);

	cUnit* m_pTarget;
	eBossState m_eCurrentAct;
	iUnitAction* m_pCurrentAction;

	float m_nSkillFireTime[2];
	float m_nSkillCurrentTime[2];
public:
	cActionBossAi();
	virtual ~cActionBossAi();

	virtual void Start() override;
	virtual void Update() override;

	void SleepAi();
	void BaseAi();
	void DefenceAi();

	virtual void OnUnitActionFinish(iUnitAction* pAction) override;
};

