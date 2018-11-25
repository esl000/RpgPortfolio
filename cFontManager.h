#pragma once

#define g_pFontManager cFontManager::GetInstance()

class cFontManager
{

private:
	SINGLETONE(cFontManager);

public:
	enum eFontType
	{
		E_DEFAULT,
		E_QUEST,
		E_NAME,
	};

private:
	std::map<eFontType, LPD3DXFONT> m_mapFont;

public:
	LPD3DXFONT GetFont(eFontType e);
	void Destroy();
};

