#include "stdafx.h"
#include "cTestScene.h"
#include "cDataload.h"
#include "cUnitPlayer.h"


cTestScene::cTestScene()
{
}


cTestScene::~cTestScene()
{
}

void cTestScene::Load()
{
	for (int x = 0; x < 60; ++x)
	{
		for (int z = 0; z < 60; ++z)
		{
			cDataload::GameLoad(ST_CHUNK_INDEX(x, z));
		}
	}
}

void cTestScene::Save()
{

}

void cTestScene::Setup()
{


	m_pLight = new cLight;
	m_pLight->Setup();

	cUnitPlayer* pPlayer = new cUnitPlayer;
	pPlayer->SetPosition(D3DXVECTOR3(40 * CHUNK_SIZE + CHUNK_SIZE / 2.03f, 25, -29 * CHUNK_SIZE + CHUNK_SIZE / 2.03f));

	m_pCamera = new cCamera;
	m_pCamera->SetTarget(pPlayer->GetPos());
	m_pCamera->Setup();

	g_pUnitManager->SetCamera(m_pCamera);
	g_pUnitManager->SetPlayer(pPlayer);
	g_pTileManager->SetTarget(pPlayer);
	g_pTileManager->Setup();

	g_pFrustum->Setup();

	pPlayer->Setup();

	g_pUnitManager->RegisterUnit(pPlayer);
	g_pIntersectManager->SetTarget(pPlayer);
	Load();
}

void cTestScene::Update()
{
	m_pLight->Update();

	g_pFrustum->Update();
	g_pTileManager->Update();

	g_pUImanager->Update();

	g_pIntersectManager->Update();
	g_pEntityManager->Update();
	g_pEffectManager->Update();
	g_pSkillManager->Update();

	m_pCamera->Update();
}

void cTestScene::Render()
{


	g_pTileManager->Render();
	g_pEffectManager->Render();
	g_pSkillManager->Render();

	g_pIntersectManager->Render();
	g_pEntityManager->Render();

	g_pUImanager->Render();
	g_pPicking->Update();
}

void cTestScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
