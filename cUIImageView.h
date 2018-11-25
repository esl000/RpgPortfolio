#pragma once

class cUIImageView : public cUIObject
{
private:
	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	SYNTHESIZE(D3DXIMAGE_INFO, m_stImageInfo, stImageInfo);
	SYNTHESIZE(string, m_sFullPath, FullPath);

public:
	inline void SetScale(D3DXVECTOR3 _Scale)
	{
		D3DXMatrixScaling(&m_matScale, _Scale.x, _Scale.y, _Scale.z);
		//m_vScale = _Scale;
	}

public:
	cUIImageView(void);
	virtual ~cUIImageView(void);

	virtual void Update(void) override;
	virtual void Render(LPD3DXSPRITE pSprite) override;

	virtual void SetTexture(std::string sFullPath);
	virtual LPDIRECT3DTEXTURE9 GetTexture();
	string GetFullPath();


};

