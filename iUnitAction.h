#pragma once

class iUnitAction;
class cUnit;

class iUnitActionDelegate
{
public:
	virtual void OnUnitActionFinish(iUnitAction* pAction) = 0;
};

class iUnitAction : public cObject
{
protected:
	float m_fCurrentTime;
	SYNTHESIZE(cUnit*, m_pOwner, Owner);
	SYNTHESIZE(iUnitActionDelegate*, m_pDelegate, Delegate);
public:
	iUnitAction();
	virtual ~iUnitAction();

	virtual void Start() = 0;
	virtual void Update() = 0;

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

