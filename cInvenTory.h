#pragma once

#include "cItem.h"

//Item(Slot) - Setting
class cInvenTory
	: public cUIObject
{
private:
	cItem*				m_rcSlot[ITEM_Y][ITEM_X];
public:
	cInvenTory();
	virtual ~cInvenTory();
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	cItem* GetItem(int y, int x);
	void AddItem(cItem* pItem);
	void AddItem(cItem* pItem, int y, int x);
	cItem* RemoveItem(int y, int x);
};

