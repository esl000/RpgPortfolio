#pragma once

class cUnitMonster : public cUnit
	, public iUnitActionDelegate
{
	friend class cMonsterDatabase;
protected:
	SYNTHESIZE(std::string, m_sFolder, Folder);
	SYNTHESIZE(std::string, m_sFile, File);
	SYNTHESIZE(DWORD, m_dwLevel, Level);
	SYNTHESIZE(int, m_nExp, Exp);
	SYNTHESIZE(int, m_nMoney, Money);
	SYNTHESIZE(vector<std::string>, m_vecItems, Items);
public:

	enum eMonsterAnim
	{
		E_STAND = 0
	};


	cUnitMonster();
	~cUnitMonster();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Damage(float fDamage);
	virtual void Die();

	virtual void OnUnitActionFinish(iUnitAction* pAction) override;
};

