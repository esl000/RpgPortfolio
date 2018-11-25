#pragma once

#include "iUnitAction.h"

class cPlayerActionLeftTurn : public iUnitAction
{
protected:
	cSkinnedMesh* m_pOwnerMesh;

public:
	cPlayerActionLeftTurn();
	virtual ~cPlayerActionLeftTurn();

	virtual void Start() override;
	virtual void Update() override;
};

