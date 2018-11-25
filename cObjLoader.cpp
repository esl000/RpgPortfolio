#include "StdAfx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cGroup.h"

cObjLoader::cObjLoader(void)
{
}


cObjLoader::~cObjLoader(void)
{
}

void cObjLoader::Load( IN char* szFullPath, OUT std::vector<cGroup*>& vecGroup )
{
	//std::vector<D3DXVECTOR3> vecV;
	//std::vector<D3DXVECTOR2> vecVT;
	//std::vector<D3DXVECTOR3> vecVN;
	//std::vector<ST_PNT_VERTEX> vecVertex;

	//FILE* fp = NULL;
	//fopen_s(&fp, szFullPath, "r");
	//while(true)
	//{
	//	if(feof(fp))
	//		break;

	//	char szBuf[1024] = {0, };
	//	fgets(szBuf, 1024, fp);

	//	if(strlen(szBuf) == 0)
	//		continue;

	//	if(szBuf[0] == '#')
	//	{
	//		continue;
	//	}
	//	else if(szBuf[0] == 'm')
	//	{
	//		char szMtlLibPath[1024];
	//		sscanf_s(szBuf, "%*s %s", szMtlLibPath, 1024);
	//		LoadMtlLib(sz, szMtlLibPath);
	//	}
	//	else if(szBuf[0] == 'g')
	//	{
	//		if(!vecVertex.empty())
	//		{
	//			cGroup* pGroup = vecGroup.back();
	//			pGroup->BuildVB(vecVertex);
	//			vecVertex.clear();
	//		}
	//	}
	//	else if(szBuf[0] == 'v')
	//	{
	//		if(szBuf[1] == ' ')
	//		{
	//			float x, y, z;
	//			sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
	//			vecV.push_back(D3DXVECTOR3(x, y, z));
	//		}
	//		else if(szBuf[1] == 't')
	//		{
	//			float u, v;
	//			sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
	//			vecVT.push_back(D3DXVECTOR2(u, v));
	//		}
	//		else if(szBuf[1] == 'n')
	//		{
	//			float x, y, z;
	//			sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
	//			vecVN.push_back(D3DXVECTOR3(x, y, z));
	//		}
	//	}
	//	else if(szBuf[0] == 'u')
	//	{ 
	//		char szMtlName[1024];
	//		sscanf_s(szBuf, "%*s %s", szMtlName, 1024);

	//		cGroup* pGroup = new cGroup;
	//		pGroup->SetMtlTex(m_mapMtlTex[szMtlName]);
	//		vecGroup.push_back(pGroup);
	//	}
	//	else if(szBuf[0] == 'f')
	//	{ 
	//		int aIndex[3][3];
	//		sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
	//			&aIndex[0][0], &aIndex[0][1], &aIndex[0][2], 
	//			&aIndex[1][0], &aIndex[1][1], &aIndex[1][2], 
	//			&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

	//		for (int i = 0; i < 3; ++i)
	//		{
	//			ST_PNT_VERTEX v;
	//			v.p = vecV[aIndex[i][0] - 1];
	//			v.t = vecVT[aIndex[i][1] - 1];
	//			v.n = vecVN[aIndex[i][2] - 1];
	//			vecVertex.push_back(v);
	//		}
	//	}
	//}
	//fclose(fp);

	//for each(auto it in m_mapMtlTex)
	//{
	//	SAFE_RELEASE(it.second);
	//}
	//m_mapMtlTex.clear();
}

LPD3DXMESH cObjLoader::Load(IN const char* szFolder, IN const char* szPath, OUT std::vector<cMtlTex*>& vecMtlTex, OUT ST_SPHERE& stBoundingSphere)
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::vector<DWORD>			vecAttrBuf;
	DWORD						dwAttrId = 0;

	string sPullPath = string(szFolder) + string("/") + string(szPath);

	FILE* fp = NULL;
	fopen_s(&fp, sPullPath.c_str(), "r");
	if (!fp)
		return NULL;

	while(true)
	{
		if(feof(fp))
			break;

		if (szPath == string("dalaranprison"))
		{
			int a = 0;
		}

		char szBuf[1024] = {0, };
		fgets(szBuf, 1024, fp);

		if(strlen(szBuf) == 0)
			continue;

		if(szBuf[0] == '#')
		{
			continue;
		}
		else if(szBuf[0] == 'm')
		{
			char szMtlLibPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlLibPath, 1024);
			LoadMtlLib(szFolder, szMtlLibPath);
		
			vecMtlTex.resize(m_mapMtlTex.size());
			for each(auto it in m_mapMtlTex)
			{
				vecMtlTex[it.second->m_nAttrId] = it.second;
			}
		}
		else if(szBuf[0] == 'g')
		{
		}
		else if(szBuf[0] == 'v')
		{
			if(szBuf[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if(szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if(szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if(szBuf[0] == 'u')
		{ 
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);

			dwAttrId = m_mapMtlTex[szMtlName]->m_nAttrId;
		}
		else if(szBuf[0] == 'f')
		{ 
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2], 
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2], 
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];
				vecVertex.push_back(v);
			}

			vecAttrBuf.push_back(dwAttrId);
		}
	}
	fclose(fp);

	D3DXComputeBoundingSphere(&vecVertex[0].p, vecVertex.size(), sizeof(ST_PNT_VERTEX), &stBoundingSphere.vCenter, &stBoundingSphere.fRadius);

	LPD3DXMESH pMesh = NULL;
	DWORD DWTest = vecVertex.size() / 3;
	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&pMesh);

	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrBuf[0], sizeof(DWORD) * vecAttrBuf.size());
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0],
		0, 0, 0);

	m_mapMtlTex.clear();

	return pMesh;
}

LPD3DXMESH cObjLoader::LoadObject(IN const char* szFolder, IN const char* szPath, OUT std::vector<cMtlTex*>& vecMtlTex, OUT std::vector<ST_BOUNDINGBOX>& vecBox, OUT ST_SPHERE& stBoundingSphere)
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::vector<DWORD>			vecAttrBuf;

	//ST_BOUNDINGBOX				stBB;
	DWORD						dwAttrId = 0;

	string sPullPath = string(szFolder) + string("/") + string(szPath);
	bool isBoundingBox = false;

	FILE* fp = NULL;
	fopen_s(&fp, sPullPath.c_str(), "r");
	if (!fp)
		return NULL;

	while (true)
	{
		if (feof(fp))
			break;

		if (szPath == string("dalaranprison"))
		{
			int a = 0;
		}

		char szBuf[1024] = { 0, };
		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0)
			continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'm')
		{
			char szMtlLibPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlLibPath, 1024);
			LoadMtlLib(szFolder, szMtlLibPath);

			vecMtlTex.resize(m_mapMtlTex.size());
			for each(auto it in m_mapMtlTex)
			{
				vecMtlTex[it.second->m_nAttrId] = it.second;
			}
		}
		else if (szBuf[0] == 'g')
		{
			isBoundingBox = false;
			char szGroupName[1024];
			sscanf_s(szBuf, "%*s %s", szGroupName, 1024);
			if (szGroupName[0] == 'b' &&
				szGroupName[1] == 'b' &&
				szGroupName[2] == '_')
			{
				isBoundingBox = true;
				ST_BOUNDINGBOX stBB;
				vecBox.push_back(stBB);
			}
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);

			dwAttrId = m_mapMtlTex[szMtlName]->m_nAttrId;
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			if (isBoundingBox)
			{
				ST_FACE stFace(vecV[aIndex[0][0] - 1],
					vecV[aIndex[1][0] - 1],
					vecV[aIndex[2][0] - 1]);
				vecBox.back().vecPosition.push_back(stFace);
			}
			else
			{
				for (int i = 0; i < 3; ++i)
				{
					ST_PNT_VERTEX v;
					v.p = vecV[aIndex[i][0] - 1];
					v.t = vecVT[aIndex[i][1] - 1];
					v.n = vecVN[aIndex[i][2] - 1];
					vecVertex.push_back(v);
				}
			}

			vecAttrBuf.push_back(dwAttrId);
		}
	}
	fclose(fp);

	D3DXComputeBoundingSphere(&vecVertex[0].p, vecVertex.size(), sizeof(ST_PNT_VERTEX), &stBoundingSphere.vCenter, &stBoundingSphere.fRadius);

	LPD3DXMESH pMesh = NULL;
	DWORD DWTest = vecVertex.size() / 3;
	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&pMesh);

	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrBuf[0], sizeof(DWORD) * vecAttrBuf.size());
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0],
		0, 0, 0);

	m_mapMtlTex.clear();

	return pMesh;
}

LPD3DXMESH cObjLoader::LoadSurface(IN const char* szFolder, IN const char* szPath, OUT std::vector<cMtlTex*>& vecMtlTex, OUT std::vector<ST_FACE>& vecFace)
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::vector<DWORD>			vecAttrBuf;
	DWORD						dwAttrId = 0;

	string sPullPath = string(szFolder) + string("/") + string(szPath);

	FILE* fp = NULL;
	fopen_s(&fp, sPullPath.c_str(), "r");
	if (!fp)
		return NULL;

	while (true)
	{
		if (feof(fp))
			break;

		if (szPath == string("dalaranprison"))
		{
			int a = 0;
		}

		char szBuf[1024] = { 0, };
		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0)
			continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'm')
		{
			char szMtlLibPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlLibPath, 1024);
			LoadMtlLib(szFolder, szMtlLibPath);

			vecMtlTex.resize(m_mapMtlTex.size());
			for each(auto it in m_mapMtlTex)
			{
				vecMtlTex[it.second->m_nAttrId] = it.second;
			}
		}
		else if (szBuf[0] == 'g')
		{
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);

			dwAttrId = m_mapMtlTex[szMtlName]->m_nAttrId;
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];
				vecVertex.push_back(v);
			}

			vecAttrBuf.push_back(dwAttrId);
		}
	}
	fclose(fp);

	for (size_t i = 0; i < vecVertex.size(); i += 3)
	{
		vecFace.push_back(ST_FACE(vecVertex[i].p, vecVertex[i + 1].p, vecVertex[i + 2].p));
	}

	LPD3DXMESH pMesh = NULL;
	DWORD DWTest = vecVertex.size() / 3;
	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&pMesh);

	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrBuf[0], sizeof(DWORD) * vecAttrBuf.size());
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0],
		0, 0, 0);

	m_mapMtlTex.clear();

	return pMesh;
}

void cObjLoader::LoadMtlLib(IN const char* szFolder, IN char* szPath)
{
	if (szPath == string("dalaranprison"))
	{
		int a = 0;
	}
	std::string sMtlName;

	string sPullPath = string(szFolder) + string("/") + string(szPath);

	int nAttrId = 0;

	FILE* fp = NULL;
	fopen_s(&fp, sPullPath.c_str(), "r");
	while(true)
	{
		if(feof(fp))
			break;

		char szBuf[1024] = {0, };
		fgets(szBuf, 1024, fp);

		if(strlen(szBuf) == 0)
			continue;

		if(szBuf[0] == '#')
		{
			continue;
		}
		else if(szBuf[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = szMtlName;

			//if (m_mapMtlTex.find(sMtlName) != m_mapMtlTex.end())
			//{
			//	cMtlTex* pMtl = new cMtlTex;
			//	pMtl->m_nAttrId = m_mapMtlTex[sMtlName]->
			//	SAFE_RELEASE(m_mapMtlTex[sMtlName]);
			//}
			if (m_mapMtlTex.find(sMtlName) == m_mapMtlTex.end())
			{
				m_mapMtlTex[sMtlName] = new cMtlTex;
				m_mapMtlTex[sMtlName]->m_nAttrId = nAttrId++;
			}
		}
		else if(szBuf[0] == 'K')
		{
			if(szBuf[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->m_stMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if(szBuf[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->m_stMtl.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
				m_mapMtlTex[sMtlName]->m_stMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if(szBuf[1] == 's')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->m_stMtl.Specular = D3DXCOLOR(r, g, b, 1.0f);
			}
		}
		else if(szBuf[0] == 'm')
		{
			char szTexturePath[1024];
			sscanf_s(szBuf, "%*s %s", szTexturePath, 1024);
			string sTexturePath = string(szFolder) + string("/") + string(szTexturePath);
			m_mapMtlTex[sMtlName]->m_pTexture = g_pTextureManager->GetTexture(sTexturePath);
		}
	}
	fclose(fp);
}
