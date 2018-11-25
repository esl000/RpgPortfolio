#include "StdAfx.h"
#include "cUIMainView.h"

#include "cUIObject.h"
#include "cUIImageView.h"
#include "cUIButton.h"

#include "cGameScene.h"
#include "cLoadingScene.h"
#include "cMapToolScene.h "

cUIMainView::cUIMainView(void)
{

}

cUIMainView::~cUIMainView(void)
{
}

void cUIMainView::Setup(void)
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite); 
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	cUIImageView* pImage = new cUIImageView;
	pImage->SetTexture(string("./UI/(1)Menu/0.MenuBack/MenuBack_2.png"));
	pImage->SetPosition(D3DXVECTOR3(0, 0, 0));
	AddChild(pImage);

	cUIButton* pButton = new cUIButton;
	pButton->SetButtonImage("./UI/(1)Menu/1.MenuButton/MenuButton_000.png",
				"./UI/(1)Menu/1.MenuButton/MenuButton_001.png", 
				"./UI/(1)Menu/1.MenuButton/MenuButton_001.png");
	pButton->SetPosition(D3DXVECTOR3((rc.right / 2) - 150, (rc.bottom / 2) + 2, 0));
	pButton->SetTag(0);
	pButton->SetDelegate(this);
	AddChild(pButton);

	pButton = new cUIButton;
	pButton->SetButtonImage("./UI/(1)Menu/1.MenuButton/MenuButton_100.png",
		"./UI/(1)Menu/1.MenuButton/MenuButton_101.png",
		"./UI/(1)Menu/1.MenuButton/MenuButton_101.png");
	pButton->SetPosition(D3DXVECTOR3((rc.right / 2) - 150, (rc.bottom / 2) + 52, 0));
	pButton->SetDelegate(this);
	pButton->SetTag(1);
	AddChild(pButton);
}

void cUIMainView::Update(void)
{
	cUIObject::Update();
}

void cUIMainView::Render(void)
{
	cUIObject::Render(m_pSprite);
	g_pPicking->Update();
}

void cUIMainView::OnClick(cUIButton* pButton)
{
	if (pButton->GetTag() == 0)
	{
		//cGameScene* pGameScene = new cGameScene;
		//pGameScene->Setup();
		//g_pSceneManager->AddScene(string("GameScene"), pGameScene);
		//g_pSceneManager->ChangeScene(string("GameScene"));
		g_pSoundManager->stop("MenuSceneBackGround");
		g_pSoundManager->play("LodingSceneBackGround", 0.3f);

		cLoadingScene* pLoad = new cLoadingScene;
		pLoad->Setup();
		g_pSceneManager->AddScene(string("loading"), pLoad);
		g_pSceneManager->ChangeScene(string("loading"));
		//리턴 꼭 해줄것
		return;
	}
	else
	{
		g_pSoundManager->stop("MenuSceneBackGround");

		cMapToolScene* pMapTool = new cMapToolScene;
		pMapTool->Setup();
		g_pSceneManager->AddScene(string("map"), pMapTool);
		g_pSceneManager->ChangeScene(string("map"));
		return;
	}
	
}