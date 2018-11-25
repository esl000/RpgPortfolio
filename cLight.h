#pragma once

#include  "cAction.h"

class cLight : public cGameObject
{
protected:
	SYNTHESIZE(int, m_nIndex, Index);
	SYNTHESIZE(D3DLIGHT9, m_lLight, Light);
	SYNTHESIZE_ADD_REF(cAction*, m_pAction, Action);

public:
	virtual void Setup() override;
	virtual void Update() override;

	cLight();
	~cLight();
};

