#pragma once

#include "iEffect.h"

class cEffectCleave : public iEffect
{
public:
	cEffectCleave();
	virtual ~cEffectCleave();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

