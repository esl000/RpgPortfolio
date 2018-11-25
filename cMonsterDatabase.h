#pragma once

class cUnitMonster;

#define  g_pMonsterDatabase cMonsterDatabase::GetInstance()

class cMonsterDatabase
{
private:
	std::map<std::string, cUnitMonster*> m_mapMonster;
	vector<cUnitMonster*> m_vecMonster;
	void Load();
public:
	SINGLETONE(cMonsterDatabase);

	void Destroy();

	cUnitMonster* GetMonster(std::string sName);
	cUnitMonster* GetMonster(int& nIndex);
};

