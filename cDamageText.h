#pragma once

class cUITextView;

class cDamageText : public cGameObject
{
public:
	enum eColorState
	{
		E_WHITE,
		E_YELLOW,
		E_RED
	};

protected:
	LPD3DXFONT						m_pFont;
	std::string						m_sStr;
	DWORD							m_dwColor;
	//cUITextView*					m_pText;
	float							m_fPlusY;
public:
	cDamageText();
	~cDamageText();

	void Setup(std::string str, eColorState eColor);
	void Update();
	void Render();
};

