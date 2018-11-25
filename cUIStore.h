#pragma once
#include "cUIObject.h"
#include "cUIButton.h"
#include "cItem.h"

class cItem;
class cUIImageView;

class cStore;
class cInvenTory;

class cUIStore 
	: public cUIObject
	, public iUIButtonDelegate
{
private:
	LPD3DXSPRITE			m_pSprite;
	cItem*                  m_aItem[5][2];
	RECT					m_rcStore[5][2];
	bool					m_bDrag;


public:
	cUIStore();
	virtual ~cUIStore();
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void OnClick(cUIButton* pButton);
	void PickStore();
};

