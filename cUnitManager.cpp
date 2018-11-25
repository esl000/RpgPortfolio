#include "stdafx.h"
#include "cUnitManager.h"
#include "cUnitPlayer.h"


cUnitManager::cUnitManager()
	: m_pPlayer(NULL)
	, m_pCamera(NULL)
{
}


cUnitManager::~cUnitManager()
{
}

void cUnitManager::Setup()
{
	m_setUnit.clear();
}

void cUnitManager::Destroy()
{
	for each(auto p in m_setUnit)
	{
		if (p)
			SAFE_RELEASE(p);
	}
}

void cUnitManager::RegisterUnit(cUnit* pUnit)
{
	pUnit->SetUnitDelegate(this);
	m_setUnit.insert(pUnit);
	pUnit->AddRef();
	g_pEntityManager->RegisterEntity(pUnit);
}

set<cUnit*>* cUnitManager::GetSetUnits()
{
	return &m_setUnit;
}

void cUnitManager::onUnitDelete(cUnit* pUnit)
{
	m_setUnit.erase(pUnit);
	if (m_pPlayer->GetTarget() == pUnit)
		m_pPlayer->SetTarget(NULL);
	pUnit->GetDelegate()->onEntityDelete(pUnit);
	SAFE_RELEASE(pUnit);
}

