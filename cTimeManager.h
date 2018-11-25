#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	DWORD			m_dwLastUpdateTime;
	DWORD			m_dwDeltaTime;
	DWORD			m_dFps;
	DWORD			m_dCurrentTime;
	DWORD			m_dFpsCount;
	LPD3DXFONT		m_pFont;

public:
	SINGLETONE(cTimeManager);

	void Update();
	void Render();
	float GetElapsedTime();
};

