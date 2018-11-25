#pragma once
#include "cObject.h"

class cGameObject;

class cAction;

class iActionDelegate
{
public:
	virtual void OnActionFinish(cAction* pSender) = 0;
};

class cAction : public cObject
{
protected:
	float m_fCurrentTime;
	SYNTHESIZE(cGameObject*, m_pOwner, Owner);
	SYNTHESIZE(iActionDelegate*, m_pDelegate, Delegate);
	//SYNTHESIZE(float, m_fPlayTime, PlayTime);

public:
	virtual void Start() = 0;
	virtual void Update() = 0;

	cAction();
	virtual ~cAction();
};

