#pragma once

#include "cCamera.h"

class cUnitPlayer;

#define g_pUnitManager cUnitManager::GetInstance()


class cUnitManager : public iUnitDelegate
{
private:
	set<cUnit*> m_setUnit;
	SYNTHESIZE(cUnitPlayer*, m_pPlayer, Player);
	SYNTHESIZE(cCamera*, m_pCamera, Camera);
public:
	SINGLETONE(cUnitManager);

	virtual void Setup();
	virtual void Destroy();

	virtual set<cUnit*>* GetSetUnits();
	virtual void RegisterUnit(cUnit* pUnit);
	virtual void onUnitDelete(cUnit* pUnit);
};

