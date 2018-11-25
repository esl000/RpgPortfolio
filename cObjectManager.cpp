#include "StdAfx.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager(void)
{
}


cObjectManager::~cObjectManager(void)
{
}

void cObjectManager::AddObject( cObject* pObject )
{
	m_setObject.insert(pObject);
}

void cObjectManager::RemoveObject( cObject* pObject )
{
	m_setObject.erase(pObject);
}

void cObjectManager::Destroy()
{
	assert(m_setObject.empty() && "cObject를 상속받아 생성된 인스턴스 중 해제되지 않은 인스턴스가 있습니다.");
}

void cObjectManager::AddAutoReleasePool( cObject* pObject )
{
	m_vecAutoRelease.push_back(pObject);
}

void cObjectManager::Drain()
{
	for (size_t i = 0; i < m_vecAutoRelease.size(); ++i)
	{
		SAFE_RELEASE(m_vecAutoRelease[i]);
	}
	m_vecAutoRelease.clear();
}
