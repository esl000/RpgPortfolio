#pragma once
#include "iUnitAction.h"

class cUnitPlayer;

class cPlayerNormalAction : public iUnitAction
	, public iUnitActionDelegate
{
public:
	enum eNormalState
	{
		E_NONE,
		E_STAND,
		E_FRONTMOVE,
		E_BACKMOVE,
		E_TARGETMOVE,
		E_POSMOVE,
		E_KEYMOVE,
		E_ATTACK
	};

protected:

	cUnit* m_pTarget;
	cUnitPlayer* m_pPlayer;

	bool m_isAction;

	SYNTHESIZE(eNormalState, m_eCurrentAction, CurrentActionType);
	SYNTHESIZE(iUnitAction*, m_pCurrentAction, CurrentAction);
	SYNTHESIZE(DWORD, m_dwWalkAnim, WalkAnim);
	SYNTHESIZE(D3DXVECTOR3, m_vOrgPos, OrgPos);
public:
	cPlayerNormalAction();
	virtual  ~cPlayerNormalAction();

	virtual void Start() override;
	virtual void Update() override;

	virtual void OnUnitActionFinish(iUnitAction* pAction);

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

