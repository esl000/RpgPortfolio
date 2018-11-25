#include "StdAfx.h"
#include "cFontManager.h"


cFontManager::cFontManager(void)
{
}


cFontManager::~cFontManager(void)
{
}

LPD3DXFONT cFontManager::GetFont( eFontType e )
{
	if(m_mapFont.find(e) == m_mapFont.end())
	{
		if(e == E_DEFAULT)
		{
			//폰트 생성
			D3DXFONT_DESC fd;
			ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
			fd.Height			= 20;
			fd.Width			= 10;
			fd.Weight			= FW_MEDIUM;
			fd.Italic			= false;
			fd.CharSet			= DEFAULT_CHARSET;
			fd.OutputPrecision  = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily   = FF_DONTCARE;
			strcpy_s(fd.FaceName, "궁서체");	//글꼴 스타일
			//AddFontResource("umberto.ttf");
			//strcpy(fd.FaceName, "umberto");

			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
		}
		if (e == E_QUEST)
		{
			//폰트 생성
			D3DXFONT_DESC fd;
			ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
			fd.Height = 20;
			fd.Width = 10;
			//	fd.Weight = FW_MEDIUM;
			fd.Weight = FW_BLACK;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			//strcpy_s(fd.FaceName, "-2002");	//글꼴 스타일
			AddFontResource("K_Damage.ttf");
			strcpy_s(fd.FaceName, "K_Damage");
//			cout << "얌마" << endl;
			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
		}
		if (e == E_NAME)
		{
			//폰트 생성
			D3DXFONT_DESC fd;
			ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
			fd.Height = 8;
			fd.Width = 6;
			//	fd.Weight = FW_MEDIUM;
			fd.Weight = FW_BLACK;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			//strcpy_s(fd.FaceName, "-2002");	//글꼴 스타일
			AddFontResource("K_Damage.ttf");
			strcpy_s(fd.FaceName, "K_Damage");
			//			cout << "얌마" << endl;
			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
		}
	}
	return m_mapFont[e];
}

void cFontManager::Destroy()
{
	for each(auto it in m_mapFont)
	{
		SAFE_RELEASE(it.second);
	}
}
