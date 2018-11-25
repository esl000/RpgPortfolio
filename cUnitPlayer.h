#pragma once

#include "iUnitAction.h"
#include "cBuff.h"
#include "cPlayerAction.h"
#include "cText.h"

class cQuestList;
class cInvenTory;
class cEquip;
class cSkyBox;

//Test
class cUIMonsterBar;
class cSkillInven;
class cSkillAd;

class cUnitPlayer : public cUnit
	, public iUnitActionDelegate
	, public iBuffDelegate
{
	friend class cPlayerAction;
public:
	enum PLAYERJOB
	{
		E_WARRIOR = 0,
		E_MAGE,
		E_PRIEST
	};
protected:
	cText* m_pName;
	cUIMonsterBar* m_pMonsterBar;
	bool m_bOpenQuestList;
	cSkyBox* m_pSky;

	SYNTHESIZE(cQuestList*, m_pQuestList, QuestList);
	SYNTHESIZE(cInvenTory*, m_pInventory, Inventory);
	SYNTHESIZE(cEquip*, m_pEquip, Equip);
	SYNTHESIZE(int, m_nCurrentExp, CurrentExp);
	SYNTHESIZE(int, m_nMaxExp, MaxExp);
	SYNTHESIZE(PLAYERJOB, m_eJob, Job);
	
	SYNTHESIZE(cSkillInven*, m_pSkillInven, SkillInven);
private:
	std::map<string, cCustomQuest*> m_mapCompleteQuest;
public:
	cUnitPlayer();
	virtual ~cUnitPlayer();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	virtual void OnUnitActionFinish(iUnitAction* pAction);
	virtual void OnBuffFinished(cBuff* pBuff);

	D3DXVECTOR3* GetPos();
	void Save();
	void Load();
	void OpenQuestList();
	void OpenInvenTory();
	void OpenStatus();
	void SetCompleteQuest(cCustomQuest* pQuest);
	cCustomQuest* GetCompleteQuest(string QuestName);
};

