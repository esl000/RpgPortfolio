#include "StdAfx.h"
#include "cUIInterface.h"
#include "cUIImageView.h"
#include "cUIInvenTory.h"
#include "cUIStatus.h"
#include "cUIPlayerBar.h"
#include "cUISkillInvenTory.h"
#include "cUIMonsterBar.h"
#include "cUIRootItem.h"
#include "cUIStore.h"

cUIInterface::cUIInterface(void)
	: m_bInvenTory(false)
	, m_pSkillInvenTory(false)
	, m_pUIPlayerBar(false)
	, m_pUIStore(false)
	, m_bTest(false)
{
}


cUIInterface::~cUIInterface(void)
{
	SAFE_RELEASE(m_pSkillInvenTory);
	SAFE_RELEASE(m_pUIPlayerBar);
	SAFE_RELEASE(m_pUIStore);
}

void cUIInterface::Setup()
{
	//테스트
	m_pSkillInvenTory = new cUISkillInvenTory;
	m_pSkillInvenTory->Setup();

	m_pUIPlayerBar = new cUIPlayerBar;
	m_pUIPlayerBar->Setup();

	m_pUIStore = new cUIStore;
	m_pUIStore->Setup();
}

void cUIInterface::Update()
{
	if (m_pSkillInvenTory)
	{
		m_pSkillInvenTory->Update();
	}
	if (m_pUIPlayerBar)
	{
		m_pUIPlayerBar->Update();
	}

	if (m_bTest)
	{
		if (m_pUIStore)
		{
			m_pUIStore->Update();
		}
	}

	//테스트
	if (GetKeyState(VK_F2) & 0x8001)
	{
		m_bTest = true;
	}
	else
	{
		m_bTest = false;
		return;
	}

}

void cUIInterface::Render()
{
	if (m_pSkillInvenTory)
	{
		m_pSkillInvenTory->Render(NULL); 
	}
	if (m_pUIPlayerBar)
	{
		m_pUIPlayerBar->Render(NULL);
	}

	if (m_bTest)
	{
		if (m_pUIStore)
		{
			m_pUIStore->Render(NULL);
		}
	}
	
}

void cUIInterface::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'P':
			break;
		}
		break;
	}
}