#pragma once

#include "cUIObject.h"

#define COUNT 8

class cUIObject;
class cUISkillInvenTory;
class cUIPlayerBar;
class cUIStore; 

//테스트 클래스
class cUIInterface
	: public cUIObject
{
private:
	enum eUI
	{
		E_STAT = 0,
		E_BAG = 1
	};
private:
	cUISkillInvenTory*	m_pSkillInvenTory;
	cUIPlayerBar*		m_pUIPlayerBar;
	cUIStore*			m_pUIStore;
	LPD3DXFONT			m_pFont;
	bool				m_bTest;
	SYNTHESIZE(bool, m_bInvenTory, InvenTory);
public:
	cUIInterface(void);
	virtual ~cUIInterface(void);

public:
	virtual void Setup();
	virtual void Update();
	virtual void Render();
public:
	void KeyCheck();
	void InterfaceFont();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};



