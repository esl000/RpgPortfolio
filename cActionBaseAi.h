#pragma once

#include "iUnitAction.h"

class cActionBaseAi : public iUnitAction
	, public iUnitActionDelegate
{
public:
	enum eUnitState
	{
		E_NONE = 0,
		E_STAND,
		E_TARGETMOVE,
		E_POSMOVE,
		E_ATTACK
	};
	
	SYNTHESIZE(DWORD, m_dwWalkAnim, WalkAnim);
	SYNTHESIZE(DWORD, m_dwAttackAnim, AttackAnim);
	SYNTHESIZE(D3DXVECTOR3, m_vOrgPos, OrgPos);
	SYNTHESIZE(D3DXVECTOR3, m_vOrgDir, OrgDir);
	SYNTHESIZE(bool, m_isDeffense, Deffense);

protected:
	cUnit* m_pTarget;
	eUnitState m_eCurrentAct;
	iUnitAction* m_pCurrentAction;
public:
	cActionBaseAi();
	~cActionBaseAi();

	virtual void Start() override;
	virtual void Update() override;

	virtual void BaseAi();
	virtual void DefenseAi();

	virtual void OnUnitActionFinish(iUnitAction* pAction) override;
};

