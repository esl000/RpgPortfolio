#include "StdAfx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager(void)
	: m_pFont(NULL)
	, m_dwLastUpdateTime(0)
	, m_dwDeltaTime(0)
	, m_dFps(0)
	, m_dCurrentTime(0)
	, m_dFpsCount(0)
{
	m_dwLastUpdateTime = GetTickCount();
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 20;
	fd.Width = 10;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	strcpy_s(fd.FaceName, "굴림체"); //글꼴 스타일
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
}


cTimeManager::~cTimeManager(void)
{
}

void cTimeManager::Update()
{
	DWORD dwCurrTime = GetTickCount();
	m_dwDeltaTime = dwCurrTime - m_dwLastUpdateTime;
	m_dwLastUpdateTime = dwCurrTime;

	m_dCurrentTime += m_dwDeltaTime;
	++m_dFpsCount;
	if (m_dCurrentTime >= 1000)
	{
		m_dCurrentTime -= 1000;
		m_dFps = m_dFpsCount;
		m_dFpsCount = 0;
	}
}

void cTimeManager::Render()
{
	if (m_pFont)
	{
		char		FPS[128];
		sprintf_s(FPS, "Fps : %d", (int)m_dFps);
		RECT rc;
		SetRect(&rc, 0, 0, 4, 4);
		m_pFont->DrawTextA(NULL,
			FPS,
			strlen(FPS),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 0));
	}
}

float cTimeManager::GetElapsedTime()
{
	return m_dwDeltaTime / 1000.0f;
}
