#pragma once

class cUIButton;
class cGameScene;
class cMenuScene;
class cLoadingScene;
class cMapToolScene;

class iUIButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) = 0;
};

class cUIButton : public cUIObject
{
protected:
	enum eButtonState
	{
		E_NORMAL,
		E_MOVER,
		E_SELECTED,
		E_COUNT,
	};

	eButtonState		m_eButtonState;
	LPDIRECT3DTEXTURE9	m_aTexture[E_COUNT];
	SYNTHESIZE(iUIButtonDelegate*, m_pDelegate, Delegate);

private:
	cGameScene*				m_pGameScene;
	cLoadingScene*			m_pLoadingScene;
	cMapToolScene*			m_pMapToolScene;


public:
	cUIButton(void);
	virtual ~cUIButton(void);

public:
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
	virtual void SetButtonImage(std::string sNor, std::string sOvr, std::string sSel);
public:
	void OnClick(cUIButton* pUIButton);
};

