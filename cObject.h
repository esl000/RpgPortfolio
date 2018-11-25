#pragma once

class cObject
{
protected:
	int m_nRefCount;

public:
	cObject(void);
	virtual ~cObject(void);

	virtual void AddRef();
	virtual void Release();
	virtual void AutoRelease();
};

