#include "StdAfx.h"
#include "cUILoading.h"
#include "cSceneManager.h"
#include "cLoadingScene.h"
#include "cGameScene.h"
#include "cUIImageView.h"
#include "cUnitPlayer.h"
#include "cDataload.h"


cUILoading::cUILoading(void)
	: m_fLoading(0)
	, m_ulStackSize(0)
	, m_bVolLoading(false)
	, m_bVolSetup(false)
	, m_pGameScene(NULL)
{
}


cUILoading::~cUILoading(void)
{
}

void cUILoading::Setup(void)
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cUIImageView* pUIImageView = new cUIImageView;
	pUIImageView->SetTexture(string("./UI/(3)Loading/Loading_01.png"));
	pUIImageView->SetScale(D3DXVECTOR3(1.f, 1.f, 1.f));
	pUIImageView->SetPosition(D3DXVECTOR3(0, 0, 0));
	AddChild(pUIImageView);

	m_pUILoadingGauge = new cUIImageView;
	m_pUILoadingGauge->SetTexture(string("./UI/(3)Loading/Loading_5.png"));
	m_pUILoadingGauge->SetScale(D3DXVECTOR3(0.0f, 1.f, 1.f));
	m_pUILoadingGauge->SetPosition(D3DXVECTOR3((rc.right / 2) - 369.f, (rc.bottom / 2) + 301.f, 0));
	AddChild(m_pUILoadingGauge);

	InitializeCriticalSection(&cs);

	DWORD dwThID[2];
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadSetup, this, NULL/*CREATE_SUSPENDED*/, &dwThID[1]));
}

void cUILoading::Update(void)
{ 
	cUIObject::Update();
	if (m_fLoading <= 1.f)
	m_fLoading += g_pTimeManager->GetElapsedTime() / 200.f;
	m_pUILoadingGauge->SetScale(D3DXVECTOR3(m_fLoading, 1.f, 1.f));
}

void cUILoading::Render(void)
{
	EnterCriticalSection(&cs);
	cUIObject::Render(m_pSprite);
	LeaveCriticalSection(&cs);
	g_pPicking->Update();
}

void cUILoading::ThreadSetup(LPVOID lpVod)
{
	cUILoading* pLoading = (cUILoading*)lpVod;

	cGameScene* pGameScene = new cGameScene;
	g_pFrustum->Setup();
	g_pItemDatabase->GetItem(string(""));
	g_pQuestDatabase->GetQuest(string(""));
	g_pNpcDatabase->GetCustomNpc(string(""));
	g_pBuildingDatabase->GetBuilding(string(""));
	pLoading->m_fLoading = 0.4f;
	g_pObjectDatabase->GetObjects(string(""));
	
	g_pPicking->Setup();
	g_pEntityManager->Setup();
	g_pUnitManager->Setup();

	g_pEffectManager->Setup();
	g_pSkillManager->Setup();
	g_pIntersectManager->Setup();


	cUnitPlayer* pPlayer = new cUnitPlayer;
	pPlayer->SetPosition(D3DXVECTOR3(22026.68, 30, -14598.11));
	//22026.68, 30, -14598.11

	g_pUnitManager->SetPlayer(pPlayer);
	g_pTileManager->SetTarget(pPlayer);
	g_pTileManager->SetDelegate(pGameScene);
	g_pTileManager->Setup();

	pPlayer->Setup();

	g_pUnitManager->RegisterUnit(pPlayer);
	g_pIntersectManager->SetTarget(pPlayer);

	while (true)
	{
		if (!g_pTileManager->m_isLoading)
			break;
		Sleep(100);
	}

	for (int x = 0; x < 60; ++x)
	{
		for (int z = 0; z < 60; ++z)
		{
			cDataload::GameLoad(ST_CHUNK_INDEX(x, z));
		}
	}

	pLoading->m_fLoading = 0.8f;

	pGameScene->Setup();

	EnterCriticalSection(&cs);
	pLoading->m_fLoading = 1.f;

	g_pSceneManager->AddScene(string("GameScene"), pGameScene);
	g_pSceneManager->ChangeScene(string("GameScene"));
	//LeaveCriticalSection(&cs);
}
