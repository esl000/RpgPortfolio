#pragma once
#include "cUIObject.h"
class cUIBossBar :
	public cUIObject
{
public:
	cUIBossBar();
	virtual ~cUIBossBar();
	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

