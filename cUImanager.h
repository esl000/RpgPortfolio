#pragma once

#define g_pUImanager cUImanager::GetInstance()

class cUImanager : public cUIDelegate
{

private:
	set<cUIObject*> m_setUI;
	map<cUIObject::eUIType, vector<cUIObject*>> m_mapUIType;

	vector<cUIObject*> m_vecDeletePool;
public:
	SINGLETONE(cUImanager);

	void RegisterUI(cUIObject* pUI);
	set<cUIObject*>* GetUI();

	void Update();
	void Render();

	void Destroy();

	virtual void OnUIFinished(cUIObject* pUI);
	void WndProc(HWND hWnd, UINT messgae, WPARAM wParam, LPARAM lParam);
};

