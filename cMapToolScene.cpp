#include "stdafx.h"
#include "cMapToolScene.h"
#include "cDataload.h"
#include "cEntityBuilding.h"
#include "cEntityObject.h"
#include "cUnitMonster.h"
#include "cUnitCustomNpc.h"
#include "cHeightMap.h"
#include "cSceneManager.h"
#include "cMenuScene.h"


cMapToolScene::cMapToolScene()
	: m_pCurrentEntity(NULL)
	, m_eCurrentType(cEntity::E_BUILDING)
	, m_nIndex(0)
	, m_pCamera(NULL)
	, m_pLight(NULL)
	, m_pGrid(NULL)
	, m_pViewPos(NULL)
{
}


cMapToolScene::~cMapToolScene()
{
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pLight);
	SAFE_DELETE(m_pGrid);
	SAFE_RELEASE(m_pViewPos);

	for each(auto p in m_vecEntity)
	{
		SAFE_RELEASE(p);
	}

	g_pNpcDatabase->Destroy();
	g_pMonsterDatabase->Destroy();
	g_pBuildingDatabase->Destroy();
	g_pObjectDatabase->Destroy();
	g_pTileManager->Destroy();
}

void cMapToolScene::Load()
{
	for (int x = 0; x < 60; ++x)
	{
		for (int z = 0; z < 60; ++z)
		{
			cDataload::Load(m_vecEntity, ST_CHUNK_INDEX(x, z));
		}
	}
}

void cMapToolScene::Save()
{
	for (int x = 0; x < 60; ++x)
	{
		for (int z = 0; z < 60; ++z)
		{
			cDataload::Save(m_vecEntity, ST_CHUNK_INDEX(x, z));
		}
	}
	//cDataload::Save(m_vecEntity);
}

void cMapToolScene::Setup()
{
	Load();
	//cHeightMap* pMap = new cHeightMap;
	//pMap->Load("map", "kalimdor_27_33.adt_Heightmap_LOD.raw", "desolacerock01");
	//g_pTileManager->AddMap("1", pMap);

	m_pGrid = new cGrid;
	m_pGrid->Setup(50, CHUNK_SIZE);

	m_pLight = new cLight;
	m_pLight->Setup();

	m_pViewPos = new cViewPos;
	m_pViewPos->SetPosition(D3DXVECTOR3(40 * CHUNK_SIZE + CHUNK_SIZE / 2.05f, 25, -28 * CHUNK_SIZE + CHUNK_SIZE / 2.05f));
	m_pViewPos->Setup();

	m_pCamera = new cCamera;
	m_pCamera->SetTarget(m_pViewPos->GetPos());
	m_pCamera->Setup();
	g_pUnitManager->SetCamera(m_pCamera);

	g_pTileManager->SetTarget(m_pViewPos);
	g_pTileManager->SetDelegate(this);
	g_pTileManager->Setup();
}

void cMapToolScene::Update()
{
	m_pLight->Update();
	m_pViewPos->Update();
	m_pCamera->Update();

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		float fAngle = atan2f(m_pCurrentEntity->GetDirection().x, m_pCurrentEntity->GetDirection().z) - D3DX_PI;
		fAngle -= 0.1f;
		D3DXMATRIXA16 matR, matT;
		D3DXMatrixRotationY(&matR, fAngle);

		D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
		D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
		D3DXVec3Normalize(&vDirection, &vDirection);
		m_pCurrentEntity->SetDirection(vDirection);
	}

	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		float fAngle = atan2f(m_pCurrentEntity->GetDirection().x, m_pCurrentEntity->GetDirection().z) - D3DX_PI;
		fAngle += 0.1f;
		D3DXMATRIXA16 matR, matT;
		D3DXMatrixRotationY(&matR, fAngle);

		D3DXVECTOR3 vDirection = D3DXVECTOR3(0.f, 0.f, -1.f);
		D3DXVec3TransformNormal(&vDirection, &vDirection, &matR);
		D3DXVec3Normalize(&vDirection, &vDirection);
		m_pCurrentEntity->SetDirection(vDirection);
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{
		D3DXVECTOR3 vPos = m_pCurrentEntity->GetPosition();
		vPos.y += 0.3f;
		m_pCurrentEntity->SetPosition(vPos);
	}

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		D3DXVECTOR3 vPos = m_pCurrentEntity->GetPosition();
		vPos.y -= 0.3f;
		m_pCurrentEntity->SetPosition(vPos);
	}

	if (GetKeyState('I') & 0x8000)
	{
		D3DXVECTOR3 vPos = m_pCurrentEntity->GetPosition();
		vPos.z += 10 * g_pTimeManager->GetElapsedTime();
		m_pCurrentEntity->SetPosition(vPos);
	}

	if (GetKeyState('K') & 0x8000)
	{
		D3DXVECTOR3 vPos = m_pCurrentEntity->GetPosition();
		vPos.z -= 10 * g_pTimeManager->GetElapsedTime();
		m_pCurrentEntity->SetPosition(vPos);
	}

	if (GetKeyState('J') & 0x8000)
	{
		D3DXVECTOR3 vPos = m_pCurrentEntity->GetPosition();
		vPos.x -= 10 * g_pTimeManager->GetElapsedTime();
		m_pCurrentEntity->SetPosition(vPos);
	}

	if (GetKeyState('L') & 0x8000)
	{
		D3DXVECTOR3 vPos = m_pCurrentEntity->GetPosition();
		vPos.x += 10 * g_pTimeManager->GetElapsedTime();
		m_pCurrentEntity->SetPosition(vPos);
	}

	if (GetKeyState('M') & 0x8000)
	{
		m_eCurrentType = cEntity::E_MONSTER;
		std::cout << "MONSTER" << endl;
	}

	if (GetKeyState('N') & 0x8000)
	{
		m_eCurrentType = cEntity::E_NPC;
		std::cout << "NPC" << endl;
	}

	if (GetKeyState('B') & 0x8000)
	{
		m_eCurrentType = cEntity::E_BUILDING;
		std::cout << "BUILDING" << endl;
	}

	if (GetKeyState('O') & 0x8000)
	{
		m_eCurrentType = cEntity::E_OBJECT;
		std::cout << "OBJECT" << endl;
	}

	for each(auto p in m_vecEntity)
	{
		EnterCriticalSection(&cs);
		if (p && g_pTileManager->IsMovementRange(p->GetPosition(), p->GetEntityType()))
			p->Update();
		LeaveCriticalSection(&cs);
	}
	g_pTileManager->Update();
}

void cMapToolScene::Render()
{
	m_pGrid->Render();
	for each(auto p in m_vecEntity)
	{
		EnterCriticalSection(&cs);
		if (p && g_pFrustum->IsIn(&p->GetFrustumSphere()) && g_pTileManager->IsMovementRange(p->GetPosition(), p->GetEntityType()))
			p->Render();
		LeaveCriticalSection(&cs);
	}
	g_pTileManager->Render();
}

void cMapToolScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pCamera->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'C':
			if (m_eCurrentType == cEntity::E_BUILDING)
			{
				cEntityBuilding* pEntity = g_pBuildingDatabase->GetBuilding(m_nIndex);
				D3DXVECTOR3 vPos;
				g_pTileManager->GetPickingMapPos(vPos);
				pEntity->SetPosition(vPos);
				pEntity->Setup();
				m_pCurrentEntity = pEntity;
				m_vecEntity.push_back(pEntity);
				std::cout << "PLACE!!!!!!" << endl;
			}
			else if (m_eCurrentType == cEntity::E_OBJECT)
			{
				cEntityObject* pEntity = g_pObjectDatabase->GetObjects(m_nIndex);
				D3DXVECTOR3 vPos;
				g_pTileManager->GetPickingMapPos(vPos);
				pEntity->SetPosition(vPos);
				pEntity->Setup();
				m_pCurrentEntity = pEntity;
				m_vecEntity.push_back(pEntity);
				std::cout << "PLACE!!!!!!" << endl;
			}
			else if (m_eCurrentType == cEntity::E_MONSTER)
			{
				cUnitMonster* pEntity = g_pMonsterDatabase->GetMonster(m_nIndex);
				D3DXVECTOR3 vPos;
				g_pTileManager->GetPickingMapPos(vPos);
				pEntity->SetPosition(vPos);
				pEntity->Setup();
				m_pCurrentEntity = pEntity;
				m_vecEntity.push_back(pEntity);
				std::cout << "PLACE!!!!!!" << endl;
			}
			else if (m_eCurrentType == cEntity::E_NPC)
			{
				cUnitCustomNpc* pEntity = g_pNpcDatabase->GetCustomNpc(m_nIndex);
				D3DXVECTOR3 vPos;
				g_pTileManager->GetPickingMapPos(vPos);
				pEntity->SetPosition(vPos);
				pEntity->Setup();
				m_pCurrentEntity = pEntity;
				m_vecEntity.push_back(pEntity);
				std::cout << "PLACE!!!!!!" << endl;
			}
			break;
		case '1':
			m_nIndex--;
			std::cout << "INDEX : " << m_nIndex << endl;
			break;
		case '2':
			m_nIndex++;
			std::cout << "INDEX : " << m_nIndex << endl;
			break;
		case VK_F1:
			Save();
			std::cout << "Save!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			break;
		case VK_ESCAPE:
			for (int i = 0; i < m_vecEntity.size(); ++i)
			{
				if (m_pCurrentEntity == m_vecEntity[i])
				{
					SAFE_RELEASE(m_pCurrentEntity);
					m_vecEntity.erase(m_vecEntity.begin() + i);
					break;
				}
			}
			break;
		}
		break;
	case WM_RBUTTONDOWN:
		cRay r = cRay::GetRayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);
		for each (auto p in m_vecEntity)
		{
			if (r.IsPicked(&p->GetFrustumSphere()))
			{
				m_pCurrentEntity = p;
				std::cout << " 0 : building" << endl;
				std::cout << " 1 : object" << endl;
				std::cout << " 2 : unit" << endl;
				std::cout << "SELECT!!" << " : " << p->GetEntityType() << endl;
				return;
			}
		}

		if (m_pCurrentEntity)
		{
			D3DXVECTOR3 vPos;
			g_pTileManager->GetPickingMapPos(vPos);
			m_pCurrentEntity->SetPosition(vPos);
			std::cout << "MOVE!!" << endl;
		}
		break;
	}
}

void cMapToolScene::OnLoadDelegate(ST_CHUNK_INDEX stIndex)
{
	//cDataload::Load(m_vecEntity, stIndex);
}
