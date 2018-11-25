#include "stdafx.h"
#include "cGameScene.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cLight.h"
#include "iMap.h"
#include "cHeightMap.h"
#include "cUnitPlayer.h"
#include "cUnitMonster.h"
#include "cUIInterface.h"
#include "cUnitCustomNpc.h"
#include "cDataload.h"
#include "cEntityBuilding.h"
#include "cEntityObject.h"
#include "cUIIQuest.h"


cGameScene::cGameScene()
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pLight(NULL)
	, m_pMap(NULL)
	, m_pPlayer(NULL)
	, m_pInterface(NULL)
	, m_pNpcSylva(NULL)
	, m_pNpcThrall(NULL)
	, m_pGaugeBar(NULL)
	, m_bSetupComplete(false)
{
}


cGameScene::~cGameScene()
{
	SAFE_DELETE(m_pGrid);
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pLight);
	SAFE_RELEASE(m_pMap);
	SAFE_RELEASE(m_pInterface);

	g_pItemDatabase->Destroy();
	g_pQuestDatabase->Destroy();
	g_pNpcDatabase->Destroy();
	g_pMonsterDatabase->Destroy();
	g_pBuildingDatabase->Destroy();
	g_pObjectDatabase->Destroy();
	g_pEffectManager->Destroy();
	g_pSkillManager->Destroy();
	g_pUnitManager->Destroy();
	g_pEntityManager->Destroy();
	g_pTileManager->Destroy();
	g_pObjManager->Destroy();
	g_pUImanager->Destroy();
	g_pItemDatabase->Destroy();
}

void cGameScene::Setup()
{
	//g_pFrustum->Setup();
	////g_pQuestDatabase->GetQuest(string(""));
	////g_pNpcDatabase->GetCustomNpc(string(""));
	////g_pBuildingDatabase->GetBuilding(string(""));
	//g_pObjectDatabase->GetObjects(string(""));
	////g_pQuestDatabase->
	//g_pPicking->Setup();
	//g_pEntityManager->Setup();
	//g_pUnitManager->Setup();
	//g_pEffectManager->Setup();
	//g_pSkillManager->Setup();
	//g_pIntersectManager->Setup();
	//////////////////////////////////////////////////
	////UILoadingÀ¸·Î ÀÌµ¿µÊ
	////g_pFrustum->Setup();
	////g_pQuestDatabase->GetQuest(string(""));
	////g_pNpcDatabase->GetCustomNpc(string(""));
	////g_pBuildingDatabase->GetBuilding(string(""));
	////g_pObjectDatabase->GetObjects(string(""));

	////g_pPicking->Setup();
	////g_pEntityManager->Setup();
	////g_pUnitManager->Setup();
	////g_pEffectManager->Setup();
	////g_pSkillManager->Setup();
	////g_pIntersectManager->Setup();
	//////////////////////////////////////////////////

	m_pLight = new cLight;
	m_pLight->Setup();

	//m_pGrid = new cGrid;
	//m_pGrid->Setup(500, 1);

	//m_pPlayer = new cUnitPlayer;
	//m_pPlayer->SetPosition(D3DXVECTOR3(40 * CHUNK_SIZE + CHUNK_SIZE / 2, 100, -28 * CHUNK_SIZE + CHUNK_SIZE / 2));

	////cEntityBuilding* pBuilding = g_pBuildingDatabase->GetBuilding("ogrimmar");
	////pBuilding->SetPosition(D3DXVECTOR3(0, 20, 0));
	////pBuilding->Setup();
	////g_pEntityManager->RegisterEntity(pBuilding);

	////cEntityObject* pObject = g_pObjectDatabase->GetObjects("tree01");
	////pObject->SetPosition(D3DXVECTOR3(100, 0, 100));
	////pObject->Setup();
	////g_pEntityManager->RegisterEntity(pObject);

	//g_pUnitManager->RegisterUnit(m_pPlayer);
	//g_pIntersectManager->SetTarget(m_pPlayer);

	////g_pTileManager->SetTarget(m_pPlayer);

	//////////////////////////////////
	////UILoadingÀ¸·Î ÀÌµ¿µÊ
	//g_pTileManager->SetTarget(m_pPlayer);
	//g_pTileManager->SetDelegate(this);
	//g_pTileManager->Setup();
	//
	//m_pPlayer->Setup();
	//////////////////////////////////
	
	/*m_pMonster = g_pMonsterDatabase->GetMonster(string("µ¥½ºÀ®"));
	m_pMonster->SetPosition(D3DXVECTOR3(22226.68, 24.60, -14578.11));*/

	//float fAngle = atan2f(m_pMonster->GetDirection().x, m_pMonster->GetDirection().z) - D3DX_PI;
	/*float fAngle = D3DX_PI / 2.0f;
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, fAngle);
	D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
	D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
	D3DXVec3Normalize(&vDirection, &vDirection);
	m_pMonster->SetDirection(vDirection);
	
	m_pMonster->SetTarget(m_pPlayer);
	m_pMonster->Setup();
	g_pUnitManager->RegisterUnit(m_pMonster);*/


	m_pCamera = new cCamera;
	m_pCamera->SetTarget(g_pUnitManager->GetPlayer()->GetPos());
	m_pCamera->SetPlayer(g_pUnitManager->GetPlayer());
	m_pCamera->Setup();
	g_pUnitManager->SetCamera(m_pCamera);

	//cHeightMap* pMap = new cHeightMap;
	//pMap->Load("map", "kalimdor_27_33.adt_Heightmap_LOD.raw", "desolacerock01");
	//g_pTileManager->AddMap("1", pMap);
		
	if (m_pInterface == NULL)
	{
		m_pInterface = new cUIInterface;
		m_pInterface->Setup();
	}
	/*if (m_pGaugeBar == NULL)
	{
		m_pGaugeBar = new cUIGaugeBar;
		m_pGaugeBar->Setup();
	}*/

}

void cGameScene::Update()
{
	if (!m_bSetupComplete)
	{
		g_pSoundManager->stop("LodingSceneBackGround");
		g_pSoundManager->play("OrgrimarBackGround", 0.3f);
		m_bSetupComplete = true;
	}

	g_pFrustum->Update();
	g_pTileManager->Update();

	g_pUImanager->Update();

	if (m_pInterface)
		m_pInterface->Update();

	
	if (m_pLight)
		m_pLight->Update();

	g_pIntersectManager->Update();
	g_pEntityManager->Update();
	g_pEffectManager->Update();
	g_pSkillManager->Update();

	if (m_pCamera)
		m_pCamera->Update();
}

void cGameScene::Render()
{
	if (m_pGrid)
		m_pGrid->Render();

	g_pEntityManager->Render();
	
	
	g_pTileManager->Render();
	g_pEffectManager->Render();
	g_pSkillManager->Render();

	if (m_pInterface)
		m_pInterface->Render();
	//if (m_pGaugeBar)
	//	m_pGaugeBar->Render();
	

	g_pUImanager->Render();
	g_pPicking->Update();

}

void cGameScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	g_pUImanager->WndProc(hWnd, message, wParam, lParam);
	g_pEntityManager->WndProc(hWnd, message, wParam, lParam);
}

void cGameScene::OnLoadDelegate(ST_CHUNK_INDEX stIndex)
{
	cDataload::GameLoad(stIndex);
}
