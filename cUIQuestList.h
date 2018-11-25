#pragma once
#include "cUIObject.h"
#include "cUIButton.h"

class cUIImageView;
class cUITextView;
class cUIButton;
class cQuestList;

class cUIQuestList :
	public cUIObject,
	public iUIButtonDelegate
{
private:
	cUIImageView*	m_pUiImageView;
	cUITextView*	m_pUiTextView;
	cUITextView*	m_pUiTextViewSecond;
	vector<string> m_vecQuestName;

	//Ä¿·»Æ® 
	SYNTHESIZE(cQuestList*, m_pList, QuestList);
	SYNTHESIZE(cCustomQuest*, m_pCurrentQuest, Quest);

public:
	cUIQuestList();
	~cUIQuestList();

public:
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void OnClick(cUIButton* pButton);
};

