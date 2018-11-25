#pragma once
#include "cBuff.h"
#include "iUnitAction.h"

class cBuffStun : public cBuff
{
protected:
	//float		m_fOrgSpeed;
	iUnitAction* m_pAction;
	cSkinnedMesh* m_pOwnerMesh;
	SYNTHESIZE(float, m_fStunTime, StunTime);
	SYNTHESIZE(DWORD, m_dwStunAnim, StunAnim);
public:
	cBuffStun();
	~cBuffStun();

	virtual void Start();
	virtual void Update();
};

