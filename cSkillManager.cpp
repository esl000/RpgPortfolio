#include "stdafx.h"
#include "cSkillManager.h"


cSkillManager::cSkillManager()
{
}


cSkillManager::~cSkillManager()
{
}

void cSkillManager::Setup()
{
	m_setSkill.clear();
}

void cSkillManager::Update()
{
	for each(auto p in m_setSkill)
	{
		if (p)
			p->Update();
	}
}

void cSkillManager::Render()
{
	for each(auto p in m_setSkill)
	{
		if (p)
			p->Render();
	}
}

void cSkillManager::Destroy()
{
	for each(auto p in m_setSkill)
	{
		if (p)
			SAFE_RELEASE(p);
	}
}


void cSkillManager::RegisterSkill(cSkill* pSkill)
{
	pSkill->SetDelegate(this);
	m_setSkill.insert(pSkill);
}

void cSkillManager::OnSkillFinish(cSkill* pSkill)
{
	m_setSkill.erase(pSkill);
	SAFE_RELEASE(pSkill);
}
