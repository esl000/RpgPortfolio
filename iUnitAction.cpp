#include "stdafx.h"
#include "iUnitAction.h"
#include "cUnit.h"


iUnitAction::iUnitAction()
	: m_pOwner(NULL)
	, m_pDelegate(NULL)
	, m_fCurrentTime(0.f)
{
}


iUnitAction::~iUnitAction()
{
}

void iUnitAction::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
