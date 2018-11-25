#include "stdafx.h"
#include "iEffect.h"


iEffect::iEffect()
	: m_pMesh(NULL)
	, m_pDelegate(NULL)
	, m_pUnit(NULL)
	, m_fMaxTime(0.f)
	, m_fCurrentTime(0.f)
	, m_eEffectType(E_NONE)
{
}


iEffect::~iEffect()
{
	SAFE_DELETE(m_pMesh);
}
