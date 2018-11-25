#pragma once
#include "cObject.h"

#include "cAction.h"

class cGameObject : public cObject
{
protected:
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Direction);
	SYNTHESIZE_ADD_REF(cAction*, m_pAction, Action);

public:
	cGameObject(void);
	virtual ~cGameObject(void);

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

