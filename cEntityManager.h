#pragma once

#define g_pEntityManager cEntityManager::GetInstance()

class cEntityManager : public iEntityDelegate
{
private:
	set<cEntity*> m_setEntity;
public:
	SINGLETONE(cEntityManager);

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	virtual set<cEntity*>* GetSetEntitys();
	virtual void RegisterEntity(cEntity* pEntity);
	virtual void onEntityDelete(cEntity* pEntity);
};

