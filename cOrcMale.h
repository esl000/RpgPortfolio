#pragma once
#include "cUnitPlayer.h"

class cOrcMale : public cUnitPlayer
{
public:
	cOrcMale();
	virtual	~cOrcMale();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

