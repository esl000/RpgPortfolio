#pragma once

#include "iEffect.h"

class cEffectLightningNova : public iEffect
{
protected:

public:
	cEffectLightningNova();
	virtual ~cEffectLightningNova();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

