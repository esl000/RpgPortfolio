#pragma once

class cUnitCustomNpc;
class cQuestDatabase;
#define g_pNpcDatabase cNpcDataBase::GetInstance()

class cNpcDataBase
{
protected:
	std::map<string, cUnitCustomNpc*> m_mapDatabase;
	vector<cUnitCustomNpc*> m_vecDatabase;
	void Load();
public:
	SINGLETONE(cNpcDataBase);

	void Destroy();
	cUnitCustomNpc* GetCustomNpc(std::string sName);
	cUnitCustomNpc* GetCustomNpc(int& nIndex);
};

