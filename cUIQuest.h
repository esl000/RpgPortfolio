#pragma once
#include "cUIObject.h"
#include "cUIButton.h"

class cUIImageView;
class cUITextView;
class cUIButton;
class cQuestList;
class cInvenTory;


class cUIQuest
	: public cUIObject
	, public iUIButtonDelegate
{
private:
	cUIImageView* m_pUiImageView;
	cUITextView* m_pUiTextView;

	SYNTHESIZE(cCustomQuest*, m_pQuest, Quest);
	SYNTHESIZE(bool, m_bEnd,BEnd);

public:
	cUIQuest();
	~cUIQuest();
public:
	virtual void SetUp();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void OnClick(cUIButton* pButton);
	void QuestSend();
};

