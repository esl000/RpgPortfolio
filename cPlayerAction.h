#pragma once

#include "iUnitAction.h"

class cUnitPlayer;

class cPlayerAction : public iUnitAction
	, public iUnitActionDelegate
{
public:

	enum ePlayerState
	{
		E_NORMAL,
		E_BATTLE
	};

protected:

	bool	        m_isClick;

	ePlayerState m_eCurrentAction;
	iUnitAction* m_pCurrentAction;
	cUnitPlayer* m_pPlayer;
public:
	cPlayerAction();
	virtual ~cPlayerAction();

	virtual void Start() override;
	virtual void Update() override;

	virtual void Picking();

	virtual void OnUnitActionFinish(iUnitAction* pAction);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

