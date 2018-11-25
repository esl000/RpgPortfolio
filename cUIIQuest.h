#pragma once

#include "cUIObject.h"
#include "cUIButton.h"

class cUIImageView;
class cUITextView;
class cUIButton;

class cUIIQuest
	: public cUIObject
	, public iUIButtonDelegate
{
private:
	cUIImageView*		m_pUiImageView;
	cUITextView*		m_pUiTextView;
	
	SYNTHESIZE(cCustomQuest*, m_pQuest, Quest);
	SYNTHESIZE(bool, m_bEnd, BEnd);
	
public:
	cUIIQuest(void);
	virtual ~cUIIQuest(void);
public:
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void OnClick(cUIButton* pButton);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void QuestSend();
};

