#pragma once

#include "iUnitAction.h"

class cPlayerActionRightTurn : public iUnitAction
{
protected:
	cSkinnedMesh* m_pOwnerMesh;

public:
	cPlayerActionRightTurn();
	virtual ~cPlayerActionRightTurn();

	virtual void Start() override;
	virtual void Update() override;
};

