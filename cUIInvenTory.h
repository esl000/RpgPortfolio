#pragma once

#include "cUIObject.h"
#include "cUIButton.h"
#include "cInvenTory.h"
#include "cUITextView.h"

class cObject;
class cUIImageView;
class cDeviceManager;
class cInvenTory;
class cItem;
class cUIStatus;

//Monitor(Collision)
class cUIInvenTory
	: public cUIObject
	, public iUIButtonDelegate
{
private:
	SYNTHESIZE(cInvenTory*, m_pInventory, pInvenTory);

	RECT						m_aPickRect[ITEM_Y][ITEM_X];
	cUIImageView*				m_pItem;
	cUIImageView*				m_pUIInvenTory;
	D3DXVECTOR3					m_vPos;
	DWORD						m_dwCurrentIndex[2];
	cItem*						m_pCurrentItem;
	bool						m_bWindowSound;
	bool						m_bButtonSound;
	char						m_szFont[128];
	LPD3DXFONT					m_pFont;
	SYNTHESIZE(bool, m_bInvenToryMax, InvenToryMax);
	SYNTHESIZE(bool, m_bClick, Click);
	SYNTHESIZE(bool, m_bCheck, Check);
	SYNTHESIZE(bool, m_bExit, Exit);
	SYNTHESIZE(bool, m_bButton, Button);
	SYNTHESIZE(bool, m_bDrag, Drag);
	SYNTHESIZE(bool, m_bSwap, Swap);
	SYNTHESIZE(bool, m_bCollision, Collision);
	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	SYNTHESIZE(D3DXIMAGE_INFO, m_stImageInfo, stImageInfo);
	SYNTHESIZE(cUITextView*, m_pText, TextView);
public:
	cUIInvenTory();
	virtual ~cUIInvenTory();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void OnClick(cUIButton* pButton);
	void InvenToryDrag();
	void InvenFont();
	void InvenDisplay();
	void InvenCalc(int nType);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

