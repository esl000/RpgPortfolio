#include "stdafx.h"
#include "cTileManager.h"
#include "cHeightMap.h"
#include "cDataload.h"
#include "cMapToolScene.h"


cTileManager::cTileManager()
	: m_pTarget(NULL)
	, m_pDelegate(NULL)
	, m_pEffect(NULL)
	, m_isLoading(false)
	, m_stCurrentChuck(-1, -1)
	, vTarget()
{
	
}


cTileManager::~cTileManager()
{
}

void cTileManager::Setup()
{
	m_pEffect = LoadEffect("mapshader.fx");
	Update();
}

void cTileManager::Load(LPVOID pThis)
{
	cTileManager* pTile = (cTileManager*)pThis;

	if (pTile->m_vecLoadMap.size() == 0)
	{
		ST_CHUNK stChunk = GetChunk(pTile->m_pTarget->GetPosition());
		ST_CHUNK_INDEX stPrevIndex = pTile->m_stCurrentChuck;
		ST_CHUNK_INDEX stIndex = GetChunkIndex(pTile->m_pTarget->GetPosition());
		EnterCriticalSection(&cs_tile);
		pTile->m_stCurrentChuck = stIndex;
		LeaveCriticalSection(&cs_tile);

		vector<ST_CHUNK_INDEX> vecIndex(25);
		vector<cHeightMap*> vecLoadMap(25);
		pTile->m_stCurrentChuck = GetChunkIndex(pTile->m_pTarget->GetPosition());
		for (int x = -2; x <= 2; ++x)
		{
			for (int z = -2; z <= 2; ++z)
			{
				vecIndex[(x + 2) * 5 + z + 2] = ST_CHUNK_INDEX(pTile->m_stCurrentChuck.x + x, pTile->m_stCurrentChuck.z + z);
				vecLoadMap[(x + 2) * 5 + z + 2] = pTile->LoadTile(ST_CHUNK_INDEX(pTile->m_stCurrentChuck.x + x, pTile->m_stCurrentChuck.z + z));
			}
		}


		EnterCriticalSection(&cs_tile);
		pTile->m_vecViewMap.resize(9);
		pTile->m_vecViewMap[0] = vecLoadMap[6];
		pTile->m_vecViewMap[1] = vecLoadMap[7];
		pTile->m_vecViewMap[2] = vecLoadMap[8];

		pTile->m_vecViewMap[3] = vecLoadMap[11];
		pTile->m_vecViewMap[4] = vecLoadMap[12];
		pTile->m_vecViewMap[5] = vecLoadMap[13];

		pTile->m_vecViewMap[6] = vecLoadMap[16];
		pTile->m_vecViewMap[7] = vecLoadMap[17];
		pTile->m_vecViewMap[8] = vecLoadMap[18];

		pTile->m_vecLoadMap = vecLoadMap;
		pTile->m_vecLoadIndex = vecIndex;
		LeaveCriticalSection(&cs_tile);
		cout << "Load!!" << endl;
		pTile->m_isLoading = false;
		return;
	}

	if (pTile->m_pTarget)
	{
		ST_CHUNK_INDEX stPrevIndex = pTile->m_stCurrentChuck;
		ST_CHUNK_INDEX stIndex = GetChunkIndex(pTile->m_pTarget->GetPosition());
		EnterCriticalSection(&cs_tile);
		pTile->m_stCurrentChuck = stIndex;
		LeaveCriticalSection(&cs_tile);
		//vector<ST_CHUNK_INDEX> vecIndex;

		vector<cHeightMap*> vecViewMap(9);
		vector<cHeightMap*> vecLoadMap(25);
		vector<cHeightMap*> vecOrgLoadMap = pTile->m_vecLoadMap;

		vector<DWORD> vecIndex;
		vecIndex.push_back(6);
		vecIndex.push_back(7);
		vecIndex.push_back(8);

		vecIndex.push_back(11);
		vecIndex.push_back(12);
		vecIndex.push_back(13);

		vecIndex.push_back(16);
		vecIndex.push_back(17);
		vecIndex.push_back(18);

		vector<ST_CHUNK_INDEX> vecLoadIndex(25);

		for (size_t i = 0; i < pTile->m_vecLoadMap.size(); ++i)
		{
			vecLoadIndex[i] = pTile->m_vecLoadIndex[i];
		}

		if (pTile->m_stCurrentChuck.x == stPrevIndex.x + 1)
		{
			for (size_t i = 0; i < vecIndex.size(); ++i)
			{
				vecIndex[i] += 5;
			}

			for (size_t i = 0; i < vecLoadIndex.size(); ++i)
			{
				vecLoadIndex[i].x += 1;
			}
		}
		else if (pTile->m_stCurrentChuck.x == stPrevIndex.x - 1)
		{
			for (size_t i = 0; i < vecIndex.size(); ++i)
			{
				vecIndex[i] -= 5;
			}

			for (size_t i = 0; i < vecLoadIndex.size(); ++i)
			{
				vecLoadIndex[i].x -= 1;
			}
		}

		if (pTile->m_stCurrentChuck.z == stPrevIndex.z + 1)
		{
			for (size_t i = 0; i < vecIndex.size(); ++i)
			{
				vecIndex[i] += 1;
			}

			for (size_t i = 0; i < vecLoadIndex.size(); ++i)
			{
				vecLoadIndex[i].z += 1;
			}
		}
		else if (pTile->m_stCurrentChuck.z == stPrevIndex.z - 1)
		{
			for (size_t i = 0; i < vecIndex.size(); ++i)
			{
				vecIndex[i] -= 1;
			}

			for (size_t i = 0; i < vecLoadIndex.size(); ++i)
			{
				vecLoadIndex[i].z -= 1;
			}
		}

		for (size_t i = 0; i < vecIndex.size(); ++i)
		{
			vecViewMap[i] = vecOrgLoadMap[vecIndex[i]];
		}

		for (size_t i = 0; i < vecLoadIndex.size(); ++i)
		{
			bool isNotLoad = false;
			for (size_t j = 0; j < pTile->m_vecLoadIndex.size(); ++j)
			{
				if (vecLoadIndex[i] == pTile->m_vecLoadIndex[j])
				{ 
					isNotLoad = true;
					vecLoadMap[i] = vecOrgLoadMap[j];
					vecOrgLoadMap.erase(vecOrgLoadMap.begin() + j);
					pTile->m_vecLoadIndex.erase(pTile->m_vecLoadIndex.begin() + j);
					continue;
				}
			}
			if (isNotLoad)
				continue;
			cHeightMap* pMap = pTile->LoadTile(vecLoadIndex[i]);
			vecLoadMap[i] = pMap;
		}


		for (size_t i = 0; i < vecOrgLoadMap.size(); ++i)
		{
			SAFE_RELEASE(vecOrgLoadMap[i]);
		}

		
		pTile->m_vecLoadMap.clear();
		pTile->m_vecLoadIndex.clear();

		pTile->m_vecLoadMap = vecLoadMap;
		pTile->m_vecLoadIndex = vecLoadIndex;

		EnterCriticalSection(&cs_tile);
		pTile->m_vecViewMap.clear();
		pTile->m_vecViewMap = vecViewMap;
		LeaveCriticalSection(&cs_tile);


		pTile->m_isLoading = false;
	}
}

bool cTileManager::IsMovementRange(D3DXVECTOR3 vPosition, cEntity::eEntityType eType)
{
	ST_CHUNK_INDEX stIndex = GetChunkIndex(vPosition);

	if (eType == 0)
	{

		EnterCriticalSection(&cs_tile);
		if (m_stCurrentChuck.x - 2 <= stIndex.x && stIndex.x <= m_stCurrentChuck.x + 2
			&& m_stCurrentChuck.z - 2 <= stIndex.z && stIndex.z <= m_stCurrentChuck.z + 2)
		{
			LeaveCriticalSection(&cs_tile);
			return true;
		}
	}
	else
	{
		EnterCriticalSection(&cs_tile);
		if (m_stCurrentChuck.x - 1 <= stIndex.x && stIndex.x <= m_stCurrentChuck.x + 1
			&& m_stCurrentChuck.z - 1 <= stIndex.z && stIndex.z <= m_stCurrentChuck.z + 1)
		{
			LeaveCriticalSection(&cs_tile);
			return true;
		}
	}
	LeaveCriticalSection(&cs_tile);
	return false;
}

cHeightMap* cTileManager::LoadTile(ST_CHUNK_INDEX stIndex)
{
	cHeightMap* pMap = new cHeightMap;
	char szPath[1024];
	sprintf_s(szPath, "kalimdor_%d_%d.adt_Heightmap_LOD.raw", stIndex.x, stIndex.z);

	//if (m_pDelegate)
	//{
	//	m_pDelegate->OnLoadDelegate(stIndex);
	//}

	string sFullPath = string("map/kalimdor") + string("/") + string(szPath);
	
	cout << "trying Load : " << sFullPath.c_str() << endl;

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");
	if (!fp)
		return NULL;
	fclose(fp);
	pMap->SetIndex(stIndex);
	pMap->SetShader(m_pEffect);
	pMap->SetChunk(ST_CHUNK(stIndex.x * CHUNK_SIZE, -stIndex.z * CHUNK_SIZE));
	pMap->Load("map/kalimdor", szPath, "abc.png");

	return pMap;
}

void cTileManager::Update()
{
	//static int nCnt;
	if (m_pTarget)
	{
		//++nCnt;
		//if (nCnt == 30)
		//{
		//	nCnt = 0;
		//	//cout << "target index : " << GetChunkIndex(m_pTarget->GetPosition()).x << " , " << GetChunkIndex(m_pTarget->GetPosition()).z << endl;
		//	//cout << "target index : " << m_stCurrentChuck.x << " , " << m_stCurrentChuck.z << endl;
		//}
		if (GetChunkIndex(m_pTarget->GetPosition()) != m_stCurrentChuck && !m_isLoading)
		{
			m_isLoading = true;
			cout << "callthread!!!" << endl;
			DWORD dwThID;
			CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Load, this, NULL/*CREATE_SUSPENDED*/, &dwThID));
		}
	}
}

void cTileManager::Render()
{
	LPDIRECT3DTEXTURE9 pRenderTarget;
	LPDIRECT3DSURFACE9 pRenderSurface;
	LPDIRECT3DSURFACE9 pOrgRenderSurface;

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//g_pD3DDevice->CreateTexture(rc.right,
	//	rc.bottom,
	//	1, D3DUSAGE_RENDERTARGET,
	//	D3DFMT_A8R8G8B8,
	//	D3DPOOL_DEFAULT,
	//	&pRenderTarget, NULL);

	//g_pD3DDevice->GetRenderTarget(0, &pOrgRenderSurface);

	//pRenderTarget->GetSurfaceLevel(0, &pRenderSurface);

	//g_pD3DDevice->SetRenderTarget(0, pRenderSurface);

	//SAFE_RELEASE(pRenderSurface);

	//g_pD3DDevice->Clear(NULL,
	//	NULL,
	//	D3DCLEAR_TARGET,
	//	D3DCOLOR_XRGB(0, 0, 0),
	//	1.0f, 0);

	D3DXMATRIXA16 matWorld, matView, matProj;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXVECTOR3 vEye = g_pUnitManager->GetCamera()->GetEye();

	m_pEffect->SetMatrix("g_matWorld", &matWorld);
	m_pEffect->SetMatrix("g_matView", &matView);
	m_pEffect->SetMatrix("g_matProjection", &matProj);
	m_pEffect->SetVector("g_vWorldCameraPos", &D3DXVECTOR4(vEye.x, vEye.y, vEye.z, 1.f));

	m_pEffect->SetTexture("DurotarDirt_Tex", NULL);
	m_pEffect->SetTexture("DurotarDirtSmooth_Tex", NULL);
	m_pEffect->SetTexture("DurotarGrass_Tex", NULL);

	m_pEffect->SetTexture("DurotarDirt_s_Tex", NULL);
	m_pEffect->SetTexture("DurotarDirtSmooth_s_Tex", NULL);
	m_pEffect->SetTexture("DurotarGrass_s_Tex", NULL);

	m_pEffect->SetTexture("kalimdor_37_32adt_Heightmap_LOD_Tex", NULL);

	UINT uiPasses;
	m_pEffect->Begin(&uiPasses, NULL);
	for (UINT i = 0; i < uiPasses; ++i)
	{
		m_pEffect->BeginPass(i);
		for (size_t i = 0; i < m_vecViewMap.size(); ++i)
		{
			EnterCriticalSection(&cs_tile);
			if (m_vecViewMap[i] && g_pFrustum->IsIn(&m_vecViewMap[i]->GetFrustumSphere()))
				m_vecViewMap[i]->Render();
			LeaveCriticalSection(&cs_tile);
		}
		m_pEffect->EndPass();
	}
	m_pEffect->End();

	//g_pD3DDevice->SetRenderTarget(0, pOrgRenderSurface);
	//SAFE_RELEASE(pOrgRenderSurface);

	//vector<D3DXVECTOR3> vecVertex;

	//vecVertex.push_back(D3DXVECTOR3(-1.f, -1.f, 0.f));
	//vecVertex.push_back(D3DXVECTOR3(-1.f, 1.f, 0.f));
	//vecVertex.push_back(D3DXVECTOR3(1.f, 1.f, 0.f));

	//vecVertex.push_back(D3DXVECTOR3(1.f, 1.f, 0.f));
	//vecVertex.push_back(D3DXVECTOR3(1.f, -1.f, 0.f));
	//vecVertex.push_back(D3DXVECTOR3(-1.f, -1.f, 0.f));

	//g_pD3DDevice->SetFVF(D3DFVF_XYZ);

	//LPD3DXEFFECT pEffect = g_pShaderManager->getEffect("hdr.fx");
	//pEffect->SetTexture("Coin_Tex", pRenderTarget);
	//pEffect->Begin(&uiPasses, NULL);
	//for (UINT i = 0; i < uiPasses; ++i)
	//{
	//	pEffect->BeginPass(i);
	//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	//		2, &vecVertex[0],
	//		sizeof(D3DXVECTOR3));
	//	pEffect->EndPass();
	//}
	//pEffect->End();

	//SAFE_RELEASE(pRenderTarget);
}

void cTileManager::Destroy()
{
	for (size_t i = 0; i < m_vecLoadMap.size(); ++i)
	{
		SAFE_RELEASE(m_vecLoadMap[i]);
	}
}

//void cTileManager::AddMap(string sName, cHeightMap* pMap)
//{
//	m_mapHeight[sName] = pMap;
//}


//클릭은 음...최대한 적게
bool cTileManager::GetHeight(OUT D3DXVECTOR3& vDest, D3DXVECTOR3 vPos)
{
	ST_CHUNK stChunk = GetChunk(D3DXVECTOR3(vPos.x, 0, vPos.z));
	D3DXVECTOR3 vFloor1, vFloor2;

	bool OnBuilding = false;
	if (g_pIntersectManager->IntersectInBuilding(((cUnit*)m_pTarget)->GetFrustumSphere(), vPos, vFloor1))
	{
		OnBuilding = true;
	}

	EnterCriticalSection(&cs_tile);
	for each(auto v in m_vecViewMap)
	{
		if (v && v->GetChunk() == stChunk)
		{
			float y;
			v->GetHeight(vPos.x, vPos.z, y);
			vFloor2 = D3DXVECTOR3(vPos.x, y, vPos.z);
			break;
		}
	}

	if (OnBuilding)
	{
		if (vFloor1.y > vFloor2.y)
			vDest = vFloor1;
		else
			vDest = vFloor2;
		LeaveCriticalSection(&cs_tile);
		return true;
	}
	else
	{
		vDest = vFloor2;
		LeaveCriticalSection(&cs_tile);
		return true;
	}

	LeaveCriticalSection(&cs_tile);
	return false;
}

bool cTileManager::GetPickingMapPos(OUT D3DXVECTOR3& vDest)
{
	cRay r = cRay::GetRayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);

	EnterCriticalSection(&cs_tile);
	for each(auto p in m_vecViewMap)
	{
		if (p && r.IsPicked(&p->m_stFrustumSphere))
		{
			D3DXVECTOR3 vDests;
			D3DXVECTOR3 vPos(0, 0, 0);
			if (r.GetPickedPosition(vDests, p->m_pMesh, vPos))
			{
				vDest = vDests;
				LeaveCriticalSection(&cs_tile);
				return true;
			}
		}
	}
	LeaveCriticalSection(&cs_tile);
	return false;
}

bool cTileManager::GetPickingPos(OUT D3DXVECTOR3& vDest)
{
	D3DXVECTOR3 vPick;
	if (g_pIntersectManager->PickingInBuilding(vPick))
	{
		vDest = vPick;
		return true;
	}

	if (GetPickingMapPos(vPick))
	{
		vDest = vPick;
		return true;
	}

	return false;
}

//for (size_t i = 0; i < p.second->m_vecVertex.size(); i += 3)
//{
//	if (r.GetPickedPosition(vDests,
//		vPos + p.second->m_vecVertex[i],
//		vPos + p.second->m_vecVertex[i + 1],
//		vPos + p.second->m_vecVertex[i + 2]))
//	{
//		vDest = vDests;
//		return true;
//	}
//}
