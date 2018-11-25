#pragma once
class cText : public cGameObject
{
protected:
	D3DXMATRIXA16					m_matBillBoard;
	ID3DXMesh*						m_pText;
	int								m_nLength;
public:
	cText();
	~cText();

	void Setup(std::wstring sStr);
	void Update();
	void Render();
};

