#pragma once

#include "iEffect.h"
#include "cDamageText.h"


class cEffectFont : public iEffect
{
public:
	enum eFontState
	{
		E_BASIC,
		E_SKILL
	};

protected:
	cDamageText* m_pPont;
	SYNTHESIZE(int, m_nDamage, Damage);
	SYNTHESIZE(eFontState, m_eFontState, FontState);
public:
	cEffectFont();
	virtual ~cEffectFont();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

