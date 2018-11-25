#pragma once

class cSkill;
class cUnit;

class iSkillDelegate
{
public:
	virtual void OnSkillFinish(cSkill* pSkill) = 0;
};
class cSkill : public cObject
{
protected:
	SYNTHESIZE(cUnit*, m_pOwner, Owner);
	SYNTHESIZE(iSkillDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(iEffect*, m_pEffect, Effect);
public:
	cSkill();
	virtual ~cSkill();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

