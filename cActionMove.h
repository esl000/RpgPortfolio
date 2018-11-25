#pragma once

#include "iUnitAction.h"

class cActionMove : public iUnitAction
{
protected:
	cSkinnedMesh*		m_pOwnerMesh;
	SYNTHESIZE(D3DXVECTOR3, m_vDest, Dest);
	SYNTHESIZE(D3DXVECTOR3, m_vInitDir, InitDir);
	SYNTHESIZE(DWORD, m_dwWalkAnim, WalkAnim);
public:
	cActionMove();
	~cActionMove();

	virtual void Start() override;
	virtual void Update() override;
};

