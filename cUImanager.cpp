#include "stdafx.h"
#include "cUImanager.h"


cUImanager::cUImanager()
{
}


cUImanager::~cUImanager()
{
}

void cUImanager::RegisterUI(cUIObject* pUI)
{
	pUI->SetUIDelegate(this);
	
	if (m_mapUIType[pUI->GetUItype()].size() == 1)
	{
		m_setUI.erase(m_mapUIType[pUI->GetUItype()][0]);
		SAFE_RELEASE(m_mapUIType[pUI->GetUItype()][0]);
		m_mapUIType[pUI->GetUItype()].clear();
		SAFE_RELEASE(pUI);
		return;
	}

	m_setUI.insert(pUI);
	m_mapUIType[pUI->GetUItype()].push_back(pUI);
}

set<cUIObject*>* cUImanager::GetUI()
{
	return &m_setUI;
}

void cUImanager::Update()
{
	for each(auto p in m_setUI)
	{
		p->Update();
	}
	for each(auto p in m_vecDeletePool)
	{
		m_setUI.erase(p);
		SAFE_RELEASE(p);
	}
	m_vecDeletePool.clear();
}

void cUImanager::Render()
{

	for each(auto p in m_setUI)
	{
		if (p)
			p->Render(NULL);
	}
}

void cUImanager::Destroy()
{
	for each(auto p in m_setUI)
	{
		SAFE_RELEASE(p);
	}
}

void cUImanager::OnUIFinished(cUIObject* pUI)
{
	m_vecDeletePool.push_back(pUI);

	for (size_t i = 0; i < m_mapUIType[pUI->GetUItype()].size();)
	{
		if (m_mapUIType[pUI->GetUItype()][i] == pUI)
		{
			m_mapUIType[pUI->GetUItype()].erase(m_mapUIType[pUI->GetUItype()].begin() + i);
			break;
		}
		else
			++i;
	}
}

void cUImanager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	for each(auto p in m_setUI)
	{
		if (p)
			p->WndProc(hWnd, message, wParam, lParam);
	}
}
