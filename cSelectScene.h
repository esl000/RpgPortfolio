#pragma once
#include "iScene.h"
class cSelectScene :
	public iScene
{
public:
	cSelectScene();
	~cSelectScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

