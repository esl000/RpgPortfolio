#pragma once

////////////////////////////////////////////////////
//[�ڵ��Ģ]�� ���� �Ұ�
//��ƼƼ, ���� ���� ���� ������� �Ŵ����� �־��ּ���. 
//�Ŵ������� �˾Ƽ� �� ������ ������Ʈ ���ݴϴ�.
//��� ���� : m_
//����3 : v
//������ : p
//int : n
//float : f
//�迭 : a
//����ü : st
//string : s
//char[] : sz
//char : c
//stlset : set
//stlvextor : vec
//matrix : mat
//material : mtl
//stlmap : map
//entity : cEntityŬ������
//�Լ����� : �ּ��ʼ�
//1.�ε��� �̹��� �Ķ���
//2.�̴ϸ� ��ġ
//3.����ġ�� ����� ����
////////////////////////////////////////////////////


class cObject;
class cUIObject;


class cUIDelegate
{
public:
	virtual void OnUIFinished(cUIObject* pUI) = 0;
};


class cUIObject
	: public cObject
{

protected:
	std::vector<cUIObject*> m_vecChild;
	cUIObject*				m_pParent;
public:
	enum eUIType
	{
		E_QUEST,
		E_QUESTLIST,
		E_INVENTORY,
		E_STATUS,
		E_HPBAR,
		E_MESSAGE
	};
protected:
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matScale;
	D3DXMATRIXA16			m_matTrans;
	LPD3DXSPRITE			m_pSprite;
	SYNTHESIZE(int, m_nTag, Tag);
	SYNTHESIZE(bool, m_isDrawBoundingBox, DrawBoundingBox);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);
	SYNTHESIZE(ST_SIZEF, m_stSize, Size);
	SYNTHESIZE(eUIType, m_eUItype, UItype);
	SYNTHESIZE(cUIDelegate*, m_pUIDelegate, UIDelegate);
public:
	cUIObject(void);
	virtual ~cUIObject(void);
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void AddChild(cUIObject* pChild);
	virtual void Destroy();
	virtual cUIObject* GetChildByTag(int nTag);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

