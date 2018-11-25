#pragma once

#include "iEffect.h"

class cEffectSlow : public iEffect
{
public:
	cEffectSlow();
	virtual ~cEffectSlow();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

