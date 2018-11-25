#pragma once

#include "cUIObject.h"
#include "cUIButton.h"

class cUIImageView;
class cDeviceManager;
class cUnitPlayer;
class cUIInvenTory;
class cEquip;



class cUIStatus
	: public cUIObject
	, public iUIButtonDelegate
{
private:
	RECT						m_aRect[5];
	D3DXVECTOR3					m_vPos;
	cUIImageView*				m_pUIImageView;
	LPD3DXFONT					m_pFont;
	char						m_szFont[128];
	bool						m_bDrag;
	SYNTHESIZE(bool, m_bStatus, StatusCheck);
	SYNTHESIZE(cEquip*, m_pEquip, Equip);
public:
	cUIStatus(void);
	virtual ~cUIStatus();
public:
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void OnClick(cUIButton* pButton);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void StatusFont();
	void StatusDisplay();
	void StatusDrag();
	void KeyCheck();
	void StatusCalc(int nType);
};

