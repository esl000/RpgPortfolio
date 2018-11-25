#pragma once

#include "iEffect.h"

class cEffectHit : public iEffect
{
public:
	cEffectHit();
	virtual ~cEffectHit();	

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

