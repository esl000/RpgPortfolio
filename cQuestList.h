#pragma once

#include "cCustomQuest.h"

class cQuestList : public cObject
	, public iQuestDelegate
{
protected:
public:
	SYNTHESIZE(bool, m_bComplete, Complete);
	SYNTHESIZE(cCustomQuest*, m_pQuest, Quset);
	map<string, cCustomQuest*> m_mapQuest;

	cQuestList();
	~cQuestList();

	virtual void Setup();
	virtual void Update();
	//virtual void Render();

	void AddQuest(cCustomQuest* pQuest);
	void RemoveQuest(std::string sName);
	virtual void OnQuestFinished(cCustomQuest* pQuest) override;
	bool CheckFinish(string sQuestName);
	bool IsIn(string sQuestName);
};

