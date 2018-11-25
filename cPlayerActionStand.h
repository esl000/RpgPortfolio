#pragma once

#include "iUnitAction.h"

class cPlayerActionStand :public iUnitAction
{
protected:
	cSkinnedMesh* m_pOwnerMesh;

	SYNTHESIZE(DWORD, m_dwStandAnim, StandAnim);
public:
	cPlayerActionStand();
	virtual ~cPlayerActionStand();

	virtual void Start() override;
	virtual void Update() override;

};

