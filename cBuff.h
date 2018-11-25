#pragma once

class cUnit;
class cBuff;

class iBuffDelegate
{
public:
	virtual void OnBuffFinished(cBuff* pBuff) = 0;
};

class cBuff : public cObject
{
protected:
	SYNTHESIZE(cUnit*, m_pOwner, Owner);
	SYNTHESIZE(iBuffDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(float, m_fPassedTime, m_fPassedTime);
public:
	cBuff();
	~cBuff();

	virtual void Start() = 0;
	virtual void Update() = 0;
};

