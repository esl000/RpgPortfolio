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
	assert(m_setObject.empty() && "cObject�� ��ӹ޾� ������ �ν��Ͻ� �� �������� ���� �ν��Ͻ��� �ֽ��ϴ�.");
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
