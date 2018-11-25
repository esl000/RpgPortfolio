#pragma once

#include "cSkill.h"

#define g_pSkillManager cSkillManager::GetInstance()

class cSkillManager : public iSkillDelegate
{
protected:
	set<cSkill*> m_setSkill;
public:
	SINGLETONE(cSkillManager);

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual void Destroy();

	virtual void RegisterSkill(cSkill* pSkill);
	virtual void OnSkillFinish(cSkill* pSkill);
};

