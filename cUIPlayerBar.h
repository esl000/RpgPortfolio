#pragma once
#include "cUIObject.h"

#define COUNT 3

class cUIObject;
class cUIImageView;
class cUIInvenTory;
class cUIStatus;
class cUIMiniMap;
class cItem;

class cUIPlayerBar :
	public cUIObject
{
private:
	cUIInvenTory*		m_pUIInvenTory;
	cUIImageView*		m_pUIImageView;
	cUIStatus*			m_pUIStatus;
	cUIMiniMap*			m_pUIMiniMap;
	cUIImageView*		m_pInterface[COUNT];
	cUIImageView*		m_pUIImageItem[INTERFACE_X];
	SYNTHESIZE(TCHAR, m_szFont[128], Font);
	SYNTHESIZE(bool, m_bTest, Test);
	SYNTHESIZE(bool, m_bInvenTory, InvenTory);
	SYNTHESIZE(float, m_fGauge, Gauge);
	SYNTHESIZE(char, m_sNameData[128], NameData);
	SYNTHESIZE(D3DXVECTOR3, m_vPos, vPos);
public:
	cUIPlayerBar();
	virtual ~cUIPlayerBar();
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	void FontData();
	void FontDraw();
};

