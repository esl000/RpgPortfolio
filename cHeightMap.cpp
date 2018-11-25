#include "StdAfx.h"
#include "cHeightMap.h"


cHeightMap::cHeightMap(void)
	: m_pMesh(NULL)
	, m_pTexture(NULL)
	, m_pEffect(NULL)
	, m_vChunk(0, 0)
	, m_stFrustumSphere()
{
	m_pTextureBlending = NULL;
	for (int i = 0; i < 3; ++i)
	{
		m_pDiffuseTexture[i] = NULL;
		m_pSpecularTexture[i] = NULL;
	}
}


cHeightMap::~cHeightMap(void)
{
	SAFE_RELEASE(m_pMesh);
}

void cHeightMap::Load( char* szFolder, char* szRawFile, char* szTexture, int nBytePerColor /*= 1*/ )
{
	std::string sFolder(szFolder);
	std::string sFullPath(szRawFile);

	sFullPath = sFolder + std::string("/") + sFullPath;

	m_sTexure = sFolder + std::string("/") + std::string(szTexture);

	FILE* fp = NULL;
	FILE* fpRight = NULL;
	FILE* fpBottom = NULL;
	FILE* fpRightBottom = NULL;

	char szTextures[1024];
	sprintf_s(szTextures, "kalimdor_%d_%d.adt_Heightmap_LOD.png", m_stIndex.x, m_stIndex.z);

	string sTexBlending = sFolder + std::string("/") + std::string(szTextures);

	m_pTextureBlending = g_pTextureManager->GetTexture(sTexBlending);

	sprintf_s(szTextures, "kalimdor_%d_%d.adt_Heightmap_LOD.txt", m_stIndex.x, m_stIndex.z);

	string sTexPath = sFolder + std::string("/") + std::string(szTextures);

	fopen_s(&fp, sTexPath.c_str(), "r");

	char szBuf[1024];
	char* szContext;
	if (fp)
	{
		for (int i = 0; i < 3; ++i)
		{
			fgets(szBuf, 1024, fp);
			char* szToken = strtok_s(szBuf, "\n", &szContext);
			string sTexPath1 = sFolder + std::string("/") + std::string(szToken) + std::string(".png");
			m_pDiffuseTexture[i] = g_pTextureManager->GetTexture(sTexPath1);
			string sTexPath2 = sFolder + std::string("/") + std::string(szToken) + std::string("_s.png");
			m_pSpecularTexture[i] = g_pTextureManager->GetTexture(sTexPath2);
		}
	}

	char szPath[3][1024];
	sprintf_s(szPath[0], "kalimdor_%d_%d.adt_Heightmap_LOD.raw", m_stIndex.x + 1, m_stIndex.z);
	sprintf_s(szPath[1], "kalimdor_%d_%d.adt_Heightmap_LOD.raw", m_stIndex.x, m_stIndex.z + 1);
	sprintf_s(szPath[2], "kalimdor_%d_%d.adt_Heightmap_LOD.raw", m_stIndex.x + 1, m_stIndex.z + 1);

	string sPath[3];
	sPath[0] = string("map/kalimdor") + string("/") + string(szPath[0]);
	sPath[1] = string("map/kalimdor") + string("/") + string(szPath[1]);
	sPath[2] = string("map/kalimdor") + string("/") + string(szPath[2]);

	m_pTexture = g_pTextureManager->GetTexture(m_sTexure);


	fopen_s(&fp, sFullPath.c_str(), "rb");
	fopen_s(&fpRight, sPath[0].c_str(), "rb");
	fopen_s(&fpBottom, sPath[1].c_str(), "rb");
	fopen_s(&fpRightBottom, sPath[2].c_str(), "rb");


	int nRowCount = 128;


	int nTile = nRowCount - 1;
	m_nTile = nTile;

	std::vector<ST_PNT_VERTEX> vecVertex;
	vecVertex.resize((nRowCount + 1) * (nRowCount + 1));
	m_vecVertex.resize((nRowCount + 1) * (nRowCount + 1));

	for (int z = nRowCount; z >= 0; --z)
	{
		for (int x = 0; x <= nRowCount; ++x)
		{
			if (x == nRowCount)
			{
				float y = 0;
				if (z == 0)
				{
					if (fpRightBottom)
					{
						y = (float)fgetc(fpRightBottom) / 2.0f;
					}
				}
				else if (fpRight)
				{
					fseek(fpRight, nRowCount * (nRowCount - z), SEEK_SET);
					y = (float)fgetc(fpRight) / 2.0f;
				}
				ST_PNT_VERTEX v;
				v.p = D3DXVECTOR3(x * 4 + m_vChunk.x, y, z * 4 + m_vChunk.z);
				v.n = D3DXVECTOR3(0, 1, 0);
				v.t = D3DXVECTOR2(3 * x / (float)nRowCount, 3 * (nRowCount - z) / (float)nRowCount);
				vecVertex[z * (nRowCount + 1) + x] = v;
				m_vecVertex[z * (nRowCount + 1) + x] = v.p;
				continue;
			}

			if (z == 0)
			{
				float y = 0;
				if (fpBottom)
				{
					fseek(fpBottom, x, SEEK_SET);
					y = (float)fgetc(fpBottom) / 2.0f;
				}
				ST_PNT_VERTEX v;
				v.p = D3DXVECTOR3(x * 4 + m_vChunk.x, y, z * 4 + m_vChunk.z);
				v.n = D3DXVECTOR3(0, 1, 0);
				v.t = D3DXVECTOR2(3 * x / (float)nRowCount, 3 * (nRowCount - z) / (float)nRowCount);
				vecVertex[z * (nRowCount + 1) + x] = v;
				m_vecVertex[z * (nRowCount + 1) + x] = v.p;
				continue;
			}

			float y = (float)fgetc(fp) / 2.f;
			ST_PNT_VERTEX v;
			v.p = D3DXVECTOR3(x * 4 + m_vChunk.x, y, z * 4 + m_vChunk.z);
			v.n = D3DXVECTOR3(0, 1, 0);
			v.t = D3DXVECTOR2(3 * x / (float)nRowCount, 3 * (nRowCount - z) / (float)nRowCount);
			vecVertex[z * (nRowCount + 1) + x] = v;
			m_vecVertex[z * (nRowCount + 1) + x] = v.p;
		}
	}

	fclose(fp);

	if (fpRight)
		fclose(fpRight);
	if (fpBottom)
		fclose(fpBottom);
	if (fpRightBottom)
		fclose(fpRightBottom);


	for (int z = 1; z < nRowCount; ++z)
	{
		for (int x = 1; x < nRowCount; ++x)
		{
			int l = (z + 0) * (nRowCount + 1) + x - 1;
			int r = (z + 0) * (nRowCount + 1) + x + 1;
			int u = (z + 1) * (nRowCount + 1) + x + 0;
			int d = (z - 1) * (nRowCount + 1) + x + 0;

			D3DXVECTOR3 du = vecVertex[u].p - vecVertex[d].p;
			D3DXVECTOR3 lr = vecVertex[r].p - vecVertex[l].p;
			D3DXVECTOR3 n;
			D3DXVec3Cross(&n, &du, &lr);
			D3DXVec3Normalize(&n, &n);
			int nIndex = (z + 0) * (nRowCount + 1) + x - 0;
			vecVertex[nIndex].n = n;
		}
	}


	std::vector<DWORD> vecIndex;
	vecIndex.reserve(nRowCount * nRowCount * 3 * 2);
	// 1-3
	// |\|
	// 0-2
	for (int z = 0; z < nRowCount; ++z)
	{
		for (int x = 0; x < nRowCount; ++x)
		{
			int _0 = (z + 0) * (nRowCount + 1) + x + 0;
			int _1 = (z + 1) * (nRowCount + 1) + x + 0;
			int _2 = (z + 0) * (nRowCount + 1) + x + 1;
			int _3 = (z + 1) * (nRowCount + 1) + x + 1;
			vecIndex.push_back(_0); 
			vecIndex.push_back(_1);
			vecIndex.push_back(_2);

			vecIndex.push_back(_3);
			vecIndex.push_back(_2);
			vecIndex.push_back(_1);
		}
	}

	D3DXComputeBoundingSphere(&vecVertex[0].p, vecVertex.size(), sizeof(ST_PNT_VERTEX), &m_stFrustumSphere.vCenter, &m_stFrustumSphere.fRadius);

	D3DXCreateMeshFVF(vecIndex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh);

	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, sizeof(DWORD) * vecIndex.size() / 3);
	m_pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecIndex.size());
	m_pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0],
		0, 0, 0);


	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f) * 0.6f;
	m_stMtl.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f) * 0.6f;
	m_stMtl.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f) * 0.6f;
	m_stMtl.Power = 1.f;
}

void cHeightMap::Render()
{
	//D3DXMATRIXA16 mat;
	//D3DXMatrixIdentity(&mat);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	//g_pD3DDevice->SetTexture(0, m_pTexture);
	//g_pD3DDevice->SetMaterial(&m_stMtl);

	if (m_pEffect)
	{
		m_pEffect->SetTexture("DurotarDirt_Tex", m_pDiffuseTexture[0]);
		m_pEffect->SetTexture("DurotarDirtSmooth_Tex", m_pDiffuseTexture[1]);
		m_pEffect->SetTexture("DurotarGrass_Tex", m_pDiffuseTexture[2]);

		m_pEffect->SetTexture("DurotarDirt_s_Tex", m_pSpecularTexture[0]);
		m_pEffect->SetTexture("DurotarDirtSmooth_s_Tex", m_pSpecularTexture[1]);
		m_pEffect->SetTexture("DurotarGrass_s_Tex", m_pSpecularTexture[2]);

		m_pEffect->SetTexture("kalimdor_37_32adt_Heightmap_LOD_Tex", m_pTextureBlending);
		m_pEffect->CommitChanges();

		m_pMesh->DrawSubset(0);
		//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

bool cHeightMap::GetHeight( IN float x, IN float z, OUT float& y )
{
	x -= m_vChunk.x;
	z -= m_vChunk.z;

	int nX = (int)(x / 4);
	int nZ = (int)(z / 4);

	if (nX < 0 || nZ < 0 || nX >= m_nTile + 1 || nZ >= m_nTile + 1)
	{
		y = 0.0f;
		return false;
	}

	int _0 = (nZ + 0) * (m_nTile + 2) + nX + 0;
	int _1 = (nZ + 1) * (m_nTile + 2) + nX + 0;
	int _2 = (nZ + 0) * (m_nTile + 2) + nX + 1;
	int _3 = (nZ + 1) * (m_nTile + 2) + nX + 1;

	// 1-3
	// |\|
	// 0-2

	float fDeltaX = (x - nX * 4) / 4.f;
	float fDeltaZ = (z - nZ * 4) / 4.f;

	if(fDeltaX + fDeltaZ < 1)
	{
		D3DXVECTOR3 _01 = m_vecVertex[_1] - m_vecVertex[_0];
		D3DXVECTOR3 _02 = m_vecVertex[_2] - m_vecVertex[_0];
		D3DXVECTOR3 v = _01 * fDeltaZ + _02 * fDeltaX;
		y = m_vecVertex[_0].y + v.y;
	}
	else
	{
		fDeltaX = 1.0f - fDeltaX;
		fDeltaZ = 1.0f - fDeltaZ;

		D3DXVECTOR3 _31 = m_vecVertex[_1] - m_vecVertex[_3];
		D3DXVECTOR3 _32 = m_vecVertex[_2] - m_vecVertex[_3];
		D3DXVECTOR3 v = _31 * fDeltaX + _32 * fDeltaZ;
		y = m_vecVertex[_3].y + v.y;
	}

	return true;
}
