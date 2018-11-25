#include "stdafx.h"
#include "cObjectDatabase.h"
#include "cObjLoader.h"
#include "cCustomFile.h"
#include "cEntityObject.h"


cObjectDatabase::cObjectDatabase()
{
	Load();
}


cObjectDatabase::~cObjectDatabase()
{
}

void cObjectDatabase::Load()
{
	std::set<string> setKeys;
	setKeys.insert(string("name"));
	setKeys.insert(string("mesh_folder"));
	setKeys.insert(string("mesh_file"));
	setKeys.insert(string("collision"));
	setKeys.insert(string("isbb"));
	setKeys.insert(string("x"));
	setKeys.insert(string("y"));
	setKeys.insert(string("z"));


	FILE* fp;
	fopen_s(&fp, "object/objectSize.txt", "r");
	if (!fp)
		return;

	int dwSize = 0;
	fscanf_s(fp, "%d", &dwSize);
	fclose(fp);

	if (dwSize <= 0)
		return;

	std::map<string, string> mapData;

	for (int i = 0; i < dwSize; ++i)
	{
		char szBuf[1024];
		string sPath("object/_");
		sprintf(szBuf, "%d", i);
		sPath += string(szBuf) + string(".txt");
		if (cCustomFile::LoadCustomFile(sPath.c_str(), setKeys, mapData))
		{
			cEntityObject* object = new cEntityObject;
			object->m_sName = mapData[string("name")];

			if (mapData.find(string("isbb")) != mapData.end() &&
				atoi(mapData[string("isbb")].c_str()) == 1)
			{
				D3DXCreateBox(g_pD3DDevice, atof(mapData[string("x")].c_str()),
					atof(mapData[string("y")].c_str()),
					atof(mapData[string("z")].c_str()),
					&object->m_pBoundingBox, NULL);

				ST_PN_VERTEX* pVertex;
				WORD* pI;

				object->m_pBoundingBox->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVertex);
				object->m_pBoundingBox->LockIndexBuffer(D3DLOCK_READONLY, (LPVOID*)&pI);

				for (size_t i = 0; i < object->m_pBoundingBox->GetNumFaces() * 3; i++)
				{
					object->m_vecBoudingBox.push_back(pVertex[pI[i]].p);
				}

				object->m_pBoundingBox->UnlockIndexBuffer();
				object->m_pBoundingBox->UnlockVertexBuffer();

				object->m_vBoundingBoxCenter = D3DXVECTOR3(0, 0, 0);

				object->m_bCollision = true;

				m_mapObject[object->m_sName] = object;
				m_vecObject.push_back(object);
				mapData.clear();

				object->m_stFrustumSphere = ST_SPHERE(object->m_vBoundingBoxCenter, atof(mapData[string("x")].c_str()) / 2.f);
				continue;
			}

			object->m_pObjMesh = g_pObjManager->GetObj(object->m_vecMtl, object->m_stFrustumSphere, mapData[string("mesh_folder")].c_str(), mapData[string("mesh_file")].c_str());
			
			object->m_bCollision = atoi(mapData[string("collision")].c_str());

			D3DXVECTOR3* pV;
			D3DXVECTOR3 vMin, vMax;
			
			if (object->m_bCollision)
			{
				object->m_pObjMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pV);
				D3DXComputeBoundingBox(pV,
				object->m_pObjMesh->GetNumVertices(),
				object->m_pObjMesh->GetNumBytesPerVertex(),
				&vMin, &vMax);

				object->m_pObjMesh->UnlockVertexBuffer();
			}

			D3DXCreateBox(g_pD3DDevice, vMax.x - vMin.x, (vMax.y - vMin.y) * 1.5f, vMax.z - vMin.z, &object->m_pBoundingBox, NULL);


			ST_PN_VERTEX* pVertex;
			WORD* pI;
			
			object->m_pBoundingBox->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVertex);
			object->m_pBoundingBox->LockIndexBuffer(D3DLOCK_READONLY, (LPVOID*)&pI);

			for (size_t i = 0; i < object->m_pBoundingBox->GetNumFaces() * 3; i++)
			{
				object->m_vecBoudingBox.push_back(pVertex[pI[i]].p);
			}

			object->m_pBoundingBox->UnlockIndexBuffer();
			object->m_pBoundingBox->UnlockVertexBuffer();

			object->m_vBoundingBoxCenter = (vMin + vMax) / 2.f;

			m_mapObject[object->m_sName] = object;
			m_vecObject.push_back(object);
		}
		mapData.clear();
	}
}

cEntityObject* cObjectDatabase::GetObjects(string sName)
{
	if (m_mapObject.find(sName) == m_mapObject.end())
		return NULL;
	else
	{
		cEntityObject* object = new cEntityObject;
		object->SetEntityType(cEntity::E_OBJECT);
		object->m_sName = m_mapObject[sName]->GetName();
		object->m_isBBox = m_mapObject[sName]->m_isBBox;
		m_mapObject[sName]->m_pBoundingBox->AddRef();
		if (m_mapObject[sName]->m_pObjMesh)
			m_mapObject[sName]->m_pObjMesh->AddRef();
		object->m_pObjMesh = m_mapObject[sName]->m_pObjMesh;
		object->m_vecMtl = m_mapObject[sName]->m_vecMtl;
		object->m_stFrustumSphere = m_mapObject[sName]->m_stFrustumSphere;
		object->m_bCollision = m_mapObject[sName]->m_bCollision;

		if (object->m_bCollision)
		{
			object->m_pBoundingBox = m_mapObject[sName]->m_pBoundingBox;
			object->m_vecBoudingBox = m_mapObject[sName]->m_vecBoudingBox;
		}
		return object;
	}
}

cEntityObject* cObjectDatabase::GetObjects(int& nIndex)
{
	nIndex %= m_vecObject.size();
	cEntityObject* object = new cEntityObject;
	object->m_sName = m_vecObject[nIndex]->GetName();
	object->m_isBBox = m_vecObject[nIndex]->m_isBBox;
	object->SetEntityType(cEntity::E_OBJECT);
	if (m_vecObject[nIndex]->m_pObjMesh)
		m_vecObject[nIndex]->m_pObjMesh->AddRef();
	m_vecObject[nIndex]->m_pBoundingBox->AddRef();
	object->m_pObjMesh = m_vecObject[nIndex]->m_pObjMesh;
	object->m_sName = m_vecObject[nIndex]->m_sName;
	object->m_vecMtl = m_vecObject[nIndex]->m_vecMtl;
	object->m_stFrustumSphere = m_vecObject[nIndex]->m_stFrustumSphere;
	object->m_bCollision = m_vecObject[nIndex]->m_bCollision;

	if (object->m_bCollision)
	{
		object->m_vecBoudingBox = m_vecObject[nIndex]->m_vecBoudingBox;
		object->m_pBoundingBox = m_vecObject[nIndex]->m_pBoundingBox;
	}
	return object;
}

void cObjectDatabase::Destroy()
{
	for each(auto p in m_mapObject)
	{
		//for each(auto mtl in p.second->m_vecMtl)
		//{
		//	SAFE_RELEASE(mtl);
		//}
		SAFE_RELEASE(p.second);
	}
}
