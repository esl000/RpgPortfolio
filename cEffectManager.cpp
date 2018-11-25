#include "stdafx.h"
#include "cEffectManager.h"
#include "cDieEffect.h"


cEffectManager::cEffectManager()
{
}


cEffectManager::~cEffectManager()
{
}

void cEffectManager::Setup()
{
	m_setEffects.clear();
}

void cEffectManager::Update()
{
	for each(auto p in m_setEffects)
	{
		if (p)
			p->Update();
	}

	for (size_t i = 0; i < m_vecDeletePool.size(); ++i)
	{
		m_setEffects.erase(m_vecDeletePool[i]);
		SAFE_RELEASE(m_vecDeletePool[i])
	}
	m_vecDeletePool.clear();
}

void cEffectManager::Render()
{
	for each(auto p in m_setEffects)
	{
		if (p)
			p->Render();
	}
}

void cEffectManager::Destroy()
{
	for each(auto p in m_setEffects)
	{
		if (p)
			SAFE_RELEASE(p);
	}
}

void cEffectManager::RegisterEffect(iEffect* pEffect)
{
	pEffect->SetDelegate(this);
	m_setEffects.insert(pEffect);
}

void cEffectManager::OnEffectFinish(iEffect* pEffect)
{
	m_vecDeletePool.push_back(pEffect);
}

iEffect* cEffectManager::PickingDieEffect(cRay r)
{
	for each (auto p in m_setEffects)
	{
		if (p->GetEffectType() == iEffect::E_DIEEFFECT &&
			r.IsPicked(&p->GetFrustumSphere()) &&
			((cDieEffect*)p)->GetRootInv())
		{
			return p;
		}
	}
	return NULL;
}
