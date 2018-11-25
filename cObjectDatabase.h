#pragma once

class cEntityObject;

#define g_pObjectDatabase cObjectDatabase::GetInstance()

class cObjectDatabase
{
private:
	std::map<string, cEntityObject*> m_mapObject;
	vector<cEntityObject*> m_vecObject;
	void Load();
public:
	SINGLETONE(cObjectDatabase);

	cEntityObject* GetObjects(string sName);
	cEntityObject* GetObjects(int& nIndex);
	void Destroy();
};

