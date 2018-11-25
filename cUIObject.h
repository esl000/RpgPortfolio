#pragma once

////////////////////////////////////////////////////
//[코드규칙]꼭 엄수 할것
//엔티티, 유닛 등은 꼭꼭 만든다음 매니저에 넣어주세요. 
//매니저에서 알아서 다 렌더랑 업데이트 해줍니다.
//멤버 변수 : m_
//벡터3 : v
//포인터 : p
//int : n
//float : f
//배열 : a
//구조체 : st
//string : s
//char[] : sz
//char : c
//stlset : set
//stlvextor : vec
//matrix : mat
//material : mtl
//stlmap : map
//entity : cEntity클래스명
//함수생성 : 주석필수
//1.로딩바 이미지 파랑색
//2.미니맵 위치
//3.경험치바 보라색 변경
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

