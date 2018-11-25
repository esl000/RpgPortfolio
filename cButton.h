#pragma once

class cButton;

class iButtonSelect
{
public:
	virtual void onButtonSelect(cButton* pButton) = 0;
};

class cButton : public cGameObject
{
protected:

	enum eButtonState
	{
		E_NONE,
		E_ACTIVE,
		E_PUSH
	};

	RECT			m_stBoundingBox;
	eButtonState	m_eButtonState;
	LPD3DXSPRITE	m_pSprite;
	LPD3DXFONT	m_pFont;
	D3DXVECTOR3	m_vLocalFont;
	SYNTHESIZE(bool, m_isClick, Click);
	SYNTHESIZE(D3DXVECTOR3, m_vLocalPos, LocalPos);
	SYNTHESIZE(D3DXVECTOR3, m_vParentPos, ParentPos);
	SYNTHESIZE(DWORD, m_dButtonType, ButtonType);
	SYNTHESIZE(D3DXIMAGE_INFO, m_stImageInfo, ImageInfo);
	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pButton, ButtonTexture);
	SYNTHESIZE(iButtonSelect*, m_pButtonSelect, ButtonSelect);
	SYNTHESIZE(std::string, m_sButtonLore, ButtonLore);
public:
	cButton();
	~cButton();

	virtual void Setup(DWORD dButtonType = 0, char* szFullPath = NULL, char* szLore = NULL);
	virtual void Update();
	virtual void Render();
	virtual D3DCOLOR GetColor();
};

