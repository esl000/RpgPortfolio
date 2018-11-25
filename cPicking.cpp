#include "stdafx.h"
#include "cPicking.h"
#include "cHeightMap.h"
#include "cUnitCustomNpc.h"
#include "cUnitPlayer.h"
#include "cDieEffect.h"
#include "cRootItem.h"
#include "cUIRootItem.h"


cPicking::cPicking()
{
}


cPicking::~cPicking()
{
}

void cPicking::Setup()
{

}

void cPicking::Update()
{
	m_mapUse.clear();
}


//cPicking::E_LEFTCLICK || cPicking::E_RIGHCLICK
bool cPicking::PickingObjects(OUT D3DXVECTOR3& vDest, OUT cUnit** pTarget, int nClickType)
{
	if (m_mapUse.find(nClickType) != m_mapUse.end() && m_mapUse[nClickType])
		return false;

	cRay r = cRay::GetRayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);

	*pTarget = NULL;

	cDieEffect* pEffect = (cDieEffect*)g_pEffectManager->PickingDieEffect(r);

	if (pEffect)
	{
		cUIRootItem* pRootItem = new cUIRootItem;
		pRootItem->SetRootItem(pEffect->GetRootInv());
		pRootItem->Setup();
		g_pUImanager->RegisterUI(pRootItem);
		vDest = pEffect->GetPosition();
		return true;
	}

	for each(auto p in *g_pUnitManager->GetSetUnits())
	{
		if (p->GetUnitType() == cUnit::E_CHARACTER)
			continue;

		if (r.IsPicked(&p->GetFrustumSphere()))
		{
			*pTarget = p;
			//m_mapUse[nClickType] = true;
			vDest = p->GetPosition();
			return true;
		}
	}

	if (g_pTileManager->GetPickingPos(vDest))
	{
		//m_mapUse[nClickType] = true;
		return true;
	}
	else
		return false;

}

void cPicking::SetUse(int nClickType)
{
	m_mapUse[nClickType] = true;
}

bool cPicking::GetUse(int nClickType)
{
	if (m_mapUse.find(nClickType) != m_mapUse.end() && m_mapUse[nClickType])
		return false;
	else
		return true;
}
