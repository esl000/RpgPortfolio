#pragma once

#include "iScene.h"
#include "cUIMainView.h"
#include "cMenuScene.h"
#include "cSceneManager.h"

class cMenuScene
	: public iScene
{
private:
	cUIMainView*		m_pUIMainView;

public:
	cMenuScene();
	virtual ~cMenuScene();

public:
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

