#pragma once
#include "iUnitAction.h"

class cCustomQuest;
class cNpcCourse;
class cUIIQuest;
class cUnitPlayer;

class cUnitCustomNpc : public cUnit
	, public iUnitActionDelegate
{
protected:
	SYNTHESIZE(std::string, m_sName, Name);
	SYNTHESIZE(std::string, m_sLore, Lore);
	SYNTHESIZE(std::string, m_sQuest, Quest);
	SYNTHESIZE(std::string, m_sFolder, Folder);
	SYNTHESIZE(std::string, m_sFile, File);
	SYNTHESIZE(std::string, m_sMoveNpc, MoveNpc);
	SYNTHESIZE(cCustomQuest*, m_pQuest, PQuest);
	SYNTHESIZE(bool, m_bPicking, picking);
	SYNTHESIZE_ONLY_GETTER(int, m_nQuestIndex, QuestIndex);
private:
	std::vector<cCustomQuest*> m_vecQuest;
	std::vector<D3DXVECTOR3> m_vecVMoveCourse;
public:
	cUnitCustomNpc();
	virtual ~cUnitCustomNpc();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnUnitActionFinish(iUnitAction* pAction);
	
	void OpenMessage();
};

