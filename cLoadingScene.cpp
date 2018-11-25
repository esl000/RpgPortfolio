#include "stdafx.h"
#include "cLoadingScene.h"

#include "cUIObject.h"
#include "cUILoading.h"

cLoadingScene::cLoadingScene()
	: m_pUILoading(NULL)
	, m_isChecked(false)
	, m_nCount(0)
{
	//임계영역 초기화
	//InitializeCriticalSection(&cs);
}


cLoadingScene::~cLoadingScene()
{
	//Scene넘어갈때 문제발생 메모리RELEASE 하면 안됨
	SAFE_RELEASE(m_pUILoading);
}

void cLoadingScene::Setup(void)
{
	DWORD dwThread[2] = { 0 };

	unsigned long ulStackSize = 0;

	////////////////////////////////////////////////////////////
	//CreateThread(인자값)
	//_In_opt_    LPSECURITY_ATTRIBUTES     lpThreadAttributes,
	//_In_        SIZE_T                    dwStackSize,
	//_In_        LPTHREAD_START_ROUTINE    lpStartAddress,
	//_In_opt_    __drv_aliasesMem LPVOID   lpParameter,
	//_In_        DWORD                     dwCreationFlags,
	//_Out_opt_   LPDWORD					lpThreadId
	///////////////////////////////////////////////////////////

	if (m_pUILoading == NULL)
	{
		m_pUILoading = new cUILoading;
		((cUILoading*)m_pUILoading)->Setup();
	}
}

void cLoadingScene::Update(void)
{
	if (m_pUILoading)
	{
		((cUILoading*)m_pUILoading)->Update();
	}
}

void cLoadingScene::Render(void)
{
	if (m_pUILoading)
	{
		((cUILoading*)m_pUILoading)->Render();
	}
}

void cLoadingScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
