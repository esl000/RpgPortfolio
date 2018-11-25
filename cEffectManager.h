#pragma once

#define g_pEffectManager cEffectManager::GetInstance()

#include "iEffect.h"

class cEffectManager : public iEffectDelegate
{
private:
	set<iEffect*> m_setEffects;
	vector<iEffect*> m_vecDeletePool;
public:
	SINGLETONE(cEffectManager);

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual void Destroy();

	virtual void RegisterEffect(iEffect* pEffect);
	virtual void OnEffectFinish(iEffect* pEffect);

	virtual iEffect* PickingDieEffect(cRay r);
};

