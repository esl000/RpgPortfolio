#include "stdafx.h"
#include "cIntersectManager.h"
#include "cEntityBuilding.h"
#include "cEntityObject.h"
#include "cOctree.h"
#include "cCulling.h"


cIntersectManager::cIntersectManager()
	: m_fSearchTime(3.f)
	, m_fCurrentTime(0.f)
	, m_fOctreeTime(1.f)
	, m_fCurrentOctTime(0.f)
{
}


cIntersectManager::~cIntersectManager()
{
}

void cIntersectManager::SearchEntitys(LPVOID pThis)
{
	cIntersectManager* in = (cIntersectManager*)pThis;
	ST_SPHERE stSphere;
	stSphere.vCenter = in->m_pTarget->GetFrustumSphere().vCenter;
	stSphere.fRadius = in->m_pTarget->GetFrustumSphere().fRadius + in->m_pTarget->GetCurrentSpeed() * 3.f;

	set<cEntity*> setPassEntity;
	for (size_t i = 0; i < in->m_vecNearEntity.size(); )
	{
		setPassEntity.insert(in->m_vecNearEntity[i]);
		if (!IntersectSphereSphere(stSphere, in->m_vecNearEntity[i]->GetFrustumSphere()))
		{
			EnterCriticalSection(&cs_intersect);
			in->m_vecNearEntity.erase(in->m_vecNearEntity.begin() + i);
			LeaveCriticalSection(&cs_intersect);
		}
		else	 ++i;
	}

	for each(auto p in *g_pEntityManager->GetSetEntitys())
	{
		if (setPassEntity.find(p) != setPassEntity.end())
			continue;
		if (IntersectSphereSphere(stSphere, p->GetFrustumSphere()))
		{
			EnterCriticalSection(&cs_intersect);
			in->m_vecNearEntity.push_back(p);
			LeaveCriticalSection(&cs_intersect);
			cout << "add Intersecter : " << p->GetEntityType() << endl;
		}
	}

	cout << "Entity Size : " << in->m_vecNearEntity.size() << endl;
}

void cIntersectManager::SearchOctrees(LPVOID pThis)
{
	cIntersectManager* in = (cIntersectManager*)pThis;
	ST_SPHERE stSphere;
	stSphere.vCenter = in->m_pTarget->GetPosition();
	stSphere.fRadius = 0;
	set<cOctree*> setOctree;
	vector<cEntity*> vecNearEntity;
	vecNearEntity.reserve(in->m_vecNearEntity.size());
	EnterCriticalSection(&cs_intersect);
	vecNearEntity = in->m_vecNearEntity;
	LeaveCriticalSection(&cs_intersect);

	for each(auto p in vecNearEntity)
	{
		if (p->GetEntityType() == cEntity::E_BUILDING)
		{
			cEntityBuilding* pBuilding = (cEntityBuilding*)p;
			if (IntersectSphereSphere(stSphere, pBuilding->GetFrustumSphere()))
			{
				if (pBuilding->GetOctree())
				{				
					pBuilding->GetOctree()->GetNearOctree(ST_SPHERE(in->m_pTarget->GetPosition(), 20), setOctree);			
				}
			}
		}
	}
	cout << "Octree size : " << setOctree.size() << endl;

	map<float, cOctree*> mapOctree;

	int nIndex = 0;
	for each(auto p in setOctree)
	{
			++nIndex;
			mapOctree[-p->GetSphere().vCenter.y + 0.03 * nIndex] = p;
	}

	EnterCriticalSection(&cs_intersect);
	in->m_vecOctree.clear();
	for each(auto p in mapOctree)
	{
		in->m_vecOctree.push_back(p.second);
	}
	LeaveCriticalSection(&cs_intersect);
}

void cIntersectManager::Setup()
{
	m_vecNearEntity.reserve(100);
}

void cIntersectManager::Update()
{
	m_fCurrentTime += g_pTimeManager->GetElapsedTime();
	m_fCurrentOctTime += g_pTimeManager->GetElapsedTime();
	if (m_fCurrentTime >= m_fSearchTime)
	{
		m_fCurrentTime = 0;
		//m_vecNearEntity.clear();
		DWORD dwThID;
		cout << "start Search!!!" << endl;
		CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SearchEntitys, this, NULL/*CREATE_SUSPENDED*/, &dwThID));
	}
	if (m_fCurrentOctTime >= m_fOctreeTime)
	{
		m_fCurrentOctTime = 0.f;
		DWORD dwThID;
		//cout << "start Search!!!" << endl;
		CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SearchOctrees, this, NULL/*CREATE_SUSPENDED*/, &dwThID));
	}
}

void cIntersectManager::Render()
{
	EnterCriticalSection(&cs_intersect);
	for each(auto p in m_vecOctree)
	{
		p->Render();
	}
	LeaveCriticalSection(&cs_intersect);
}

void cIntersectManager::Synchronization(cEntity* pEntity)
{
	EnterCriticalSection(&cs_intersect);
	for (size_t i = 0; i < m_vecNearEntity.size(); ++i)
	{
		if (pEntity == m_vecNearEntity[i])
		{
			m_vecNearEntity.erase(m_vecNearEntity.begin() + i);
			LeaveCriticalSection(&cs_intersect);
			return;
		}
	}
	LeaveCriticalSection(&cs_intersect);
}

bool cIntersectManager::IntersectEntitys(ST_SPHERE stBoundingSphere)
{
	EnterCriticalSection(&cs_intersect);
	for each(auto p in m_vecNearEntity)
	{
		if (p->GetEntityType() == cEntity::E_OBJECT)
		{
			cEntityObject* pObject = (cEntityObject*)p;
			D3DXVECTOR3 vPos = stBoundingSphere.vCenter;

			if (cCulling::IsIn(pObject->GetvecBB(), &stBoundingSphere))
			{
				LeaveCriticalSection(&cs_intersect);
				return true;
			}

			//float u, v, y;

			//D3DXVECTOR3	 vDir;

			//for (size_t i = 0; i < pObject->GetvecBB().size(); i += 3)
			//{
			//	D3DXVec3Cross(&vDir, &(pObject->GetvecBB()[i + 2] - pObject->GetvecBB()[i]), &(pObject->GetvecBB()[i + 1] - pObject->GetvecBB()[i]));
			//	D3DXVec3Normalize(&vDir, &vDir);
			//	if (D3DXIntersectTri(&pObject->GetvecBB()[i],
			//		&pObject->GetvecBB()[i + 1],
			//		&pObject->GetvecBB()[i + 2],
			//		&vPos,
			//		&vDir,
			//		&u, &v, &y))
			//	{
			//		if (y <= stBoundingSphere.fRadius)
			//		{
			//			LeaveCriticalSection(&cs_intersect);
			//			return true;
			//		}
			//	}
			//}
		}
	}
	LeaveCriticalSection(&cs_intersect);
	return false;
}

bool cIntersectManager::IntersectEntitys(ST_SPHERE stBoundingSphere, D3DXVECTOR3 vDir)
{
	EnterCriticalSection(&cs_intersect);
	for each(auto p in m_vecNearEntity)
	{
		if (p->GetEntityType() == cEntity::E_OBJECT)
		{
			cEntityObject* pObject = (cEntityObject*)p;
			D3DXVECTOR3 vPos = stBoundingSphere.vCenter;


			if (IsFocusSight(vPos, pObject->GetPosition(), vDir) &&
				cCulling::IsIn(pObject->GetvecBB(), &stBoundingSphere))
			{
				LeaveCriticalSection(&cs_intersect);
				return true;
			}
		}
	}
	LeaveCriticalSection(&cs_intersect);
	return false;
}

bool cIntersectManager::IntersectInBuilding(IN ST_SPHERE stBoundingSphere, IN D3DXVECTOR3 vTemp, OUT D3DXVECTOR3& vDest)
{
	D3DXVECTOR3 vOrg = D3DXVECTOR3(vTemp.x, vTemp.y + 2, vTemp.z);
	cRay r = cRay::GetCustomRay(vOrg, D3DXVECTOR3(0, -1, 0));
	EnterCriticalSection(&cs_intersect);
	for each(auto p in m_vecOctree)
	{
		if (p->OnlyPicking(r, vDest))
		{
			LeaveCriticalSection(&cs_intersect);
			return true;
		}
	}
	LeaveCriticalSection(&cs_intersect);
	return false;
}

bool cIntersectManager::PickingInBuilding(OUT D3DXVECTOR3& vDest)
{
	cRay r = cRay::GetRayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);
	EnterCriticalSection(&cs_intersect);
	for each(auto p in m_vecNearEntity)
	{
		if (p->GetEntityType() == cEntity::E_BUILDING)
		{
			cEntityBuilding* pBuilding = (cEntityBuilding*)p;
			if (r.IsPicked(&pBuilding->GetFrustumSphere()))
			{
				if (pBuilding->GetOctree())
				{
					D3DXVECTOR3	vFloor;
					if (pBuilding->GetOctree()->isPicked(r, vFloor))
					{
						vDest = vFloor;
						LeaveCriticalSection(&cs_intersect);
						return true;
					}
				}
			}
		}
	}
	LeaveCriticalSection(&cs_intersect);
	return false;
}
