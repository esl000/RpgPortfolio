#pragma once

#include "iUnitAction.h"

class cPlayerActionBackMove : public iUnitAction
{
protected:
	cSkinnedMesh*	m_pOwnerMesh;
	SYNTHESIZE(DWORD, m_dwWalkAnim, WalkAnim);

public:
	cPlayerActionBackMove();
	virtual ~cPlayerActionBackMove();

	virtual void Start() override;
	virtual void Update() override;
};

