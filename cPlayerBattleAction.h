#pragma once

#include "iUnitAction.h"

class cUnitPlayer;

class cPlayerBattleAction : public iUnitAction
	, public iUnitActionDelegate
{
public:
	enum  eBattleState
	{
		E_NONE,
		E_STAND,
		E_FRONTMOVE,
		E_BACKMOVE,
		E_POSMOVE,
		E_ATTACK,
		E_HIT,
		E_SKILL
	};
protected:
	cUnit* m_pTarget;
	cUnitPlayer* m_pPlayer;

	bool m_bSkillOn[12];
	int m_nCoolTime[12];
	SYNTHESIZE(eBattleState, m_eCurrentAction, CurrentActionType);
	SYNTHESIZE(iUnitAction*, m_pCurrentAction, CurrentAction);
public:
	cPlayerBattleAction();
	virtual ~cPlayerBattleAction();

	virtual void Start() override;
	virtual void Update() override;

	virtual void OnUnitActionFinish(iUnitAction* pAction);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

