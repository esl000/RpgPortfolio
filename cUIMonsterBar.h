#pragma once

#include "cUIObject.h"


class cUITextView;

class cUIMonsterBar
	: public cUIObject
{
private:
	SYNTHESIZE(cUIImageView*, m_pMonsterImage, m_pMonsterImage);
	SYNTHESIZE(cUIImageView*, m_pImage, ViewImage);
	SYNTHESIZE(cUITextView*, m_pText, TextView);
	SYNTHESIZE(cUnit*, m_pOwner, Owner);
public:
	cUIMonsterBar();
	virtual ~cUIMonsterBar();
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
};

