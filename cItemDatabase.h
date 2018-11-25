#pragma once

class cItem;

#define g_pItemDatabase cItemDatabase::GetInstance()

class cItemDatabase
{
private:
	std::map<string, cItem*> m_mapItem;
	void Load();
public:
	SINGLETONE(cItemDatabase);

	cItem* GetItem(string sName);
	void Destroy();
};

