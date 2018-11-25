#pragma once

class cItem;

class cEquip : public cObject
{

protected:
	cItem*				m_aItem[5];
public:
	cEquip();
	virtual ~cEquip();

	virtual void SetUp();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	virtual void SetEquip(int nType, cItem* pItem);
	virtual cItem* GetItem(int nType);
	virtual cItem* RemoveEquip(int nType);
};

