#pragma once

#include "cInvenTory.h"

class cCustomQuest;

class iQuestDelegate
{
public:
	virtual void OnQuestFinished(cCustomQuest* pQuest) = 0;
};

class cCustomQuest
{
	friend class cQuestDatabase;
private:
	//머니 렌더
	//int money
	//gold = money / 10000
	//silver = money / 100 - gold * 100
	//bronze = money - silver * 100 - gold * 10000
	//10405
	//1골드 4실버 5브론즈
	//-------

	//main || sub
	//일 안합니까?
	SYNTHESIZE(string, m_sQuestKind, QuestKind);
	//조건
	SYNTHESIZE(DWORD, m_dwLevel, Level);
	SYNTHESIZE(string, m_sPrevQuest, PrevQuest); 
	//전에 완료해야하는퀘스트 ?무슨 퀘스트 교체요? 네 네 다음퀘스트를 받을수 있는권한이 생긴거죠 
	//설명
	SYNTHESIZE(string, m_sName, Name);
	SYNTHESIZE(string, m_sLore, Lore);
	//완료조건
	SYNTHESIZE(string, m_sTarget, Target);
	SYNTHESIZE(int, m_nTargetDeath, TargetDeath);
	SYNTHESIZE(int, m_nCurrentTargetDeath, CurrentTargetDeath);
	SYNTHESIZE(string, m_sTakeitem, Takeitem);
	SYNTHESIZE(int, m_nTakeitemAmount, TakeitemAmount);
	SYNTHESIZE(bool, m_bQuestEnd, QuestEnd);
	//보상
	SYNTHESIZE(int, m_nExp, Exp);
	SYNTHESIZE(int, m_nMoney, Money);
	SYNTHESIZE(string, m_sGiveitems, Giveitems);
	SYNTHESIZE(iQuestDelegate*, m_pDelegate, Delegate);
public:
	cCustomQuest();
	~cCustomQuest();

	void Update();

	bool CheckItem(cInvenTory* pInventory);
	void TakeItem(cInvenTory* pInventory);
	bool CheckFinish();
};

