#include "stdafx.h"
#include "cEntityManager.h"


cEntityManager::cEntityManager()
{
}


cEntityManager::~cEntityManager()
{
}

void cEntityManager::Setup()
{

}

void cEntityManager::Update()
{
	for each(auto p in m_setEntity)
	{
		if (p && g_pTileManager->IsMovementRange(p->GetPosition(), p->GetEntityType()))
			p->Update();
	}
}

void cEntityManager::Render()
{
	for each(auto p in m_setEntity)
	{
		if (p && g_pFrustum->IsIn(&p->GetFrustumSphere()) && g_pTileManager->IsMovementRange(p->GetPosition(), p->GetEntityType()))
		{
			p->Render();
		}
	}
}

void cEntityManager::Destroy()
{
	for each(auto p in m_setEntity)
	{
		if (p)
			SAFE_RELEASE(p);
	}
}

void cEntityManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		for each(auto p in m_setEntity)
		{
			if (p)
				p->WndProc(hWnd, message, wParam, lParam);
		}
		break;
	//case WM_LBUTTONDOWN:
	//	for each(auto p in m_setEntity)
	//	{
	//		if (p)
	//			p->WndProc(hWnd, message, wParam, lParam);
	//	}
	//	break;
	//case WM_RBUTTONDOWN:
	//	for each(auto p in m_setEntity)
	//	{
	//		if (p)
	//			p->WndProc(hWnd, message, wParam, lParam);
	//	}
	//	break;
	}
}

void cEntityManager::RegisterEntity(cEntity* pEntity)
{
	pEntity->SetDelegate(this);
	m_setEntity.insert(pEntity);
}
set<cEntity*>* cEntityManager::GetSetEntitys()
{
	return &m_setEntity;
}

void cEntityManager::onEntityDelete(cEntity* pEntity)
{
	m_setEntity.erase(pEntity);
	g_pIntersectManager->Synchronization(pEntity);
	SAFE_RELEASE(pEntity);
}
