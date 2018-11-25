#include "stdafx.h"
#include "cDataload.h"
#include "cEntityBuilding.h"
#include "cEntityObject.h"
#include "cUnit.h"
#include "cUnitMonster.h"
#include "cUnitCustomNpc.h"


cDataload::cDataload()
{
}


cDataload::~cDataload()
{
}

void cDataload::GameLoad(ST_CHUNK_INDEX stIndex)
{
	vector<cEntity*> vecEntity;

	FILE* fp;
	char szPath[1024];
	sprintf_s(szPath, "save/SaveFile_%d_%d.txt", stIndex.x, stIndex.z);

	fopen_s(&fp, szPath, "r");
	if (!fp)
		return;
	int nEntitySize = 0;
	fscanf_s(fp, "%d\n", &nEntitySize);
	for (int i = 0; i < nEntitySize; ++i)
	{
		char szBuf[1024];
		fgets(szBuf, 1024, fp);

		char* szToken = NULL;
		char* szContext = NULL;
		szToken = strtok_s(szBuf, ",\n", &szContext);
		std::string sName(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		int nEntityType = atoi(szToken);

		cEntity* p;
		if (nEntityType == cEntity::E_BUILDING)
		{
			cEntityBuilding* pEntity = g_pBuildingDatabase->GetBuilding(sName);
			EnterCriticalSection(&cs);
			g_pEntityManager->RegisterEntity(pEntity);
			LeaveCriticalSection(&cs);
			p = pEntity;
		}
		else if (nEntityType == cEntity::E_OBJECT)
		{
			cEntityObject* pEntity = g_pObjectDatabase->GetObjects(sName);
			EnterCriticalSection(&cs);
			g_pEntityManager->RegisterEntity(pEntity);
			LeaveCriticalSection(&cs);
			p = pEntity;
		}
		else if (nEntityType == cEntity::E_UNIT)
		{
			szToken = strtok_s(szContext, ",\n", &szContext);
			if (atoi(szToken) == cUnit::E_MONSTER)
			{
				cUnitMonster* pEntity = g_pMonsterDatabase->GetMonster(sName);
				EnterCriticalSection(&cs);
				g_pUnitManager->RegisterUnit(pEntity);
				LeaveCriticalSection(&cs);
				p = pEntity;
			}
			else if (atoi(szToken) == cUnit::E_NPC)
			{
				cUnitCustomNpc* pEntity = g_pNpcDatabase->GetCustomNpc(sName);
				EnterCriticalSection(&cs);
				g_pUnitManager->RegisterUnit(pEntity);
				LeaveCriticalSection(&cs);
				p = pEntity;
			}
			//szToken = strtok_s(szContext, ",\n", &szContext);
		}
		D3DXVECTOR3 vPos;

		szToken = strtok_s(szContext, ",\n", &szContext);
		vPos.x = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vPos.y = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vPos.z = atof(szToken);

		p->SetPosition(vPos);

		D3DXVECTOR3 vDir;

		szToken = strtok_s(szContext, ",\n", &szContext);
		vDir.x = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vDir.y = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vDir.z = atof(szToken);

		p->SetDirection(vDir);
		p->Setup();
	}
	fclose(fp);
}

void cDataload::Load(vector<cEntity*>& vecEntity)
{
	FILE* fp;
	fopen_s(&fp, "SaveFile.txt", "r");
	if (!fp)
		return;
	int nEntitySize = 0;
	fscanf_s(fp, "%d\n", &nEntitySize);
	vecEntity.reserve(nEntitySize);
	for (int i = 0; i < nEntitySize; ++i)
	{
		char szBuf[1024];
		fgets(szBuf, 1024, fp);

		char* szToken = NULL;
		char* szContext = NULL;
		szToken = strtok_s(szBuf, ",\n", &szContext);
		std::string sName(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		int nEntityType = atoi(szToken);

		cEntity* p;
		if (nEntityType == cEntity::E_BUILDING)
		{
			cEntityBuilding* pEntity = g_pBuildingDatabase->GetBuilding(sName);
			p = pEntity;
		}
		else if (nEntityType == cEntity::E_OBJECT)
		{
			cEntityObject* pEntity = g_pObjectDatabase->GetObjects(sName);
			p = pEntity;
		}
		else if (nEntityType == cEntity::E_UNIT)
		{
			szToken = strtok_s(szContext, ",\n", &szContext);
			if (atoi(szToken) == cUnit::E_MONSTER)
			{
				cUnitMonster* pEntity = g_pMonsterDatabase->GetMonster(sName);
				p = pEntity;
			}
			else if (atoi(szToken) == cUnit::E_NPC)
			{
				cUnitCustomNpc* pEntity = g_pNpcDatabase->GetCustomNpc(sName);
				p = pEntity;
			}
		}
		D3DXVECTOR3 vPos;

		szToken = strtok_s(szContext, ",\n", &szContext);
		vPos.x = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vPos.y = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vPos.z = atof(szToken);

		p->SetPosition(vPos);

		D3DXVECTOR3 vDir;

		szToken = strtok_s(szContext, ",\n", &szContext);
		vDir.x = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vDir.y = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vDir.z = atof(szToken);

		p->SetDirection(vDir);
		p->Setup();
		vecEntity.push_back(p);
	}
	fclose(fp);
}

void cDataload::Load(vector<cEntity*>& vecEntity, ST_CHUNK_INDEX stIndex)
{
	FILE* fp;
	char szPath[1024];
	sprintf_s(szPath, "save/SaveFile_%d_%d.txt", stIndex.x, stIndex.z);

	fopen_s(&fp, szPath, "r");
	if (!fp)
		return;
	int nEntitySize = 0;
	fscanf_s(fp, "%d\n", &nEntitySize);
	vecEntity.reserve(nEntitySize);
	for (int i = 0; i < nEntitySize; ++i)
	{
		char szBuf[1024];
		fgets(szBuf, 1024, fp);

		char* szToken = NULL;
		char* szContext = NULL;
		szToken = strtok_s(szBuf, ",\n", &szContext);
		std::string sName(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		int nEntityType = atoi(szToken);

		cEntity* p;
		if (nEntityType == cEntity::E_BUILDING)
		{
			cEntityBuilding* pEntity = g_pBuildingDatabase->GetBuilding(sName);
			p = pEntity;
		}
		else if (nEntityType == cEntity::E_OBJECT)
		{
			cEntityObject* pEntity = g_pObjectDatabase->GetObjects(sName);
			p = pEntity;
		}
		else if (nEntityType == cEntity::E_UNIT)
		{
			szToken = strtok_s(szContext, ",\n", &szContext);
			if (atoi(szToken) == cUnit::E_MONSTER)
			{
				cUnitMonster* pEntity = g_pMonsterDatabase->GetMonster(sName);
				p = pEntity;
			}
			else if (atoi(szToken) == cUnit::E_NPC)
			{
				cUnitCustomNpc* pEntity = g_pNpcDatabase->GetCustomNpc(sName);
				p = pEntity;
			}
		}
		D3DXVECTOR3 vPos;

		szToken = strtok_s(szContext, ",\n", &szContext);
		vPos.x = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vPos.y = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vPos.z = atof(szToken);

		p->SetPosition(vPos);

		D3DXVECTOR3 vDir;

		szToken = strtok_s(szContext, ",\n", &szContext);
		vDir.x = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vDir.y = atof(szToken);

		szToken = strtok_s(szContext, ",\n", &szContext);
		vDir.z = atof(szToken);

		p->SetDirection(vDir);
		EnterCriticalSection(&cs);
		p->Setup();
		vecEntity.push_back(p);
		LeaveCriticalSection(&cs);
	}
	fclose(fp);
}

void cDataload::Save(vector<cEntity*>& vecEntity)
{
	FILE* fp;
	fopen_s(&fp, "SaveFile.txt", "w");
	
	fprintf_s(fp, "%d\n", vecEntity.size());
	for each(auto p in vecEntity)
	{
		char szBuf[1024];
		if (p->GetEntityType() == cEntity::E_BUILDING)
		{
			cEntityBuilding* pEntity = (cEntityBuilding*)p;		
			sprintf_s(szBuf, ",%.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",
			pEntity->GetPosition().x,
			pEntity->GetPosition().y,
			pEntity->GetPosition().z,
			pEntity->GetDirection().x,
			pEntity->GetDirection().y,
			pEntity->GetDirection().z);
			string s = pEntity->GetName() + string(",") + string("0") + string(szBuf);
			cout << s.c_str() << endl;
			fputs(s.c_str(), fp);
		}
		else if (p->GetEntityType() == cEntity::E_OBJECT)
		{
			cEntityObject* pEntity = (cEntityObject*)p;
			sprintf_s(szBuf, ",%.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",
				pEntity->GetPosition().x,
				pEntity->GetPosition().y,
				pEntity->GetPosition().z,
				pEntity->GetDirection().x,
				pEntity->GetDirection().y,
				pEntity->GetDirection().z);
			string s = pEntity->GetName() + string(",") + string("1") + string(szBuf);
			cout << s.c_str() << endl;
			fputs(s.c_str(), fp);
		}
		else if (p->GetEntityType() == cEntity::E_UNIT)
		{
			cUnit* pUnit = (cUnit*)p;
			if (pUnit->GetUnitType() == cUnit::E_MONSTER)
			{
				cUnitMonster* pEntity = (cUnitMonster*)p;
				sprintf_s(szBuf, ",%.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",
					pEntity->GetPosition().x,
					pEntity->GetPosition().y,
					pEntity->GetPosition().z,
					pEntity->GetDirection().x,
					pEntity->GetDirection().y,
					pEntity->GetDirection().z);
				string s = pEntity->GetName() + string(",") + string("2") + string(",0") + string(szBuf);
				cout << s.c_str() << endl;
				fputs(s.c_str(), fp);
			}
			else if (pUnit->GetUnitType() == cUnit::E_NPC)
			{
				cUnitCustomNpc* pEntity = (cUnitCustomNpc*)p;
				sprintf_s(szBuf, ",%.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",
					pEntity->GetPosition().x,
					pEntity->GetPosition().y,
					pEntity->GetPosition().z,
					pEntity->GetDirection().x,
					pEntity->GetDirection().y,
					pEntity->GetDirection().z);
				string s = pEntity->GetName() + string(",") + string("2") + string(",1") + string(szBuf);
				cout << s.c_str() << endl;
				fputs(s.c_str(), fp);
			}
		}
	}
	fclose(fp);
}

void cDataload::Save(vector<cEntity*>& vecEntity, ST_CHUNK_INDEX stIndex)
{
	FILE* fp;
	char szPath[1024];

	sprintf_s(szPath, "save/SaveFile_%d_%d.txt", stIndex.x, stIndex.z);

	fopen_s(&fp, szPath, "w");

	int nSize = 0;
	for each(auto p in vecEntity)
	{
		if (GetChunkIndex(p->GetPosition()) == stIndex)
			++nSize;
	}

	fprintf_s(fp, "%d\n", nSize);
	for each(auto p in vecEntity)
	{

		if (GetChunkIndex(p->GetPosition()) != stIndex)
			continue;
		char szBuf[1024];
		if (p->GetEntityType() == cEntity::E_BUILDING)
		{
			cEntityBuilding* pEntity = (cEntityBuilding*)p;
			sprintf_s(szBuf, ",%.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",
				pEntity->GetPosition().x,
				pEntity->GetPosition().y,
				pEntity->GetPosition().z,
				pEntity->GetDirection().x,
				pEntity->GetDirection().y,
				pEntity->GetDirection().z);
			string s = pEntity->GetName() + string(",") + string("0") + string(szBuf);
			cout << s.c_str() << endl;
			fputs(s.c_str(), fp);
		}
		else if (p->GetEntityType() == cEntity::E_OBJECT)
		{
			cEntityObject* pEntity = (cEntityObject*)p;
			sprintf_s(szBuf, ",%.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",
				pEntity->GetPosition().x,
				pEntity->GetPosition().y,
				pEntity->GetPosition().z,
				pEntity->GetDirection().x,
				pEntity->GetDirection().y,
				pEntity->GetDirection().z);
			string s = pEntity->GetName() + string(",") + string("1") + string(szBuf);
			cout << s.c_str() << endl;
			fputs(s.c_str(), fp);
		}
		else if (p->GetEntityType() == cEntity::E_UNIT)
		{
			cUnit* pUnit = (cUnit*)p;
			if (pUnit->GetUnitType() == cUnit::E_MONSTER)
			{
				cUnitMonster* pEntity = (cUnitMonster*)p;
				sprintf_s(szBuf, ",%.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",
					pEntity->GetPosition().x,
					pEntity->GetPosition().y,
					pEntity->GetPosition().z,
					pEntity->GetDirection().x,
					pEntity->GetDirection().y,
					pEntity->GetDirection().z);
				string s = pEntity->GetName() + string(",") + string("2") + string(",0") + string(szBuf);
				cout << s.c_str() << endl;
				fputs(s.c_str(), fp);
			}
			else if (pUnit->GetUnitType() == cUnit::E_NPC)
			{
				cUnitCustomNpc* pEntity = (cUnitCustomNpc*)p;
				sprintf_s(szBuf, ",%.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",
					pEntity->GetPosition().x,
					pEntity->GetPosition().y,
					pEntity->GetPosition().z,
					pEntity->GetDirection().x,
					pEntity->GetDirection().y,
					pEntity->GetDirection().z);
				string s = pEntity->GetName() + string(",") + string("2") + string(",1") + string(szBuf);
				cout << s.c_str() << endl;
				fputs(s.c_str(), fp);
			}
		}
	}
	fclose(fp);
}
