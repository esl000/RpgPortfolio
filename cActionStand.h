#pragma once

#include "iUnitAction.h"

class cActionStand : public iUnitAction
{
protected:
	cSkinnedMesh*	m_pOwnerMesh;
public:
	cActionStand();
	virtual ~cActionStand();

	virtual void Start() override;
	virtual void Update() override;


};