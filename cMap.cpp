#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
	: m_pMesh(NULL)
	, m_pTexture(NULL)
	, m_dTile(2048)
{
}


cMap::~cMap()
{
	SAFE_RELEASE(m_pMesh);
}

cMap* cMap::GetInstance()
{
	static cMap instance;
	return &instance;
}

void cMap::Load(LPVOID pThis)
{
	cMap* pMap = (cMap*)pThis;

	LPD3DXMESH pMesh;

	string sFull = pMap->m_sFolder + string("/") + pMap->m_sTextureName;
	LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFull);
	std::vector<ST_PNT_VERTEX> vecVertex(pMap->m_dTile * pMap->m_dTile);
	pMap->m_vecPosition.resize(pMap->m_dTile * pMap->m_dTile);

	FILE* fp;
	string sFullPath = pMap->m_sFolder + string("/") + pMap->m_sFileName;
	fopen_s(&fp, sFullPath.c_str(), "r");

	for (int i = 0; i < pMap->m_dTile * pMap->m_dTile; ++i)
	{
		float x, z, y;
		fscanf_s(fp, " %f %f %f\n", &x, &z, &y);
		int nRow, nCol;
		nRow = (int)(z / 7.5f);
		nCol = (int)(x / 7.5f);

		pMap->m_vecPosition[nRow * pMap->m_dTile + nCol] = D3DXVECTOR3(nCol * 8, y, nRow * 8);
		vecVertex[nRow * pMap->m_dTile + nCol].p = D3DXVECTOR3(nCol * 8, y, nRow * 8);
		vecVertex[nRow * pMap->m_dTile + nCol].n = D3DXVECTOR3(0.f, 1.f, 0.f);
		vecVertex[nRow * pMap->m_dTile + nCol].t = D3DXVECTOR2(nCol / (float)pMap->m_dTile, nRow / (float)pMap->m_dTile);
	}

	fclose(fp);


	
	for (int z = 1; z < pMap->m_dTile - 1; ++z)
	{
		for (int x = 1; x < pMap->m_dTile - 1; ++x)
		{
			int l = (z + 0) * pMap->m_dTile + x - 1;
			int r = (z + 0) * pMap->m_dTile + x + 1;
			int u = (z + 1) * pMap->m_dTile + x + 0;
			int d = (z - 1) * pMap->m_dTile + x + 0;

			D3DXVECTOR3 du = vecVertex[u].p - vecVertex[d].p;
			D3DXVECTOR3 lr = vecVertex[r].p - vecVertex[l].p;
			D3DXVECTOR3 n;
			D3DXVec3Cross(&n, &du, &lr);
			D3DXVec3Normalize(&n, &n);
			int nIndex = (z + 0) * pMap->m_dTile + x - 0;
			vecVertex[nIndex].n = n;
		}
	}

	std::vector<DWORD> vecIndex;
	vecIndex.reserve(pMap->m_dTile * pMap->m_dTile * 3 * 2);

	// 1-3
	// |\|
	// 0-2

	for (int z = 0; z < pMap->m_dTile - 1; ++z)
	{
		for (int x = 0; x < pMap->m_dTile - 1; ++x)
		{
			int _0 = (z + 0) * pMap->m_dTile + x + 0;
			int _1 = (z + 1) * pMap->m_dTile + x + 0;
			int _2 = (z + 0) * pMap->m_dTile + x + 1;
			int _3 = (z + 1) * pMap->m_dTile + x + 1;
			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_2);

			vecIndex.push_back(_3);
			vecIndex.push_back(_2);
			vecIndex.push_back(_1);
		}
	}

	//EnterCriticalSection(&cs);
	D3DXCreateMeshFVF(vecIndex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&pMesh);

	//LeaveCriticalSection(&cs);
	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, sizeof(DWORD) * vecIndex.size() / 3);
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecIndex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0],
		0, 0, 0);


	D3DMATERIAL9 mtl;
	ZeroMemory(&mtl, sizeof(D3DMATERIAL9));
	mtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	mtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	mtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	EnterCriticalSection(&cs);
	pMap->m_stMtl = mtl;
	pMap->m_pTexture = pTexture;
	pMap->m_pMesh = pMesh;
	LeaveCriticalSection(&cs);
}

void cMap::Setup()
{
	DWORD dwThID;
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Load, this, NULL/*CREATE_SUSPENDED*/, &dwThID));
}

void cMap::Update()
{

}

void cMap::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	if (m_pMesh)
		m_pMesh->DrawSubset(0);
}

bool cMap::GetHeight(IN float x, IN float z, OUT float& y)
{
	return false;
}

void cMap::Destroy()
{
	SAFE_RELEASE(m_pMesh);
}
