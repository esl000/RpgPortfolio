#pragma once

#include "iUnitAction.h"

class cPlayerActionFrontMove : public iUnitAction
{
protected:
	cSkinnedMesh* m_pOwnerMesh;
	SYNTHESIZE(DWORD, m_dwWalkAnim, WalkAnim);

public:
	cPlayerActionFrontMove();
	virtual ~cPlayerActionFrontMove();

	virtual void Start() override;
	virtual void Update() override;
};

