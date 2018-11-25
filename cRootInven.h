#pragma once
#include "cUIObject.h"

class cItem;

class cRootInven :
	public cUIObject
{
private:
	cItem*			m_pRcRootItem[4];

public:
	cRootInven();
	virtual ~cRootInven();
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	cItem* GetItem(int y);
	cItem* RemoveItem(int y);
	void InitItem();
	void AddItem(cItem* pItem);
	void AddItem(cItem* pItem, int y);	
};

