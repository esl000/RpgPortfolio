#pragma once
#include "cUIObject.h"
#include "cUIButton.h"

class cItem;
class cUIImageView;
class cEquip;
class cInvenTory;
class cRootItem;

//Error : Path, pSprite, PtInRect, "{}"
class cUIRootItem 
	: public cUIObject
	, public iUIButtonDelegate
{
private:
	bool				m_bDrag;
	RECT				m_rc[4];
	cUIImageView*		m_pUIImageView;
	SYNTHESIZE(cRootItem*, m_pRootItem, RootItem);
public:
	cUIRootItem();
	virtual ~cUIRootItem();
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	void PickItem();
	void RootBox();
	virtual void OnClick(cUIButton* pButton);
	
};

