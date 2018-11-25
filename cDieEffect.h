#pragma once
#include "iEffect.h"

class cRootItem;

class cDieEffect : public iEffect
{
protected:
	SYNTHESIZE(cRootItem*, m_pRootInv, RootInv);
	SYNTHESIZE(DWORD, m_dwDeadAnim, DeadAnim);
public:
	cDieEffect();
	virtual ~cDieEffect();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

