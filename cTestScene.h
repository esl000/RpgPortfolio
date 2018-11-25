#pragma once
#include "iScene.h"

#include "cCamera.h"
#include "cLight.h"

class cTestScene :
	public iScene
{
protected:
	cCamera* m_pCamera;
	cLight* m_pLight;
public:
	cTestScene();
	virtual ~cTestScene();

	void Load();
	void Save();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

