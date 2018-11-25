#pragma once
#include "iUnitAction.h"
class cPlayerActionPosMove : public iUnitAction
{
	cSkinnedMesh* m_pOwnerMesh;
	SYNTHESIZE(D3DXVECTOR3, m_vDest, Dest);
	SYNTHESIZE(DWORD, m_dwWalkAnim, WalkAnim);
public:
	cPlayerActionPosMove();
	virtual ~cPlayerActionPosMove();

	virtual void Start();
	virtual void Update();
};

