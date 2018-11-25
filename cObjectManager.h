#pragma once

#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager
{
private:
	std::set<cObject*> m_setObject;
	
	std::vector<cObject*> m_vecAutoRelease;

public:
	SINGLETONE(cObjectManager);

public:
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Destroy();

	void AddAutoReleasePool(cObject* pObject);
	void Drain();
};

