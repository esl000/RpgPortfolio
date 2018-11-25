#pragma once

class cEntityBuilding;

#define g_pBuildingDatabase cBuildingDatabase::GetInstance()

class cBuildingDatabase
{
private:
	std::map<string, cEntityBuilding*> m_mapDatabase;
	vector<cEntityBuilding*> m_vecDatabase;
	void Load();
public:
	SINGLETONE(cBuildingDatabase);

	cEntityBuilding* GetBuilding(string sName);
	cEntityBuilding* GetBuilding(int& nIndex);
	void Destroy();
};

