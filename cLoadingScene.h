#pragma once

#include "iScene.h"

class cUILoading;

class cLoadingScene
	: public iScene
{
private:
	cUILoading*			m_pUILoading;
	bool				m_isChecked;
	int					m_nCount;

public:
	cLoadingScene();
	virtual ~cLoadingScene();

public:
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
public:
	static void ThreadFirst(LPVOID pParam);
	static void ThreadSecond(LPVOID pParam);

};

