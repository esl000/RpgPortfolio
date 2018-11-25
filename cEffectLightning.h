#pragma once

#include "iEffect.h"

class cEffectLightning : public iEffect
{
public:
	cEffectLightning();
	virtual ~cEffectLightning();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

