#pragma once

#include "cButton.h"

class cMessageBox;

class iMessageBoxDelegate
{
	virtual void onMessageBoxFinish(cMessageBox* pMessageBox) = 0;
};

class cMessageBox : public cGameObject
	, public iButtonSelect
{
protected:
	vector<cButton*> m_vecButton;
	RECT				m_stBoundingBox;
	LPD3DXSPRITE		m_pSprite;
	LPD3DXFONT		m_pFont;
	D3DXVECTOR3		m_vLocalFont;
	POINT			m_ptPrev;
	SYNTHESIZE(bool, m_isClick, Click);
	SYNTHESIZE(std::string, m_sLore, Lore);
	SYNTHESIZE(RECT,	m_actionBox, ActionBox);
	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pMessage, MessageTexture);
	SYNTHESIZE(D3DXIMAGE_INFO, m_stImageInfo, ImageInfo);
	SYNTHESIZE(iMessageBoxDelegate*, m_pDelegete, Delegete);
public:
	cMessageBox();
	~cMessageBox();

	virtual void AddButton(D3DXVECTOR3 vLocalPos, DWORD dIndex, char* szFullPath, char* szLore = NULL);

	virtual void Setup(char* szFullPath = NULL, char* szLore = NULL);
	virtual void Update();
	virtual void Render();
	virtual void onButtonSelect(cButton* pButton);
};

