#pragma once

#include "iEffect.h"

class cEffectCyclone : public iEffect
{
protected:
	D3DXVECTOR3 m_vOrgTargetPos;
public:
	cEffectCyclone();
	virtual ~cEffectCyclone();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

