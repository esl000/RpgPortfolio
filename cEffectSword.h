#pragma once

#include "iEffect.h"
#include "cEffectTriangle.h"

class cEffectSword : public iEffect
{
protected:
	D3DXVECTOR3				m_vPrevPos[2];
	ST_BONE*				m_pFindMesh;
	vector<ST_PC_VERTEX>	m_vecVertex;
	vector<cEffectTriangle*> m_vecTriangle;

	SYNTHESIZE(float, m_fColorChangeTime, ColorChangeTime);
	SYNTHESIZE(D3DXCOLOR, m_cFaceColor, FaceColor);
	SYNTHESIZE(cSkinnedMesh*, m_pOwnerMesh, OwnerMesh);
public:
	cEffectSword();
	virtual ~cEffectSword();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

