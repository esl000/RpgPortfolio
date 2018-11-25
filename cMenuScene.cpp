#include "stdafx.h"
#include "cMenuScene.h"
#include "cTestScene.h"
#include "cUIMainView.h"

cMenuScene::cMenuScene()
	: m_pUIMainView(NULL)
{
}


cMenuScene::~cMenuScene()
{
	//Object로 만든건 항상 릴리즈(Error -> Delete)
	SAFE_RELEASE(m_pUIMainView);
}

void cMenuScene::Setup(void)
{
	if (m_pUIMainView == NULL)
	{
		m_pUIMainView = new cUIMainView;
		m_pUIMainView->Setup();
		g_pSoundManager->play("MenuSceneBackGround", 0.3f);
	}
}

void cMenuScene::Update(void)
{
	if (m_pUIMainView)
	{
		m_pUIMainView->Update();
	}

	if (GetKeyState(VK_F3) & 0x8000)
	{
		cTestScene* pLoad = new cTestScene;
		pLoad->Setup();
		g_pSceneManager->AddScene(string("test"), pLoad);
		g_pSceneManager->ChangeScene(string("test"));
		return;
	}
}

void cMenuScene::Render(void)
{
	if (m_pUIMainView)
	{
		m_pUIMainView->Render();
	}
}

void cMenuScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
