#include "stdafx.h"
#include "cQuestList.h"
#include "cUnitPlayer.h"


cQuestList::cQuestList()
	: m_bComplete(false)
	, m_pQuest(NULL)
{
}


cQuestList::~cQuestList()
{
}

void cQuestList::Setup()
{
	
}

void cQuestList::Update()
{
	for each(auto p in m_mapQuest)
	{
		p.second->Update();
	}
}

void cQuestList::AddQuest(cCustomQuest* pQuest)
{
	if (pQuest)
	{
		pQuest->SetDelegate(this);
		m_mapQuest[pQuest->GetName()] = pQuest;
	}
}

void cQuestList::RemoveQuest(std::string sName)
{
	g_pUnitManager->GetPlayer()->SetCompleteQuest(m_mapQuest[sName]);
	m_mapQuest.erase(sName);
}

void cQuestList::OnQuestFinished(cCustomQuest* pQuest)
{
	RemoveQuest(pQuest->GetName());
}

bool cQuestList::CheckFinish(string sQuestName)
{
	return m_mapQuest[sQuestName]->CheckFinish();
}

bool cQuestList::IsIn(string sQuestName)
{
	if (m_mapQuest.find(sQuestName) == m_mapQuest.end())
		return false;
	else
		return true;
}
