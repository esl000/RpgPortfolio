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
	//�Ӵ� ����
	//int money
	//gold = money / 10000
	//silver = money / 100 - gold * 100
	//bronze = money - silver * 100 - gold * 10000
	//10405
	//1��� 4�ǹ� 5�����
	//-------

	//main || sub
	//�� ���մϱ�?
	SYNTHESIZE(string, m_sQuestKind, QuestKind);
	//����
	SYNTHESIZE(DWORD, m_dwLevel, Level);
	SYNTHESIZE(string, m_sPrevQuest, PrevQuest); 
	//���� �Ϸ��ؾ��ϴ�����Ʈ ?���� ����Ʈ ��ü��? �� �� ��������Ʈ�� ������ �ִ±����� ������� 
	//����
	SYNTHESIZE(string, m_sName, Name);
	SYNTHESIZE(string, m_sLore, Lore);
	//�Ϸ�����
	SYNTHESIZE(string, m_sTarget, Target);
	SYNTHESIZE(int, m_nTargetDeath, TargetDeath);
	SYNTHESIZE(int, m_nCurrentTargetDeath, CurrentTargetDeath);
	SYNTHESIZE(string, m_sTakeitem, Takeitem);
	SYNTHESIZE(int, m_nTakeitemAmount, TakeitemAmount);
	SYNTHESIZE(bool, m_bQuestEnd, QuestEnd);
	//����
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

