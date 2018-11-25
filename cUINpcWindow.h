#pragma once

#include "cUIObject.h"
#include "cUIButton.h"

class cUIImageView;
class cUITextView;
class cUIButton;
class cUnitCustomNpc;

class cUINpcWindow 
	: public cUIObject
	, public iUIButtonDelegate
{
public:
	cUIImageView*	m_pUiImageView;
	cUITextView*		m_pUiTextView;
	SYNTHESIZE(cUnitCustomNpc*, m_pNpc, Npc);
public:
	cUINpcWindow();
	~cUINpcWindow();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void OnClick(cUIButton* pButton);
};

