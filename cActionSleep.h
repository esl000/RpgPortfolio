#pragma once

#include "iUnitAction.h"

class cActionSleep : public iUnitAction
{
protected:
	cSkinnedMesh* m_pOwnerMesh;
public:
	cActionSleep();
	virtual ~cActionSleep();


	virtual void Start() override;
	virtual void Update() override;
};

